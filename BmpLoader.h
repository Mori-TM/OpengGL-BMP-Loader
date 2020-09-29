#ifndef _BMPLOADER_H_
#define _BMPLOADER_H_
#include <GL/freeglut.h>
#include <stdio.h>

GLuint texture[32];

GLuint LoadTexture(const char * filename)
{
	int width;
    int height;
    unsigned char info[54];
    unsigned char* data;
    
    FILE* f = fopen(filename, "rb");
    fread(info, sizeof(unsigned char), 54, f); 
    width = *(int*)&info[18];
    height = *(int*)&info[22];
    
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
	
	FILE* file;
	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	data = (unsigned char*)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);	
	
	for(int i = 0; i < width * height ; ++i)
	{
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];
		
		data[index] = R;
		data[index+2] = B;
	}

	glGenTextures(1, &texture[32]);
	glBindTexture(GL_TEXTURE_2D, texture[32]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height,GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data); 
	return texture[32];
}

void FreeTexture(GLuint texture[32])
{
	glDeleteTextures(1, &texture[32]);	
}

#endif
