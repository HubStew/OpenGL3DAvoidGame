/* 
 * 작성팀 : CG
 * 내용   : 프로젝트에서 화면을 구성하고 그에 필요한 소스들을 담음
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


/* .obj파일을 읽어드리는 함수 */
void ModelLoad()
{
	// 스펀지	
	spongeModel = glmReadOBJ(FileName);
	glmFacetNormals(spongeModel); 
	glmVertexNormals(spongeModel,90);
	glmUnitize(spongeModel);

	// 돌
	stoneModel = glmReadOBJ(FileName2);
	glmFacetNormals(stoneModel); 
	glmVertexNormals(stoneModel,90);
	glmUnitize(stoneModel);
}

/* 화면을 재구성하고 Display하는 함수를 불러주는 함수 */
void GLUT_CALL_FUNC()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
}

/* Texture을 불러서 init하는 함수 */
void texture_init()
{
	overTexture = loadTexture("over.jpg");
	mainTexture = loadTexture("main2.jpg");
	backTexture = loadTexture("back.jpg");
	spongeTexture = loadTexture("spongebob_d.jpg");
	stoneTextre = loadTexture("mrkrabs_d.png");
}

/* 전체적인 Opengl에 이용하는 것들을 초기화하는 함수 */
void GLUT_INIT(int *argcp, char **argv)
{
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("우주를 섭렵한 스펀지밥");

	glEnable( GL_TEXTURE_2D );

	texture_init();
	GLUT_CALL_FUNC();
	OTHER_INIT();
}

/* GLUT_INIT에서 초기화하고 기타 나머지를 초기화하는 함수 */
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

/* 캐릭터인 스펀지밥을 화면에 출력하는 함수. */
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

/* 게임 실행 중 배경화면을 설정하는 함수 */
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

/* 게임중 돌인 집게사장을 화면에 출력하고 이동해주는 함수 */
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
		//printf("죽음");
		menu = 3;
	}

}

/* 게임 중 돌인 집게사장을 화면에 출력하고 그 뒤에 이어서 또 다른 집게사장을 출력하는 함수 */
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
		//printf("죽음22\n");
		menu = 3;
	}

}

/* 화면에 그리는 함수. 모든 그려주는것은 이 함수안에 넣어서 OpenGL은 이 함수를 부름 */
void display()
{
	static float Light0Pos[]={10.0, 10.0, 10.0, 10.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0,0,0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);
	backGround();

	// 메뉴를 그리기 위한 것
	if (menu == 1)
	{
		mainMenu();
		
	}
	else if (menu == 2)
	{	
		score = score + (delta*3);

		// 죽었을때 표시하기 위해서
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

/* 화면의 크기를 지정하는 함수 */
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

/* 메인 함수 */
int main(int argc, char **argv)
{
	//printf("%d", menu);


	GLUT_INIT(&argc, argv);
	glutMouseFunc(MouseButton);

	glutMainLoop();

	return 0;

}
