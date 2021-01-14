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

GLuint LoadShaders( const char *vertex_file_path, const char *fragment_file_path)
{
    /* Create the shaders */
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    /* Vertex Shader vars */
    char *VertexShaderCode;
    FILE *VertexShaderFile;
    unsigned int VertexFileSize = 0;

    /* Fragment Shader vars */
    char *FragmentShaderCode;
    FILE *FragmentShaderFile;
    unsigned int FragmentFileSize = 0;

    /* Complation Vars */
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;
    GLuint ProgramID = 0;

    /* Read the Vertex Shader code from the file */
    VertexShaderFile = fopen( vertex_file_path, "r" );
    if( NULL == VertexShaderFile ) {
        printf("Impossible to open %s.  Are you in the right directory?  Don't forget to read the FAQ!\n", vertex_file_path);
        getchar();
        return 0;
    }

    if( fseek(VertexShaderFile, 0, SEEK_END) != 0) {
        printf("Unable to seek in file %s.  Is the file correctly formatted?  Don't forget to read the FAQ!\n", vertex_file_path);
        getchar();
        return 0;
    }

    VertexFileSize = ftell(VertexShaderFile);
    rewind(VertexShaderFile);
    VertexShaderCode = (char *)malloc(VertexFileSize+1);
    if( NULL == VertexShaderCode ) {
        printf("Unable to read file %s.  Is the file correctly formatted?  Don't forget to read the FAQ!\n", vertex_file_path);
        getchar();
        return 0;
    }
    VertexFileSize = fread(VertexShaderCode, 1, VertexFileSize, VertexShaderFile);
    fclose(VertexShaderFile);
    VertexShaderCode[VertexFileSize] = 0;

    /* Read the Fragment Shader code from the file */
    FragmentShaderFile = fopen( fragment_file_path, "r" );
    if( NULL == FragmentShaderFile ) {
        printf("Impossible to open %s.  Are you in the right directory?  Don't forget to read the FAQ!\n", fragment_file_path);
        getchar();
        free(VertexShaderCode);
        return 0;
    }

    if( fseek(FragmentShaderFile, 0, SEEK_END) != 0) {
        printf("Unable to seek in file %s.  Is the file correctly formatted?  Don't forget to read the FAQ!\n", fragment_file_path);
        getchar();
        free(VertexShaderCode);
        return 0;
    }

    FragmentFileSize = ftell(FragmentShaderFile);
    rewind(VertexShaderFile);
    FragmentShaderCode = (char *)malloc(FragmentFileSize+1);
    if( NULL == FragmentShaderCode ) {
        printf("Unable to read file %s.  Is the file correctly formatted?  Don't forget to read the FAQ!\n", fragment_file_path);
        getchar();
        free(VertexShaderCode);
        return 0;
    }
    FragmentFileSize = fread(FragmentShaderCode, 1, FragmentFileSize, FragmentShaderFile);
    fclose(FragmentShaderFile);
    FragmentShaderCode[FragmentFileSize] = 0;

    /* Compile Vertex Shader */
    printf("Compiling shader : %s\n", vertex_file_path);
    glShaderSource(VertexShaderID, 1, (const GLchar * const *)(&VertexShaderCode), NULL);
    glCompileShader(VertexShaderID);

    /* Check Vertex Shader */
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if( InfoLogLength > 0 ) {
        GLchar *VertexShaderErrorMessage = malloc(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n",VertexShaderErrorMessage);
        free(VertexShaderErrorMessage);
    }

    /* Compile Fragment Shader */
    printf("Compiling shader : %s\n", fragment_file_path);
    glShaderSource(FragmentShaderID, 1, (const GLchar * const *)(&FragmentShaderCode), NULL);
    glCompileShader(FragmentShaderID);

    /* Check Fragment Shader */
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if( InfoLogLength > 0 ) {
        GLchar *FragmentShaderErrorMessage = malloc(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n",FragmentShaderErrorMessage);
        free(FragmentShaderErrorMessage);
    }

    /* Link the program */
    printf("Linking program\n");
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    /* Check the program */
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if( InfoLogLength > 0 ) {
        GLchar *ProgramErrorMessage = malloc(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n",ProgramErrorMessage);
        free(ProgramErrorMessage);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
