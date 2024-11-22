#include <math.h>
#include <GL/glut.h>

#include "point.hpp"

double rad(double ang);


void translate(Point v[3], int size, GLfloat x, GLfloat y, GLfloat z);
void rotate(Point p[], int size, double angX, double angY, double angZ);

Point center(Point v[], int size);