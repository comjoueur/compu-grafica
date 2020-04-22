#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
" FragColor = ourColor;\n"
"}\n\0";
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
" FragColor = ourColor;\n"
"}\n\0";


double f1 = 0.0, s1 = 0.0, t1 = 0.0, f2 = 0.0, s2 = 0.0, t2 = 0.0;

void changeColorKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if (key == GLFW_KEY_A && action == GLFW_PRESS)
f1 += 0.1;
if (key == GLFW_KEY_S && action == GLFW_PRESS)
s1 += 0.1;
if (key == GLFW_KEY_D && action == GLFW_PRESS)
t1 += 0.1;
if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
f2 += 0.1;
if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
s2 += 0.1;
if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
t2 += 0.1;
}


int main()
{
// glfw: initialize and configure
// ------------------------------
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// glfw window creation
// --------------------
GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
if (window == NULL)
{
std::cout << "Failed to create GLFW window" << std::endl;
glfwTerminate();
return -1;
}
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

// glad: load all OpenGL function pointers
// ---------------------------------------
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
std::cout << "Failed to initialize GLAD" << std::endl;
return -1;
}

unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
unsigned int shaderProgram1 = glCreateProgram();
unsigned int shaderProgram2 = glCreateProgram(); // the second shader program
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
glCompileShader(fragmentShader1);
glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
glCompileShader(fragmentShader2);
// link the first program object
glAttachShader(shaderProgram1, vertexShader);
glAttachShader(shaderProgram1, fragmentShader1);
glLinkProgram(shaderProgram1);

glAttachShader(shaderProgram2, vertexShader);
glAttachShader(shaderProgram2, fragmentShader2);
glLinkProgram(shaderProgram2);

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float firstTriangle[] = {
-0.9f, -0.5f, 0.0f,  // left
-0.0f, -0.5f, 0.0f,  // right
-0.45f, 0.5f, 0.0f,  // top
};
float secondTriangle[] = {
0.0f, -0.5f, 0.0f,  // left
0.9f, -0.5f, 0.0f,  // right
0.45f, 0.5f, 0.0f   // top
};
unsigned int VBOs[2], VAOs[2];
glGenVertexArrays(2, VAOs);
glGenBuffers(2, VBOs);
// first triangle setup
// --------------------
glBindVertexArray(VAOs[0]);
glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// second triangle setup
// ---------------------
glBindVertexArray(VAOs[1]);
glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
glEnableVertexAttribArray(0);

// render loop
// -----------

while (!glfwWindowShouldClose(window))
{

// render
// ------
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

glfwSetKeyCallback(window, changeColorKey);

glUseProgram(shaderProgram1);
int vertexColorLocation1 = glGetUniformLocation(shaderProgram1, "ourColor");
glUniform4f(vertexColorLocation1, f1, s1, t1, 1.0f);
glBindVertexArray(VAOs[0]);
glDrawArrays(GL_TRIANGLES, 0, 3);

glUseProgram(shaderProgram2);
int vertexColorLocation2 = glGetUniformLocation(shaderProgram2, "ourColor");
glUniform4f(vertexColorLocation1, f2, s2, t2, 1.0f);
glBindVertexArray(VAOs[1]);
glDrawArrays(GL_TRIANGLES, 0, 3);

// -------------------------------------------------------------------------------
glfwSwapBuffers(window);
glfwPollEvents();
}

glDeleteVertexArrays(2, VAOs);
glDeleteBuffers(2, VBOs);

glfwTerminate();
return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
glViewport(0, 0, width, height);
}