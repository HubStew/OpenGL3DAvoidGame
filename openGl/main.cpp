/* 
 * �ۼ��� : CG
 * ����   : ������Ʈ���� ȭ���� �����ϰ� �׿� �ʿ��� �ҽ����� ����
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/FreeImage.h>
#include <string>

#include <WindowsX.h>

#include "glm.h"
#include "texture.h"
#include "mousemove.h"
#include "menu.h"
#include "stone.h"
#include "text.h"


#define START_POIHNT -3.0
#define END_POIHNT 0.0

GLMmodel *spongeModel;
char *FileName="Spongebob.obj"; 

GLMmodel *stoneModel;
char *FileName2="mr_krab.obj";

const GLfloat size = 0.2;

GLuint backTexture;
GLuint spongeTexture;
GLuint stoneTextre;

float delta = 0.001;
float stonePos = START_POIHNT;
float stonePos2 = START_POIHNT;
bool gameOver2 = true;
bool gameOver = true;

double tmpScore;
double score = 0;

void display();
void reshape(int w, int h);
void OTHER_INIT();


/* .obj������ �о�帮�� �Լ� */
void ModelLoad()
{
	// ������	
	spongeModel = glmReadOBJ(FileName);
	glmFacetNormals(spongeModel); 
	glmVertexNormals(spongeModel,90);
	glmUnitize(spongeModel);

	// ��
	stoneModel = glmReadOBJ(FileName2);
	glmFacetNormals(stoneModel); 
	glmVertexNormals(stoneModel,90);
	glmUnitize(stoneModel);
}

/* ȭ���� �籸���ϰ� Display�ϴ� �Լ��� �ҷ��ִ� �Լ� */
void GLUT_CALL_FUNC()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
}

/* Texture�� �ҷ��� init�ϴ� �Լ� */
void texture_init()
{
	overTexture = loadTexture("over.jpg");
	mainTexture = loadTexture("main2.jpg");
	backTexture = loadTexture("back.jpg");
	spongeTexture = loadTexture("spongebob_d.jpg");
	stoneTextre = loadTexture("mrkrabs_d.png");
}

/* ��ü���� Opengl�� �̿��ϴ� �͵��� �ʱ�ȭ�ϴ� �Լ� */
void GLUT_INIT(int *argcp, char **argv)
{
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("���ָ� ������ ��������");

	glEnable( GL_TEXTURE_2D );

	texture_init();
	GLUT_CALL_FUNC();
	OTHER_INIT();
}

/* GLUT_INIT���� �ʱ�ȭ�ϰ� ��Ÿ �������� �ʱ�ȭ�ϴ� �Լ� */
void OTHER_INIT()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);
	ModelLoad();
}

