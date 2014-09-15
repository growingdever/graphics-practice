//
//  main.cpp
//  graphics-pratice
//
//  Created by loki on 2014. 9. 15..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <stdlib.h>
#include <iostream>

#define WINDOW_TITLE "Loki's Graphics Practice"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;

float tAngle = 0;
float qAngle = 0;


void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
    
    // Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    
	float ratio = w * 1.0 / h;
    
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);
    
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glRotatef( tAngle, 0, 1.0f, 0 );
    
    glBegin(GL_TRIANGLES); // Drawing Using Triangles
    glColor3f(1.0f,0.0f,0.0f); // Set The Color To Red
    glVertex3f( 0.0f, 1.0f, 0.0f); // Top
    glColor3f(0.0f,1.0f,0.0f); // Set The Color To Green
    glVertex3f(-1.0f,-1.0f, 0.0f); // Bottom Left
    glColor3f(0.0f,0.0f,1.0f); // Set The Color To Blue
    glVertex3f( 1.0f,-1.0f, 0.0f); // Bottom Right
    glEnd(); // Finished Drawing The Triangle
    
    glTranslatef(3.0f, 0.0f, 0.0f);
    glRotatef( qAngle, 1.0f, 0, 0 );
    
    glColor3f(0.5f,0.5f,1.0f); // Set The Color To Blue One Time Only
    glBegin(GL_QUADS); // Start Drawing Quads
    glVertex3f(-1.0f, 1.0f, 0.0f); // Left And Up 1 Unit (Top Left)
    glVertex3f( 1.0f, 1.0f, 0.0f); // Right And Up 1 Unit (Top Right)
    glVertex3f( 1.0f,-1.0f, 0.0f); // Right And Down One Unit (Bottom Right)
    glVertex3f(-1.0f,-1.0f, 0.0f); // Left And Down One Unit (Bottom Left)
    glEnd(); // Done Drawing A Quad
    
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_LEFT:
            tAngle -= 10.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            tAngle += 10.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            qAngle += 10.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            qAngle -= 10.0f;
            glutPostRedisplay();
            break;
	}
}


int main(int argc, char **argv) {
    
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   	glutCreateWindow(WINDOW_TITLE);
    
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    
    // here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
    
	// enter GLUT event processing loop
	glutMainLoop();
    
	return 1;
}
