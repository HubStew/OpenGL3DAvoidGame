#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include <stdio.h>
#include "menu.h"

int mousePosition = 2;


/* ���콺 Ŭ���� �����ϴ� �Լ� */
void MouseButton(int button,int state,int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
			//printf("left ");
			if (mousePosition > 1 && menu == 2)
				mousePosition--;

			if (menu == 3)
			{
				menu = 1;
				mousePosition = 2;
			}
			else
				menu = 2;
			break;

		case GLUT_RIGHT_BUTTON:
			if (mousePosition < 3 && menu == 2)
				mousePosition++;
			break;
		}
	}

	glutPostRedisplay();
}

#endif