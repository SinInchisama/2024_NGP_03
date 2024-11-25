#pragma once
#include <iostream>

float line[]{
5.0f,0.0f,0.0f,
-5.0f,0.0f,0.0f,
0.0f,5.0f,0.0f,
0.0f,-5.0f,0.0f,
0.0f,0.0f,5.0f,
0.0f,0.0f,-5.0f
};

float vPositionList[] = {
0.5f, 1.0f, 0.5f, // �� ���� ���
0.5f, 1.0f, -0.5f, // �� ���� ���
-0.5f, 1.0f, -0.5f, // �� ���� ���
-0.5f, 1.0f, 0.5f, // �� ���� ���
-0.5f,0.0f,0.5f, // �� ���� �ϴ�
-0.5f,0.0f,-0.5f,	// �� ���� �ϴ�
0.5f,0.0f,-0.5f,	// �� ���� �ϴ�
0.5f,0.0f,0.5f,		// �� ���� �ϴ�

0.5f,0.0f,0.5f,
0.5f,0.0f,-0.5f,
-0.5f,0.0f,0.5f, // �� ���� �ϴ�
-0.5f,0.0f,-0.5f,	// �� ���� �ϴ�
0.0f,0.5f,0.0f
};

unsigned int index[] = {
1, 3, 0, // ù ��° �ﰢ��			// �� �簢��
1, 2, 3, // �� ��° �ﰢ��
5, 4, 2,									// ���� �簢��
3, 2, 4,
0, 7, 6,							// ������ �簢��
6, 1, 0,
3, 4, 7,							// �� �簢��
7, 0, 3,
6, 5, 2,								// �� �簢��
6, 2, 1,
6, 7, 4,	// �� ��° �ﰢ��			// �Ʒ� �簢��
6, 4, 5,	// �� ��° �ﰢ��

8,9,10,
10,9,11,
10,8,12,		// �� �ﰢ��
8,9,12,			// ������
9,11,12,		// ����
11,10,12		// ����
};

char* filetobuf(const char* file) {
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
};