#ifndef __JOY_H__
#define __JOY_H__
#include <stdio.h>

enum SHAPE_TYPE {
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,
    SHAPE_GROUP
};

typedef struct {
    enum SHAPE_TYPE type;
    float x;
    float y;
    float r;
    float w;
    float h;
    float stroke_width;
    char * stroke;
    char * fill;
} shape;

shape circle(float x, float y, float r);
shape rectangle(float x, float y, float w, float h);
void show(shape s);

#endif