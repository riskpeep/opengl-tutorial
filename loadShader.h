/*
 * opengl-tutorial.org
 *
 * Tutorial 2
 *
 */

/* Include standard headers */
#include <stdio.h>
#include <stdlib.h>

/* Include GLEW.  Always include GLEW before gl.h and glfw3.h, since it is a 
 * bit magic. */
#include <GL/glew.h>

/* Include GLFW for window and keyboard handling */
#include <GLFW/glfw3.h>

GLuint LoadShaders( const char *vertex_file_path, const char *fragment_file_path);
