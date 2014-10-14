//
//  Macro.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef graphics_practice_Macro_h
#define graphics_practice_Macro_h

#include <GLUT/GLUT.h>
#include "../Math/Vector3.h"

#include <stdlib.h>
#include <sys/time.h>

#define SAFE_DELETE(p) if( (p) != NULL ) delete (p); (p) = NULL;

void GLVertexByVector3(Vector3 &v);
long GetMillisecond(struct timeval tv);
void RenderBitmapString(void* font, float x, float y, const char *string);
double Random0to1();
double RandomRangeDouble(double start, double end);
int RandomRangeInt(int start, int end);

#endif
