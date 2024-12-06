#include "FrameWork.h"
#include "State.h"

// 전역 변수 정의
float line[] = {
	5.0f, 0.0f, 0.0f,
	-5.0f, 0.0f, 0.0f,
	0.0f, 5.0f, 0.0f,
	0.0f, -5.0f, 0.0f,
	0.0f, 0.0f, 5.0f,
	0.0f, 0.0f, -5.0f
};

float vPositionList[] = {
	0.5f, 1.0f, 0.5f, // 앞 우측 상단
	0.5f, 1.0f, -0.5f, // 뒤 우측 상단
	-0.5f, 1.0f, -0.5f, // 뒤 좌측 상단
	-0.5f, 1.0f, 0.5f, // 앞 좌측 상단
	-0.5f, 0.0f, 0.5f, // 앞 좌측 하단
	-0.5f, 0.0f, -0.5f, // 뒤 좌측 하단
	0.5f, 0.0f, -0.5f, // 뒤 우측 하단
	0.5f, 0.0f, 0.5f, // 앞 우측 하단

	0.5f, 0.0f, 0.5f,
	0.5f, 0.0f, -0.5f,
	-0.5f, 0.0f, 0.5f, // 앞 좌측 하단
	-0.5f, 0.0f, -0.5f, // 뒤 좌측 하단
	0.0f, 0.5f, 0.0f
};

unsigned int index[] = {
	1, 3, 0, // 첫 번째 삼각형         // 위 사각형
	1, 2, 3, // 두 번째 삼각형
	5, 4, 2, // 왼쪽 사각형
	3, 2, 4,
	0, 7, 6, // 오른쪽 사각형
	6, 1, 0,
	3, 4, 7, // 앞 사각형
	7, 0, 3,
	6, 5, 2, // 뒤 사각형
	6, 2, 1,
	6, 7, 4, // 세 번째 삼각형         // 아래 사각형
	6, 4, 5, // 네 번째 삼각형

	8, 9, 10,
	10, 9, 11,
	10, 8, 12, // 앞 삼각형
	8, 9, 12, // 오른쪽
	9, 11, 12, // 뒤쪽
	11, 10, 12 // 왼쪽
};

char* SERVERIP = (char*)"127.0.0.1";
// char* SERVERIP = (char*)"192.168.161.76";

#define SERVERPORT 9000
#define BUFSIZE    1024

FrameWork::FrameWork()
{
	int retval;
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		std::cout << "실패" << std::endl;

	// 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 데이터 통신에 사용할 변수
	/*char buf[BUFSIZE];
	int len;
	char* s = (char*)"192.000.00.01";
	len = (int)strlen(s);
	strncpy(buf, s, len);
	send(sock, buf, len + 1, 0);*/

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
	}
	float vertices[] = { 0.0f, 0.0f, 0.0f };
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	Init_Shader();
	init_Buffer();

	states.push_back(new Stay_State);  // 벡터에 동적으로 할당된 객체를 추가
	states.push_back(new Play_State);  // 벡터에 동적으로 할당된 객체를 추가

	currentStateIndex = 0;  // 처음 상태는 Stay_State

}

void FrameWork::Make_VertexShader()
{

	vertexsource = filetobuf("vertex.glsl");//--- 버텍스 세이더 객체 만들기
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexshader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}

	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"in vec3 positionAttribute;"
		"uniform mat4 modelTransform;"
		"uniform mat4 viewTransform;"
		"uniform mat4 projectionTransform;"
		//"in vec3 colorAttribute;"
		"in vec2 textureCoordinateAttribute;"
		//"out vec3 passColorAttribute;"
		"out vec2 passTextureCoordinateAttribute;"
		"void main()"
		"{"
		"gl_Position = projectionTransform * viewTransform * modelTransform * vec4(positionAttribute, 1.0);"
		//"passColorAttribute = colorAttribute;"
		"passTextureCoordinateAttribute = textureCoordinateAttribute;"
		"}";
	Text_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Text_vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(Text_vertexShader);

}

void FrameWork::Make_FragmentShader()
{
	fragmentsource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentshader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}

	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 passColorAttribute;"
		"in vec2 passTextureCoordinateAttribute;"
		"out vec4 fragmentColor;"
		"uniform sampler2D tex;"
		"void main()"
		"{"
		//컬러만 출력
		//"fragmentColor = vec4(passColorAttribute, 1.0);"
		//텍스처만 출력
		"fragmentColor = texture(tex, passTextureCoordinateAttribute);"
		//텍스처와 컬러 같이 출력
		//"fragmentColor = texture(tex, passTextureCoordinateAttribute)*vec4(passColorAttribute, 1.0); "
		"}";
	Text_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Text_fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(Text_fragmentShader);

	glGetShaderiv(Text_fragmentShader, GL_COMPILE_STATUS, &result);
}

