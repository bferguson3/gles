#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <GL/glut.h> // glutLeaveMainLoop
#include <stdio.h>
#include <math.h>
#include <string.h>

#define ASCII_BS 8
#define ASCII_ESC 27
#define ASCII_DEL 127
#define TRUE 1
#define FALSE 0
#define bool int 
#define false FALSE 
#define true TRUE 

#define VEC3(n) (n.x),(n.y),(n.z)
#define VEC4(n) (n.r),(n.g),(n.b),(n.a)

float spd = 0.1;
float red = 1.0f, blue = 1.0f, green = 1.0f;
typedef unsigned char u8;
GLuint shader_program, vertex_shader, fragment_shader;

typedef struct _vec3 {
    float x;
    float y;
    float z;
} vec3;

typedef struct _vec4 { 
    float r;
    float g;
    float b;
    float a;
} vec4;

typedef struct _camera {
    float h;
    float v;
    float delta_h;
    float delta_v;
    float delta_pos;
    vec3 dir;
    vec3 pos;
} Camera;

Camera playerCam;

void set_camera_pos(Camera* c)
{
    c->pos.x += c->delta_pos * c->dir.x * spd;
    c->pos.z += c->delta_pos * c->dir.z * spd;
    c->pos.y += c->delta_pos * c->dir.y * spd;
}

void set_camera_dir(Camera* c)
{
    c->h += c->delta_h;
    c->v += c->delta_v;
    c->dir.x = sin(c->h);
    c->dir.z = -cos(c->h);
    c->dir.y = sin(c->v);
}

vec3 color_white = { 1.0, 1.0, 1.0 };

void draw_snowman()
{
    glColor3f(VEC3(color_white));
    // body 
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);
    // head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);
    //eyes
    glPushMatrix(); // offset from center of head
     glColor3f(0.0f, 0.0f, 0.0f);
     glTranslatef(0.05f, 0.1f, 0.18f);
     glutSolidSphere(0.05f, 10, 10);
     glTranslatef(-0.1f, 0, 0);
     glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    // nose
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.5f, 10.0f, 2.0f);
}

void DRAW()
{
    // Update
    if(playerCam.delta_v != 0) set_camera_dir(&playerCam);
    if(playerCam.delta_h != 0) set_camera_dir(&playerCam);
    if(playerCam.delta_pos != 0) set_camera_pos(&playerCam);
    
    // clear screen buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //glUseProgram(shader_program);
    GLint clr = glGetUniformLocation(shader_program, "incolor");
    glUniform3f(clr, VEC3(color_white));
    
    // reset transformation
    glLoadIdentity();
    // camera position and angle:
    gluLookAt( playerCam.pos.x, playerCam.pos.y, playerCam.pos.z, /* eye pos */
               playerCam.pos.x + playerCam.dir.x, /* ref pos */\
                playerCam.pos.y + playerCam.dir.y,\
                playerCam.pos.z + playerCam.dir.z,\
               0.0f, 1.0f, 0.0f); /* up vector */

    //glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f);
		glVertex3f(1.0f, 1.0f, -5.0f);
    glEnd();
    
	for(int i = -3; i < 3; i++)
		for(int j= -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0.0f, j * 10.0);
			draw_snowman();
			glPopMatrix();
		}
    
    //glFlush(); <- single buffer
    glutSwapBuffers();
}

void KEY_RELEASED(u8 key, int x, int y)
{
    switch(key){
        case 's':
        case 'S':
        case 'W':
        case 'w':
            playerCam.delta_pos = 0;
            break;
    }
}

void KEY_PRESSED(u8 key, int x, int y)
{
    int m = glutGetModifiers();

    switch(key)
    {
        case ASCII_ESC:
            printf("ESC\n");
            glutLeaveMainLoop();
            break;
        case 0x31:
            if(m == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT))
                printf("Ctrl+Alt 1\n", m);
            else if(m & GLUT_ACTIVE_CTRL)
                printf("Ctrl 1\n", m);
            else if(m & GLUT_ACTIVE_ALT)
                printf("Alt 1\n", m);
            break;
        case 'w':
        case 'W':
            playerCam.delta_pos = spd;
            break;
        case 's':
        case 'S':
            playerCam.delta_pos = -spd;
            break;

    }  
}

void EXKEY_PRESSED(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT : 
            playerCam.delta_h = -0.01f; 
            break;
		case GLUT_KEY_RIGHT : 
            playerCam.delta_h = 0.01f; 
            break;
		case GLUT_KEY_UP :
            playerCam.delta_v = 0.01f;
            break;
		case GLUT_KEY_DOWN : 
            playerCam.delta_v = -0.01f;
            break;
	}
}

