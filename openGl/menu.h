#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/FreeImage.h>
#include "texture.h"

int menu = 1;

GLuint overTexture;
GLuint mainTexture;

/* 메인 메뉴를 구성하는 함수 */
void mainMenu()
{
	glPushMatrix();
	//printf("%d\n", mainTexture);
	glRotatef(30, 0, 1, 0);
	glRotatef(30, -0.5, 0, 0);
	//glTranslatef(0.0f, 0.0f, -2.0f);
	//static float Light0Pos[]={-10.0, 10.0, 10.0, 10.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);

	glBindTexture(GL_TEXTURE_2D, mainTexture);

	glBegin( GL_QUADS );
	glTexCoord3f( 0.0f, 0.0f, 0.0f );		glVertex3f( -2.6, -2.6, 0.0 );
	glTexCoord3f( 1.0f, 0.0f, 0.0f );		glVertex3f( 2.6, -2.6, 0.0 );
	glTexCoord3f( 1.0f, 1.0f, 0.0f );		glVertex3f( 2.6, 2.6, 0.0 );
	glTexCoord3f( 0.0f, 1.0f, 0.0f );		glVertex3f( -2.6, 2.6, 0.0);
	glEnd();

	glPopMatrix();
}


/* 게임 오버 화면을 구성하는 함수 */
void gameOverSecne()
{
	//printf("%d\n", overTexture);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glPushMatrix();

	glRotatef(30, 0, 1, 0);
	glRotatef(30, -0.5, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, overTexture);

	glBegin( GL_QUADS );
	glTexCoord3f( 0.0f, 0.0f, 0.0f );		glVertex3f( -2.6, -2.6, 0.0 );
	glTexCoord3f( 1.0f, 0.0f, 0.0f );		glVertex3f( 2.6, -2.6, 0.0 );
	glTexCoord3f( 1.0f, 1.0f, 0.0f );		glVertex3f( 2.6, 2.6, 0.0 );
	glTexCoord3f( 0.0f, 1.0f, 0.0f );		glVertex3f( -2.6, 2.6, 0.0);
	glEnd();


	glPopMatrix();

}

#endif