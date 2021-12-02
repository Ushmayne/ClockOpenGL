    
#include <ctime>
#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "main.h"
#include<math.h>
#include <time.h>
#include <sys/timeb.h>
#include <ctime>


#define HOUR_HAND_LENGTH 100.0
#define MINUTE_HAND_LENGTH 150
#define SECOND_HAND_LENGTH 160
#define CLOCK_RADIUS 200.0
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

double hourH = 0, minH = 0, secH = 0;

typedef struct Point {
    double x, y;
}point;


void drawPoint(point p) {
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();

}


void drawLine(double y, double ang) {
    glVertex2f(400, 300);
    glVertex2f(y * cos(ang)+400, y * sin(ang)+300);
}

void drawMarks() {
    point sp, ep, p;
    int count = 0;
    double i = M_PI / 6.0;
    sp.x = 0, sp.y = 0;
    ep.x = 0, ep.y = CLOCK_RADIUS;
    glPointSize(10.0);
    drawPoint(sp);
    for (i = 0; i <= 2 * M_PI; i += M_PI / 30.0) {
        if (i == M_PI / 2.0) {
            p.x = CLOCK_RADIUS;
        }
        else if (i == 3 * M_PI / 2.0) {
            p.x = -CLOCK_RADIUS;
        }
        else {
            p.x = ep.y * sin(i) + 400;
        }
        p.y = ep.y * cos(i) + 300;
        if (count % 5 == 0) {
            glPointSize(7.0);
            drawPoint(p);

        }
        else {
            glPointSize(3.0);
            drawPoint(p);
        }
        count++;
    }

}

void drawclock() {

    struct timeb tb;
    time_t tim = time(0);
    struct tm* t;
    t = localtime(&tim);
    ftime(&tb);

    secH = (double)(t->tm_sec + (double)tb.millitm / 1000.0) / 30.0 * M_PI;
    minH = (double)(t->tm_min) / 30.0 * M_PI + secH / 60.0;
    hourH = (double)(t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour) / 6.0 * M_PI + minH / 12.0;
    
    drawMarks();


    glLineWidth(6.0);
    glBegin(GL_LINES);
    drawLine(HOUR_HAND_LENGTH, -hourH + M_PI / 2);
    glEnd();
    glLineWidth(3.0);
    glBegin(GL_LINES);
    drawLine(MINUTE_HAND_LENGTH, -minH + M_PI / 2);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINES);
    drawLine(SECOND_HAND_LENGTH, -secH + M_PI / 2);
    glEnd();
}




int main(int argc, char* argv[])
{

    SDL_Window* window = InitializeAndCreateSDLWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    SDL_Event windowEvent;
    while (1)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
            if (windowEvent.type == SDL_KEYUP &&
                windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
        }

        glClear(GL_COLOR_BUFFER_BIT);

       // DrawCircle(400, 300, 200);
        //drawMarks();
        drawclock();
        glFlush();

        SDL_GL_SwapWindow(window);
    }

    CleanUpSDL();

    return 0;
}

