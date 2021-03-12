#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void CheckShaderStatus(GLuint shader);
void CheckProgramStatus(GLuint shaderProg);

const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    CheckProgramStatus(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f
    };

    GLfloat secondTriangle[] = {
         0.0f, -0.5f, 0.0f, 
         0.9f, -0.5f, 0.0f,  
         0.45f, 0.5f, 0.0f
    };

    //VAO, VBO init
    GLuint VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    //first
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    //Second
    glBindVertexArray(VAOs[1]);
  
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Normal mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Change in main loop
    glUseProgram(shaderProgram);

    // Main loop
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void CheckShaderStatus(GLuint shader)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void CheckProgramStatus(GLuint shaderProg)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProg, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}