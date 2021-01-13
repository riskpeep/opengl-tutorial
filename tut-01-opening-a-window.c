/*
 * opengl-tutorial.org
 *
 * Tutorial 1
 *
 */

/* Include standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Include GLEW.  Always include GLEW before gl.h and glfw3.h, since it is a 
 * bit magic. */
#include <GL/glew.h>

/* Include GLFW for window and keyboard handling */
#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow *window; /* In the accompanying source code, this variable is global for simplicity */

    /* Initialize GLFW */
    glewExperimental = true; /* Needed for core profile */
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); /* 4x anitaliasing */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* We want OpenGL 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    /*glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* We don't want the old OpenGL */

    /* Open a window and create is OpenGL context */
    window = glfwCreateWindow( 1024, 786, "Tutorial 01", NULL, NULL );
    if( window == NULL ) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); /* Initialize GLEW */
    glewExperimental=true; /* Needed in core profile */
    if( glewInit() != GLEW_OK ) {
        fprintf( stderr, "Failed to initialize GLEW\n" );
        return -1;
    }

    /* Ensure we can capture the escape key being pressed below */
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

    do{
        /* Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so its there nonetheless. */
        glClear( GL_COLOR_BUFFER_BIT );

        /* Draw nothing, see you in tutorial 2! */

        /* Swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    } /* Check if the ESC key was pressed or the window was closed */
    while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose( window ) == 0 );

    return 0;
}
