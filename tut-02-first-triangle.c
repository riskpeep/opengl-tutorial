/*
 * opengl-tutorial.org
 *
 * Tutorial 2
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

#include "loadShader.h"

int main()
{
    GLFWwindow *window; /* In the accompanying source code, this variable is global for simplicity */
    GLuint VertexArrayID;
    GLuint programID = 0;

    /* An array of 3 vectors which represent 3 vertices */
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    /* This will identify our vertex buffer */
    GLuint vertexbuffer;

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

    /* Create a VAO */
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    /* Generate 1 buffer, put the resulting identifier in vertexbuffer */
    glGenBuffers( 1, &vertexbuffer );

    /* The following commands will talk about our 'vertexbuffer' buffer */
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );

    /* Give our vertices to OpenGL */
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    /* Ensure we can capture the escape key being pressed below */
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

    /* Create and compile our GLSL program from the shaders */
    programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    do{
        /* Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so its there nonetheless. */
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        /* Use our shader */
        glUseProgram(programID);

        /* 1st attribute buffer : vertices */
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer );
        glVertexAttribPointer(
            0,          /* attribute 0. No particular reason for 0, but it must match the layout in the shader. */
            3,          /* size */
            GL_FLOAT,   /* type */
            GL_FALSE,   /* normalized? */
            0,          /* stride */
            (void *)0   /* array buffer offset */
        );
        /* Draw the triangle */
        glDrawArrays( GL_TRIANGLES, 0, 3); /* Starting from vertex 0; 3 vertices total -> 1 triangle */
        glDisableVertexAttribArray(0);

        /* Swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    } /* Check if the ESC key was pressed or the window was closed */
    while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose( window ) == 0 );

    return 0;
}
