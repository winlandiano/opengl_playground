#include <stdio.h>
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include "includes/ogldev_math_3d.h"

GLuint VBO;

/**
* ��Ⱦ�ص�����
*/
static void RenderScenceCB() {
	// �����ɫ����
	glClear(GL_COLOR_BUFFER_BIT);

	// ������������
	glEnableVertexAttribArray(0);
	// ��GL_ARRAY_BUFFER������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���߹�����������bufer�е�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// ��ʼ���Ƽ���ͼ��(����һ����)
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//  ���ö�������
	glDisableVertexAttribArray(0);

	// ����ǰ�󻺴�
	glutSwapBuffers();
}

/**
* �������㻺����
*/
static void CreateVertexBuffer()
{
	// ��������һ������Ķ�������
	Vector3f Vertices[3];
	// ����������Ļ����
	Vertices[0] = Vector3f(-0.8f, -0.8f, 0.0f);
	Vertices[1] = Vector3f(0.8f, -0.8f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 0.8f, 0.0f);

	// ����������
	glGenBuffers(1, &VBO);
	// ��GL_ARRAY_BUFFER������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �󶨶�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

/**
* ������
*/
int main(int argc, char ** argv) {

	// ��ʼ��GLUT
	glutInit(&argc, argv);

	// ��ʾģʽ��˫���塢RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// ��������
	glutInitWindowSize(480, 320);      // ���ڳߴ�
	glutInitWindowPosition(100, 100);  // ����λ��
	glutCreateWindow("Tutorial 02");   // ���ڱ���

									   // ��ʼ��Ⱦ
	glutDisplayFunc(RenderScenceCB);

	// ���GLEW�Ƿ����������Ҫ��GLUT��ʼ��֮��
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	// ������պ����ɫֵ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// �������㻺����
	CreateVertexBuffer();


	// ֪ͨ��ʼGLUT���ڲ�ѭ��
	glutMainLoop();

	return 0;
}