#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";




void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        std::cout << "welcome to my game!" << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


float vertices[] = {                    // 3 verticies which have a 3D position stored in a float array
-0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 0.0f,  0.5f, 0.0f
};







int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;








    



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "OpenGlTUT", NULL, NULL);


    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 800);             // this is OpenGL knows how we want to display the data and coordinates with respect to the window


    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();                                                                     // has to be called before functions can be used NEEDS VALID OpenGl RENDERING CONTEXT



    unsigned int VBO;                                                                        // the vertex buffer object creation
    glGenBuffers(1, &VBO);                                                                   // this is a vertex buffer, that generates an id with glGenBuffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                            // binding the created buffer to the array target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);               // copies the vertex data into buffer memory
    //           Target             Size Bytes       Actual data      How GPU manages data


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);                         // 1st takes shader object to compile, 2nd how many strings, 3rd is source vertex, 4th is null 
    glCompileShader(vertexShader);

    int success;                                                                        // checks if the shader has compiled successfully
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR" << infolog << std::endl;
    }
 



    

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);                 // &frag is where we can control the colour
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


 

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(100, 100, 0, 255);                                     //changes the colour of the square (color is american spelling) currently yellow
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);




       

        //inputs
        processInput(window);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);                                            //swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window)

        /* Poll for and process events */
        glfwPollEvents();                                                   // checks if any events are triggered (like keyboard input or mouse movement events)
    }

    glfwTerminate();
    return 0;
}