/* ĳ������ ���������� ȭ�鿡 ����ϴ� �Լ�. */
void spongeDisplay()
{
	glPushMatrix();

		glScalef(0.75, 0.75, 0.75);

		glRotatef(30, 0, 1, 0);
		glRotatef(30, -0.5, 0, 0);
		glRotatef(180, 0, 1, 0);
		glTranslatef(0.0f, -1.5f, 0.0f);

		if ( mousePosition == 1 )
			glTranslatef(2.0f, 0.0f, 0.0f);
		else if (mousePosition == 2)
			glTranslatef(0.0f, 0.0f, 0.0f);
		else if (mousePosition == 3)
			glTranslatef(-2.0f, 0.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, spongeTexture);
		glmDraw(spongeModel,GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
	glPopMatrix();

}

/* ���� ���� �� ���ȭ���� �����ϴ� �Լ� */
void backGround()
{
	glPushMatrix();

	glRotatef(30, 0, 1, 0);
	glRotatef(30, -0.5, 0, 0);
	glTranslatef(0.0f, 0.0f, -2.0f);

	glBindTexture(GL_TEXTURE_2D, backTexture);

	glBegin( GL_QUADS );
	glTexCoord3f( 0.0f, 0.0f, 0.0f );		glVertex3f( -4.0, -4.0, 0.0 );
	glTexCoord3f( 1.0f, 0.0f, 0.0f );		glVertex3f( 4.0, -4.0, 0.0 );
	glTexCoord3f( 1.0f, 1.0f, 0.0f );		glVertex3f( 4.0, 4.0, 0.0 );
	glTexCoord3f( 0.0f, 1.0f, 0.0f );		glVertex3f( -4.0, 4.0, 0.0);
	glEnd();

	glPopMatrix();
}

/* ������ ���� ���Ի����� ȭ�鿡 ����ϰ� �̵����ִ� �Լ� */
void stoneDisplay()
{

	glBindTexture(GL_TEXTURE_2D, stoneTextre);

	glRotatef(30, 0, 1, 0);
	glRotatef(30, -0.5, 0, 0);
	
	
	glScalef(0.75, 0.75, 0.75);

	if(stonePos > 3.5 || gameOver == true) {
		stonePos = START_POIHNT;
		delta = delta + 0.0001;
		makeRock();
		gameOver = false;

	}
	else {

		if(rockPos[1] == 1) {
			glPushMatrix();
			glTranslatef(-2.0, -stonePos, stonePos);
			glmDraw(stoneModel,GLM_SMOOTH|GLM_TEXTURE);
			glPopMatrix();

			if (mousePosition == 1 && (stonePos > END_POIHNT && stonePos < 1.0 ))
			{
				gameOver = true;
			}
		}
		if(rockPos[2] == 1) {
			glPushMatrix();
			glTranslatef(0.0, -stonePos, stonePos);

			glmDraw(stoneModel,GLM_SMOOTH|GLM_TEXTURE);
			glPopMatrix();

			if (mousePosition == 2 && (stonePos > END_POIHNT && stonePos < 1.0))
			{
				gameOver = true;
			}
		}

		if(rockPos[3] == 1){
			glPushMatrix();
			glTranslatef(2.0, -stonePos, stonePos);
			glmDraw(stoneModel,GLM_SMOOTH|GLM_TEXTURE);
			glPopMatrix();

			if (mousePosition == 3 && (stonePos > END_POIHNT && stonePos < 1.0))
			{
				gameOver = true;
			}
		}
	}


	stonePos += delta;

	if (gameOver == true)
	{
		//printf("����");
		menu = 3;
	}

}

/* ���� �� ���� ���Ի����� ȭ�鿡 ����ϰ� �� �ڿ� �̾ �� �ٸ� ���Ի����� ����ϴ� �Լ� */
void stoneDisplay2()
{

	glBindTexture(GL_TEXTURE_2D, stoneTextre);


	if(stonePos2 > 3.5 || gameOver2 == true) {
		stonePos2 = stonePos - 3.3;
		delta = delta + 0.0001;
		makeRock2();
		gameOver2 = false;
	}
	else {

		if(rockPos2[1] == 1) {

			glPushMatrix();
			glTranslatef(-2.0, -stonePos2, stonePos2);
			glmDraw(stoneModel,GLM_SMOOTH|GLM_TEXTURE);
			glPopMatrix();

			if (mousePosition == 1 && (stonePos2 > END_POIHNT && stonePos2 < 1.0 ))
			{
				gameOver2 = true;
			}
		}
		if(rockPos2[2] == 1) {

			glPushMatrix();
			glTranslatef(0.0, -stonePos2, stonePos2);

			glmDraw(stoneModel, GLM_SMOOTH|GLM_TEXTURE);
			glPopMatrix();

			if (mousePosition == 2 && (stonePos2 > END_POIHNT && stonePos2 < 1.0))
			{
				gameOver2 = true;
			}
		}
		if(rockPos2[3] == 1){
			glPushMatrix();
			glTranslatef(2.0, -stonePos2, stonePos2);
			glmDraw(stoneModel,GLM_SMOOTH|GLM_TEXTURE);
			glPopMatrix();

			if (mousePosition == 3 && (stonePos2 > END_POIHNT && stonePos2 < 1.0))
			{
				gameOver2 = true;
			}
		}

	}

	stonePos2 += delta;

	if (gameOver2 == true)
	{
		//printf("����22\n");
		menu = 3;
	}

}

/* ȭ�鿡 �׸��� �Լ�. ��� �׷��ִ°��� �� �Լ��ȿ� �־ OpenGL�� �� �Լ��� �θ� */
void display()
{
	static float Light0Pos[]={10.0, 10.0, 10.0, 10.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0,0,0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);
	backGround();

	// �޴��� �׸��� ���� ��
	if (menu == 1)
	{
		mainMenu();
		
	}
	else if (menu == 2)
	{	
		score = score + (delta*3);

		// �׾����� ǥ���ϱ� ���ؼ�
		tmpScore = score;
		std::string tmpScoreS = std::to_string((long long)tmpScore);
		
		glPushMatrix();
			gluOrtho2D(0, 1024, 768, 0);
			output(1200, -400, "Score : " + tmpScoreS);
		glPopMatrix();

		if ( mousePosition == 1)
			glRotatef(8, 0, 0, -1);
		else if (mousePosition == 2)
			glRotatef(8, 0, 0, 0);
		else
			glRotatef(8, 0, 0, 1);

		spongeDisplay();
		stoneDisplay();
		stoneDisplay2();
	} 
	else if (menu == 3)
	{
		stonePos = START_POIHNT;
		stonePos2 = START_POIHNT;
		gameOver2 = true;
		gameOver = true;
		delta = 0.001;
		score = 0;

		std::string tmpScoreS = std::to_string((long long)tmpScore);
		
		gameOverSecne();

		glPushMatrix();
			gluOrtho2D(0, 1024, 768, 0);
			output(1200, -400, "Score : " + tmpScoreS);
		glPopMatrix();
		
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

/* ȭ���� ũ�⸦ �����ϴ� �Լ� */
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

/* ���� �Լ� */
int main(int argc, char **argv)
{
	//printf("%d", menu);


	GLUT_INIT(&argc, argv);
	glutMouseFunc(MouseButton);

	glutMainLoop();

	return 0;

}
