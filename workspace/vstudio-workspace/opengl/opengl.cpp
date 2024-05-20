#include <GL/glut.h>

#define CAM_SENS 0.2f

GLboolean wireframe = GL_TRUE;
GLboolean rotate = GL_FALSE;

GLfloat camRX = 0.f;
GLfloat camRY = 0.f;
GLfloat camTX = 0.f;
GLfloat camTY = 0.f;

GLint prevX = 0;
GLint prevY = 0;
GLint currX = 0;
GLint currY = 0;

void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat r, GLfloat g, GLfloat b) {
	GLUquadric* quad;
	quad = gluNewQuadric();

	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(r, g, b);

	if (wireframe) {
		gluQuadricDrawStyle(quad, GLU_LINE);
	}
	else {
		gluQuadricDrawStyle(quad, GLU_FILL);
	}

	gluSphere(quad, radius, 20, 20);
	glPopMatrix();
	gluDeleteQuadric(quad);
}

void drawCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLfloat r, GLfloat g, GLfloat b) {
	GLUquadric* quad;
	quad = gluNewQuadric();

	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(r, g, b);
	if (wireframe) {
		gluQuadricDrawStyle(quad, GLU_LINE);
	}
	else {
		gluQuadricDrawStyle(quad, GLU_FILL);
	}
	gluCylinder(quad, radius, radius, height, 20, 20);
	glPopMatrix();
	gluDeleteQuadric(quad);
}

void keyboard(unsigned char key, GLint x, GLint y) {
	if (key == 'w' || key == 'W') {
		wireframe = !wireframe;
		glutPostRedisplay();
	}
}

void mouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rotate = GL_TRUE;
		prevX = currX = x;
		prevY = currY = y;
	}
	else {
		rotate = GL_FALSE;
	}
}

void motion(GLint x, GLint y) {
	if (rotate == GL_TRUE) {
		currX = x;
		currY = y;

		if (currX != prevX || currY != prevY) {
			camRX += (currX - prevX) * CAM_SENS;
			camRY += (currY - prevY) * CAM_SENS;

			prevX = currX;
			prevY = currY;
		}
	}

	glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); {
		glRotatef(camRX, 0.f, 0.1f, 0.f);
		glRotatef(camRY, 0.1f, 0.f, 0.f);

		drawSphere(0.0, 0.8, 0.0, 0.1, 1.0, 0.0, 0.0); // head
		
		drawCylinder(0.0, 0.8, 0.1, 0.1, 0.5, 0.0, 1.0, 0.0); // body

		drawCylinder(0.12, 0.8, 0.1, 0.02, 0.25, 0.0, 0.0, 1.0); // upper arm 1
		drawCylinder(0.12, 0.8, 0.35, 0.02, 0.25, 0.0, 1.0, 1.0); // lower arm 1

		drawCylinder(-0.12, 0.8, 0.1, 0.02, 0.25, 0.0, 0.0, 1.0); // upper arm 2
		drawCylinder(-0.12, 0.8, 0.35, 0.02, 0.25, 0.0, 1.0, 1.0); // lower arm 2

		drawCylinder(0.05, 0.8, 0.6, 0.05, 0.25, 1.0, 0.0, 1.0); // upper leg 1
		drawCylinder(0.05, 0.8, 0.85, 0.05, 0.25, 0.5, 1.0, 0.5); // lower leg 1

		drawCylinder(-0.05, 0.8, 0.6, 0.05, 0.25, 1.0, 0.0, 1.0); // upper leg 2
		drawCylinder(-0.05, 0.8, 0.85, 0.05, 0.25, 0.5, 1.0, 0.5); // lower leg 2


	} glPopMatrix();
	glFlush();
}

GLint main(GLint argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Robot");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}