void FrameWork::Init_Shader()
{
	Make_VertexShader(); //--- 버텍스 세이더 만들기
	Make_FragmentShader(); //--- 프래그먼트 세이더 만들기

	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);

	GLchar errorLog[512];
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
	//--- 세이더 삭제하기
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	//--- Shader Program 사용하기

	triangleShaderProgramID = glCreateProgram();

	glAttachShader(triangleShaderProgramID, Text_vertexShader);
	glAttachShader(triangleShaderProgramID, Text_fragmentShader);

	glLinkProgram(triangleShaderProgramID);


	glDeleteShader(Text_vertexShader);
	glDeleteShader(Text_fragmentShader);


	glGetProgramiv(triangleShaderProgramID, GL_LINK_STATUS, &result);
}

void FrameWork::init_Buffer()
{
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &linevao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(linevao); //--- VAO를 바인드하기
	glGenBuffers(2, linevbo); //--- 2개의 VBO를 지정하고 할당하기
	glBindBuffer(GL_ARRAY_BUFFER, linevbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);



	Define_VertexArrayObject();
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
}

void FrameWork::Define_VertexArrayObject()
{
	float position[] = {
	-0.5f,  -0.5f, 0.0f, //vertex 1 : Top
	0.5f, -0.5f, 0.0f, //vertex 2 : Top-right
	0.5f, 0.5f, 0.0f, //vertex 3 : Bottom-right
	0.5f, 0.5f, 0.0f, //vertex 4 : Bottom-right
	-0.5f, 0.5f, 0.0f, //vertex 5 : Bottom-left
	-0.5f,  -0.5f, 0.0f //vertex 6 : Top-left
	};

	float color[] = {
		1.0f, 1.0f, 1.0f, //vertex 1 : RED (1,0,0)
		1.0f, 1.0f, 1.0f, //vertex 2 : GREEN (0,1,0) 
		1.0f, 1.0f, 1.0f,  //vertex 3 : BLUE (0,0,1)
		1.0f, 1.0f, 1.0f,  //vertex 4 : BLUE (0,0,1)
		1.0f, 1.0f, 1.0f,  //vertex 5 : WHITE (1,1,1)
		1.0f, 1.0f, 1.0f //vertex 6 : RED (1,0,0)
	};

	float textureCoordinate[] = {
	0.0f, 0.0f,  //vertex 1  
	1.0f, 0.0f,  //vertex 2
	1.0f, 1.0f,   //vertex 3        
	1.0f, 1.0f,  //vertex 1  
	0.0f, 1.0f,  //vertex 2
	0.0f, 0.0f   //vertex 3        
	};



	//#2
	//Vertex Buffer Object(VBO)를 생성하여 vertex 데이터를 복사한다.
	glGenBuffers(1, &trianglePositionVertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, trianglePositionVertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glGenBuffers(1, &triangleColorVertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, triangleColorVertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	glGenBuffers(1, &triangleTextureCoordinateBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, triangleTextureCoordinateBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinate), textureCoordinate, GL_STATIC_DRAW);


	//#6
	glGenVertexArrays(1, &triangleVertexArrayObject);
	glBindVertexArray(triangleVertexArrayObject);


	GLint positionAttribute = glGetAttribLocation(triangleShaderProgramID, "positionAttribute");
	if (positionAttribute == -1) {
		//cerr << "position 속성 설정 실패" << endl;
	}
	glBindBuffer(GL_ARRAY_BUFFER, trianglePositionVertexBufferObjectID);
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(positionAttribute);

	GLint textureCoordinateAttribute = glGetAttribLocation(triangleShaderProgramID, "textureCoordinateAttribute");
	if (textureCoordinateAttribute == -1) {
		//cerr << "Texture Coordinate 속성 설정 실패" << endl;
	}
	glBindBuffer(GL_ARRAY_BUFFER, triangleTextureCoordinateBufferObjectID);
	glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureCoordinateAttribute);


	glBindVertexArray(0);
}

void FrameWork::Update(int value)
{
	states[currentStateIndex]->Update();
}

void FrameWork::Draw_Scene()
{
		glUseProgram(s_program);
		glClearColor(1.0, 1.0, 1.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		states[currentStateIndex]->Draw();

		glutSwapBuffers();

}

GLvoid FrameWork::Reshape(int w, int h)
{
	return glViewport(0, 0, w, h);
}

void FrameWork::KeyDownboard(int key, int x, int y)
{
	states[currentStateIndex]->KeyDown(key);
}

void FrameWork::KeyUpboard(int key, int x, int y)
{
	states[currentStateIndex]->KeyUp(key);
}

void FrameWork::SKeyDownboard(int key, int x, int y)
{
	states[currentStateIndex]->SKeyDown(key);
}

void FrameWork::SKeyUpboard(int key, int x, int y)
{
	states[currentStateIndex]->SKeyUp(key);
}

void FrameWork::Enter_State()
{
	states[currentStateIndex]->enter();
}

void FrameWork::Exit_State()
{
	states[currentStateIndex]->exit();
	++currentStateIndex;
	states[currentStateIndex]->enter();
}
