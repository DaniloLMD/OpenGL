#include "../include/circle.hpp"

void draw_circle(Circle c)
{
    GLdouble points = 50;
    GLdouble delTheta = (2.0 * PI) / points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for(int i = 0; i <=50; i++, theta += delTheta )
        {
            glVertex2f(c.center.x + c.rad * cos(theta), c.center.y + c.rad * sin(theta));
        }
    }

    glEnd();
}