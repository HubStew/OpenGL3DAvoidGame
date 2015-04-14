#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/FreeImage.h>

#include <windows.h>

GLuint texID = -1;

FIBITMAP  *loadImage(const char *filename) {
	FIBITMAP *dib1 = NULL;

	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);

	dib1 = FreeImage_Load(fif, filename, JPEG_DEFAULT);
	if (!dib1) {
		printf("Error opening image");
		exit (0);
	}  
	return dib1;
}

GLuint loadTexture (char* filename) { 
	int x, y;
	int height, width;
	FIBITMAP  *dib1 = NULL;
	RGBQUAD rgbquad;

	FREE_IMAGE_TYPE type;
	BITMAPINFOHEADER *header;

	dib1 = loadImage(filename);

	type = FreeImage_GetImageType(dib1); 
	height = FreeImage_GetHeight(dib1);
	width = FreeImage_GetWidth(dib1);

	header = FreeImage_GetInfoHeader(dib1);

	int scanLineWidh = ((3*width)%4 == 0) ? 3*width : ((3*width)/4)*4+4;
	unsigned char * texImg= (GLubyte*)calloc(height*scanLineWidh, sizeof(GLubyte));
	for (x=0 ; x<width ; x++)
		for (y=0 ; y<height; y++) {
			FreeImage_GetPixelColor(dib1,x,y,&rgbquad);

			texImg[(y*scanLineWidh+3*x)]=((GLubyte*)&rgbquad)[2];
			texImg[(y*scanLineWidh+3*x)+1]=((GLubyte*)&rgbquad)[1];
			texImg[(y*scanLineWidh+3*x)+2]=((GLubyte*)&rgbquad)[0];
		}

		glGenTextures (1, &texID);
		glBindTexture (GL_TEXTURE_2D, texID);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, texImg);
		free(texImg);
		FreeImage_Unload(dib1);
		return texID;
}


#endif