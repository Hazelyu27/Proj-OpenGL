#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

#include<filesystem>
#include "stb_image.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// ��������
float texCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
};
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
unsigned indices[] = {
    0,1,3,
    1,2,3
};
int main(void)
{
    glfwInit();
    // ����opengl�����ΰ汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //����window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // ÿ�����ڵ�����Сʱ������framebuffer_size_callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // �����ӿ�
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }





    // ��Ⱦѭ��

    Shader ourShader("vertex.shader", "fragment.shader");


    // ����һ��vbo����
    unsigned int VBO, VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //����һ��id��vbo����
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��һ��array�󶨵�GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //�Ѷ��㸴�Ƶ�������ڴ��� GL_STATIC_DRAW����������ı�

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ���ߺ������ö�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // vertex����
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    // ��������
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ��������ͼ��
    int width, height, nrChannels;
    unsigned char* data = stbi_load("texture2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // draw our first triangle
    //glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        ourShader.use();

        //glActiveTexture(GL_TEXTURE0); // �ڰ�����֮ǰ�ȼ�������Ԫ
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // update color 
        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // render
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
       /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES,0,3);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}