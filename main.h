#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>

SDL_Window* InitializeAndCreateSDLWindow(int screenWidth, int screenHeight) {
    // Initializing SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Creating SDL Window


    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Cannot create the sdl window: %s", SDL_GetError());
        return NULL;
    }
    // Creating GL context for the window, it is required for any gl functions to work
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("Cannot create OpenGL context, probably the requested version of OpenGL is not supported on your machine.");
        printf("SDL ERROR: %s", SDL_GetError());
        return NULL;
    }

    // Initialize GLEW
    glewInit();

    // Initialize OpenGL
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set clear color to white
    glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color to black

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(2);

    return window;
}


void CleanUpSDL() {
    SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
    SDL_Quit();
}
