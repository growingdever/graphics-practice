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
#include <fstream>

#include "SOIL.h"

#include "MyImage.h"
#include "Sprite.h"
#include "Cube.h"
#include "RubiksCube3.h"

#define WINDOW_TITLE "Loki's Graphics Practice"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;

GLfloat	xrot;				// X Rotation
GLfloat	yrot;				// Y Rotation
GLfloat zrot;               // Z Rotation
GLfloat xspeed;				// X Rotation Speed
GLfloat yspeed;				// Y Rotation Speed

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 50.0f, 1.0f };
bool	light;				// Lighting ON/OFF
bool    blend;

#define MAX_MODE_COUNT 3
const int MODE_POSITION = 0;
const int MODE_ROTATION = 1;
const int MODE_SCALE = 2;
int mode;

Vector3 cameraPosition;
Vector3 cameraRotation;
Vector3 cameraScale(1.0f, 1.0f, 1.0f);

Sprite *spriteGrass = NULL;
Cube *cube = NULL;


void LogCameraStatus() {
    cout << "camera position - (" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")" << endl;
    cout << "camera rotation - (" << cameraRotation.x << ", " << cameraRotation.y << ", " << cameraRotation.z << ")" << endl;
    cout << "camera scale - (" << cameraScale.x << ", " << cameraScale.y << ", " << cameraScale.z << ")" << endl;
}


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
	gluPerspective(45, ratio, 1, 1000);
    
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();
    
    // roughly camera setting
    glRotatef( cameraRotation.x, 1.0f, 0.0f, 0.0f );
    glRotatef( cameraRotation.y, 0.0f, 1.0f, 0.0f );
    glRotatef( cameraRotation.z, 0.0f, 0.0f, 1.0f );
    glScalef( cameraScale.x, cameraScale.y, cameraScale.z );
    glTranslatef( -cameraPosition.x, -cameraPosition.y, -cameraPosition.z );
    
    spriteGrass->Draw();
    cube->Draw();
    
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
    
    if (key == 'l' || key == 'L' ) {
        light=!light;
        if (!light)
        {
            glDisable(GL_LIGHTING);
            cout << "light off" << endl;
        }
        else
        {
            glEnable(GL_LIGHTING);
            cout << "light on" << endl;
        }
    }
    
    if ( key == 'b' || key == 'B' ) {
        blend = !blend;
        if(blend)
        {
            glEnable(GL_BLEND);			// Turn Blending On
            glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off
            cout << "blend on" << endl;
        }
        else
        {
            glDisable(GL_BLEND);		// Turn Blending Off
            glEnable(GL_DEPTH_TEST);	// Turn Depth Testing On
            cout << "blend off" << endl;
        }
    }
    
    if ( key == 'm' || key == 'M' ) {
        mode = ( mode + 1 ) % MAX_MODE_COUNT;
    }
    
    if( key == 'z' || key == 'Z' ) {
        switch (mode) {
            case MODE_POSITION:
                cameraPosition.z -= 5.0f;
                break;
            case MODE_ROTATION:
                cameraRotation.z -= 5.0f;
                break;
            case MODE_SCALE:
                cameraScale.z -= 0.1f;
                break;
        }
        
        LogCameraStatus();
    }
    if( key == 'x' || key == 'X' ) {
        switch (mode) {
            case MODE_POSITION:
                cameraPosition.z += 5.0f;
                break;
            case MODE_ROTATION:
                cameraRotation.z += 5.0f;
                break;
            case MODE_SCALE:
                cameraScale.z += 0.1f;
                break;
        }
        
        LogCameraStatus();
    }
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_LEFT:
            switch (mode) {
                case MODE_POSITION:
                    cameraPosition.x -= 5.0f;
                    break;
                case MODE_ROTATION:
                    cameraRotation.y -= 5.0f;
                    break;
            }
            break;
        case GLUT_KEY_RIGHT:
            switch (mode) {
                case MODE_POSITION:
                    cameraPosition.x += 5.0f;
                    break;
                case MODE_ROTATION:
                    cameraRotation.y += 5.0f;
                    break;
            }
            break;
        case GLUT_KEY_UP:
            switch (mode) {
                case MODE_POSITION:
                    cameraPosition.y += 5.0f;
                    break;
                case MODE_ROTATION:
                    cameraRotation.x -= 5.0f;
                    break;
            }
            break;
        case GLUT_KEY_DOWN:
            switch (mode) {
                case MODE_POSITION:
                    cameraPosition.y -= 5.0f;
                    break;
                case MODE_ROTATION:
                    cameraRotation.x += 5.0f;
                    break;
            }
            break;
	}
    

}

void MainLoop() {
    xrot += 0.3f;
    yrot += 0.2f;
    zrot += 0.4f;
    
    cube->SetRotation( Vector3( xrot, yrot, zrot ) );
    
    glutPostRedisplay();
}

bool LoadGLTextures() {
    spriteGrass = Sprite::Create("Textures/grass.jpg");
    if( spriteGrass == NULL ) {
        return false;
    }
    
    spriteGrass->SetPosition( Vector3( 0, 0, 0 ) );
    spriteGrass->SetRotation( Vector3( -90, 0, 0 ) );
    
    MyImage *boxImage = MyImage::LoadImage("Textures/Crate.bmp");
    cube = Cube::Create( boxImage->GetTexture(), 100.0f );
    cube->SetPosition( Vector3( 0, 100, -300 ) );
    delete boxImage;
    
    return true;
}

bool InitGL() {
    if (!LoadGLTextures())                          // Jump To Texture Loading Routine ( NEW )
    {
        return false;                           // If Texture Didn't Load Return FALSE ( NEW )
    }
    
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One
    
    // set camera position
    cameraPosition.Set( 0, 100, 20 );
    
    return true;
}



int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   	glutCreateWindow(WINDOW_TITLE);
    
	// register callbacks
	glutDisplayFunc(&renderScene);
	glutReshapeFunc(&changeSize);
    
    // set my main loop callback function
    glutIdleFunc(&MainLoop);
    
    // here are the new entries
	glutKeyboardFunc(&processNormalKeys);
	glutSpecialFunc(&processSpecialKeys);
    
    if( ! InitGL() ) {
        return 0;
    }
    
	// enter GLUT event processing loop
	glutMainLoop();
    
	return 0;
}
