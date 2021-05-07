#include "Angel.h"
#include "Mesh.h"
#include "glui.h"

typedef Angel::vec4  point4;
GLuint vao;

/*Rotation of teapot*/
float theta_teapot = 30;
GLint thetaLoc_teapot;
float teapot_direction = -0.1; /*counter clockwise*/
float speed = 1.0;
GLuint  model_view;	// model-view matrix uniform shader variable location
GLuint  projection;	// projection matrix uniform shader variable location
GLfloat fovy = 30.0;// Field-of-view in Y direction angle (in degrees)
GLfloat aspect;		// Viewport aspect ratio
// Projection transformation parameters
GLfloat zNear = 0.5;					
GLfloat zFar = 5.0;		
float lx = 0.0, ly = 0.0;
const GLfloat  dr = 5.0 * DegreesToRadians;
// Viewing transformation parameters
GLfloat radius = 2.0;
GLfloat theta = 0.0 - 3 * dr;
GLfloat phi = 0.0 - 10 * dr;
/*If object == 1.0, the object is teapot*/
float object;
GLint objectLoc;

//Declare the Mesh objects and variable for vertexData
Mesh teapot;
std::vector<vec3> teapotData;

//Vertices of the surface rectangle
GLfloat RecVertices[]{
	-0.7f, 0.0f, -0.4f,		// Top-left
	0.7f, 0.0f, -0.4f,		// Top-right
	0.8f, -0.8f, -0.4f,		// Bottom-right
	0.8f, -0.8f, -0.4f,		// Bottom-right
	-0.8f, -0.8f, -0.4f,	// Bottom-left
	-0.7f, 0.0f, -0.4f		// Top-left
};

std::vector<vec3> surfaceData;

//Draw the surface
void drawSurface(){
	int i;
	for (i = 0; i < 3*6; i += 3) {
		surfaceData.push_back(vec3(RecVertices[i], RecVertices[i + 1], RecVertices[i + 2]));
	}
}
//----------------------------------------------------------------------------

//Load 3D models-Mesh function
static void Load3DModel(){
	teapot.LoadObjModel("teapot.smf");	//load 3D teapot in smf formate
	teapotData = teapot.returnMesh();	//return the vertex data of mesh
}
//----------------------------------------------------------------------------

//OpenGL initialization
void init(){
	//Load Teapot Model
	Load3DModel();
	//Draw the surface
	drawSurface();
	
	//Generate VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);				//Generate VBO names
	glBindBuffer(GL_ARRAY_BUFFER, buffer);	//Bind a specific VBO
	//Load data into VBO
	glBufferData(GL_ARRAY_BUFFER, (teapotData.size() * sizeof(vec3) + surfaceData.size() * sizeof(vec3)), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, teapotData.size() * sizeof(vec3), teapotData.data());
	glBufferSubData(GL_ARRAY_BUFFER, teapotData.size() * sizeof(vec3), surfaceData.size() * sizeof(vec3), surfaceData.data());
	
	//Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	//Set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	//connect the xyz to the "vPosition" attribute of the vertex shader
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	model_view = glGetUniformLocation(program, "model_view");
	projection = glGetUniformLocation(program, "projection");
	objectLoc = glGetUniformLocation(program, "object");
	thetaLoc_teapot = glGetUniformLocation(program, "theta_teapot");

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);	
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
//----------------------------------------------------------------------------

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Camera settings
	point4  eye(radius*sin(theta)*cos(phi)-0.1, radius*sin(theta)*sin(phi)-0.1, radius*cos(theta)-0.3, 1.0);
	point4  at(lx, ly, 0.0, 1.0);
	vec4    up(0.0, 1.0, 0.0, 0.0);

	mat4  mv = LookAt(eye, at, up);		
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	if (fovy < 0)	fovy = 0;
	if (fovy > 90)	fovy = 90;
	
	mat4  p = Perspective(fovy, aspect, zNear, zFar);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);
	glUniform1f(thetaLoc_teapot, theta_teapot);

	object = 0.0;/*Surface*/
	glUniform1f(objectLoc, object);
	glDrawArrays(GL_TRIANGLE_FAN, teapotData.size(), surfaceData.size());
	
	object = 1.0;/*Teapot*/
	glUniform1f(objectLoc, object);
	glDrawArrays(GL_TRIANGLES, 0, teapotData.size());
	
	glutSwapBuffers();
}
//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'z': zNear *= 1.1; zFar *= 1.1; break;
	case 'Z': zNear *= 0.9; zFar *= 0.9; break;
	case 'r': radius *= 2.0; break;
	case 'R': radius *= 0.5; break;
	case 'o': theta += dr; break;
	case 'O': theta -= dr; break;
	case 'p': phi += dr; break;
	case 'P': phi -= dr; break;
	case 't':teapot_direction = -teapot_direction; break;	
	case '-':speed -= 1.0; break;
	case '+':speed += 1.0; break;
	case ' ':  // reset values to their defaults
		zNear = 0.5;
		zFar = 5.0;
		radius = 2.0;
		theta = 0.0;
		phi = 0.0;
		break;
	}
	if (speed <= 0) speed = 0;
	
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

void keyboard2(int key, int x, int y){
	if (key == GLUT_KEY_UP) {
		fovy -= 1;						/* forward along the global z-axis direction */	
	}else if (key == GLUT_KEY_DOWN) {
		fovy += 1;						/* backward along the global z-axis direction */	
	}else if (key == GLUT_KEY_RIGHT) {
		lx += 0.05;						/* right along the global x-axis direction */	
	}else if (key == GLUT_KEY_LEFT) {
		lx -= 0.05;						/* left along the global x-axis direction */	
	}else if (key == GLUT_KEY_PAGE_UP) {
		ly += 0.05;						/* upward along the global y-axis direction */
	}else if (key == GLUT_KEY_PAGE_DOWN) {
		ly -= 0.05;						/* downward along the global y-axis direction */
	}
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

void reshape(int width, int height){
	glViewport(0, 0, width, height);
	aspect = GLfloat(width) / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-aspect*.08, aspect*.08, -.08, .08, .1, 15.0);
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

void idle(void){
	theta_teapot -= teapot_direction * speed;
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(850,550);	//Specify window properties

	// If you are using freeglut, the next two lines will check if 
	// the code is truly 3.1. Otherwise, comment them out
	glutInitContextVersion(3, 1);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Utah Teapot");
	glewExperimental = GL_TRUE;
	glewInit();
	init();

	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard2);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);	
	glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();
	return 0;
}