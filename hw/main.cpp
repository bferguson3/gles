//#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include "bcm_host.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

#define TRUE 1
#define FALSE 0

typedef uint32_t u32;

typedef struct {
    GLuint programObject;
} UserData;

typedef struct Target_State {
    u32 width;
    u32 height;

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    EGL_DISPMANX_WINDOW_T nativeWindow;
    UserData* user_data;
    void(*draw_func)(struct Target_state*);

} Target_State;

Target_State state;
Target_State* p_state = &state;

static const EGLint attribute_list[] = { \
	EGL_RED_SIZE, 8,\
	EGL_GREEN_SIZE, 8,\
	EGL_BLUE_SIZE, 8,\
	EGL_ALPHA_SIZE, 8,\
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE
};

static const EGLint context_attributes[] = { \
	EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
};

GLuint LoadShader(GLenum type, const char* shaderSrc)
{
    GLuint _shader = glCreateShader(type);
    if(_shader == 0) return 0;

    glShaderSource(_shader, 1, &shaderSrc, NULL);
    glCompileShader(_shader);

    GLint compile_status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &compile_status);
    if(!compile_status)
    {
	GLint infolen = 0;
	glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &infolen);
	if(infolen > 0) {
	    char* log = (char*) malloc(sizeof(char) * infolen);
	    glGetShaderInfoLog(_shader, infolen, NULL, log);
	    fprintf(stderr, "Error compiling shader:\n%s\n", log);
	    free(log);
	}
	glDeleteShader(_shader);
	return 0;
    }
    return _shader;
}

int main(int argc, char* argv[])
{
    //std::string mystring;
    //std::cin >> mystring;
    //std::cout << "Hello " << mystring;
    printf("%s\n", "Hello World");
    return 0;
}