void EXKEY_RELEASED(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : 
            playerCam.delta_h = 0.0f;
            break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : 
            playerCam.delta_v = 0;
            break;
	}
}

void RESIZE(int w, int h)
{
    if(h == 0) h = 1;
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset proj matrix
    gluPerspective(45, ratio, 1, 100); /* Y fov, X fov (aspect), near clip, far clip */
    glMatrixMode(GL_MODELVIEW); // default view
}


void setup_camera(Camera* c)
{
    c->h = 0;
    c->v = 0;
    c->delta_h = 0;
    c->delta_v = 0;
    c->delta_pos = 0;
    c->dir.x = 0.0f;
    c->dir.y = 0.0f;
    c->dir.z = -1.0f;
    c->pos.x = 0.0f;
    c->pos.y = 1.0f;
    c->pos.z = 5.0f;
}

void print_shader_debug(GLuint obj)
{
    GLint length;
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
    char* log = malloc(sizeof(char) * length);
    glGetShaderInfoLog(obj, length, &length, &log[0]);
    printf("%s\n",log);
    free(log);
}

bool check_shader_compile_status(GLuint obj) {
    GLint status;
    glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) 
    {
        print_shader_debug(obj);
        return false;
    }
    return true;
}

int check_program_link_status(GLuint obj) {
    GLint status;
    glGetProgramiv(obj, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) 
    {
        print_shader_debug(obj);
        return FALSE;
    }
    return TRUE;
}

int filesize(char* fname)
{
    FILE* f = fopen(fname, "rb");
    fseek(f, 0, SEEK_END);
    int fsz = ftell(f);
    fclose(f);
    return fsz;
}

char* readTextFile(char* fname)
{
    FILE* f;
    int fsz = filesize(fname);
    char* mystr = (char*)malloc(fsz);
    f = fopen(fname, "rb");
    fread(mystr, fsz, 1, f);
    fclose(f);
    return mystr;
}

int LOAD_SHADERS()
{
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_source = readTextFile("shaders/default.vs");
    int len = filesize("shaders/default.vs");
    glShaderSource(vertex_shader, 1, &vertex_source, &len);
    glCompileShader(vertex_shader);
    if(!check_shader_compile_status(vertex_shader)) 
    {
        printf("Vertex shader failed to compile.\n");    
        return FALSE;
    }
    
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_source = readTextFile("shaders/default.fs");
    len = filesize("shaders/default.fs");
    glShaderSource(fragment_shader, 1, &fragment_source, &len);
    glCompileShader(fragment_shader);
    if(!check_shader_compile_status(fragment_shader)) 
    {
        printf("Fragment shader failed to compile.\n");
        return FALSE;
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    
    glLinkProgram(shader_program);
    if(!check_program_link_status(shader_program)) 
    {
        printf("failed\n");
        return FALSE;
    }
    else
    {
        printf("Shaders loaded successfully.\n");
    }
    // VERTEX SHADER: RESET INCOMING VARIABLE POINTER SIZE
    // position attribute
    // Index, Size, Type, Normalized, Stride, Pointer
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0);
    //glEnableVertexAttribArray(0);
    return TRUE;
}    

int main(int argc, char** argv)
{
    
    // Window:
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Hello Triangle");

    // GL Init:
    GLenum err = glewInit();
    if(GLEW_OK != err){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    // Print hardware info
    printf("This GPU supplied by %s\n", glGetString(GL_VENDOR));
    printf("This GPU supports OpenGL version %s\n", glGetString(GL_VERSION));
    printf("This GPU renders with %s\n", glGetString(GL_RENDERER));
    printf("This GPU supports GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    /*
    // shader test
    */
    if(!LOAD_SHADERS())
        return 1;
    
    // Register callbacks
    glutDisplayFunc(DRAW);
    glutReshapeFunc(RESIZE);
    glutIdleFunc(DRAW);
    glutKeyboardFunc(KEY_PRESSED);
    glutKeyboardUpFunc(KEY_RELEASED);
    glutSpecialFunc(EXKEY_PRESSED);
    //glutIgnoreKeyRepeat(0);
    glutSpecialUpFunc(EXKEY_RELEASED);

    glEnable(GL_DEPTH_TEST);

    // make a camera
    setup_camera(&playerCam);
    
    // App loop 
    glutMainLoop();

    return 1;
}
