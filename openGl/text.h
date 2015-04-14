
/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees 
and is provided without guarantee or warrantee expressed or 
implied. This program is -not- in the public domain. */

#include <string>
#include <GL/glut.h>

void *font = GLUT_BITMAP_TIMES_ROMAN_24;

/* 글씨를 써줄때 필요한 함수 */
void output(int x, int y, std::string str)
{
	int len, i;
	glRasterPos2f(x, y);

	glColor3f(1.0, 1.0, 1.0);
	len = str.size();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}