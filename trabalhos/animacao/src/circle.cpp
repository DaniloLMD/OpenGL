#include "../include/circle.hpp"

void draw_circle(Circle c, bool filled)
{
    GLdouble points = 100;
    GLdouble delTheta = (2.0 * PI) / points;
    GLdouble theta = 0.0;

    glBegin( (filled) ? GL_POLYGON : GL_LINE_LOOP);
    {   
        for(int i = 0; i <= points; i++, theta += delTheta )
        {
            glVertex2f(c.center.x + c.rad * cos(theta), c.center.y + c.rad * sin(theta));
        }
    }

    glEnd();
}