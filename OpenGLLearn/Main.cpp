#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderTool.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void CheckShaderStatus(GLuint shader);
void CheckProgramStatus(GLuint shaderProg);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

    // Init GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set callback func
    glfwSetKeyCallback(window, key_callback);

    // Initialize GLEW 
    glewExperimental = GL_TRUE;
    
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    // Build, compile shader program

    string vertexShaderSourceStr = LoadShaderFromFile("VertShader.vert");
    const GLchar* vertexShaderSource = vertexShaderSourceStr.c_str();
    string fragmentShaderSourceStr = LoadShaderFromFile("FragShader.frag");
    const GLchar* fragmentShaderSource = fragmentShaderSourceStr.c_str();
    /*string fragmentYellowShaderSourceStr = LoadShaderFromFile("FragShaderYellow.frag");
    const GLchar* fragmentYellowShaderSource = fragmentYellowShaderSourceStr.c_str();*/

    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    CheckShaderStatus(vertexShader);

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    CheckShaderStatus(fragmentShader);

    /*GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentYellowShaderSource, NULL);
    glCompileShader(fragmentShader2);

    CheckShaderStatus(fragmentShader2);*/

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    CheckProgramStatus(shaderProgram);

    /*GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);*/

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //glDeleteShader(fragmentShader2);

    GLfloat vertices[] = {
         // Positions        // Colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Down right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Down left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Up
    };

    /*GLfloat secondTriangle[] = {
         0.0f, -0.5f, 0.0f, 
         0.9f, -0.5f, 0.0f,  
         0.45f, 0.5f, 0.0f
    };*/

    //VAO, VBO init
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    //GLuint VBOs[2], VAOs[2];
    //glGenVertexArrays(2, VAOs);
    //glGenBuffers(2, VBOs);

    //first
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
    //Second
    /*glBindVertexArray(VAOs[1]);
  
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);*/

    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Normal mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Change in main loop
    

    // Main loop
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        GLfloat timeValue = glfwGetTime();
        GLfloat blueValue = (sin(timeValue) / 2) + 0.5;
        GLfloat redValue = 1-((sin(timeValue) / 2) + 0.5);
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, redValue, 0.0f, blueValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);*/

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}