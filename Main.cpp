#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "Shader.h"
#include <iostream>

// Procesa toda la entrada: consulta si se presionaron / soltaron teclas relevantes este fotograma y reacciona en consecuencia
void processInput(GLFWwindow* window);
// GLFW: cuando cambia el tamaño de la ventana (por el sistema operativo o el usuario), esta función de devolución de llamada se ejecuta
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Verifica e imprime cualquier error de OpenGL
void checkGLError();

// Constantes
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Inicializa y configura GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crea ventana GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Fire shader", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Carga punteros de funciones de OpenGL usando GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error al inicializar GLAD" << std::endl;
        return -1;
    }

    // Compilar y construir el programa de sombreado
    Shader fireShader("fire.vs", "fire.fs");

    // Configuración de datos y búferes de vértices
    float vertices[] = {
        // posiciones       // coordenadas de textura
        -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, // arriba izquierda
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, // arriba derecha
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, // abajo derecha
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f  // abajo izquierda 
    };

    unsigned int indices[] = {
        0, 1, 3, // primer triángulo
        1, 2, 3  // segundo triángulo
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo de posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo de coordenada de textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Carga y crea una textura
    unsigned int fireTexture;
    glGenTextures(1, &fireTexture);
    glBindTexture(GL_TEXTURE_2D, fireTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("fire.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Error al cargar la textura" << std::endl;
    }
    stbi_image_free(data);

    // Bucle de renderizado
    while (!glfwWindowShouldClose(window))
    {
        // Procesa entrada
        processInput(window);

        // Renderiza
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Habilita mezcla para transparencia
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Usar mezcla aditiva

        // Vincula textura
        glBindTexture(GL_TEXTURE_2D, fireTexture);

        // Activa el programa de sombreado
        fireShader.use();

        // Pasa tiempo al sombreador
        float timeValue = glfwGetTime();
        fireShader.setFloat("uvAlphaTime", timeValue);

        // Renderiza contenedor
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Intercambia búferes y procesa eventos de entrada/salida
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Libera recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &fireTexture);

    // Termina GLFW
    glfwTerminate();
    return 0;
}

// ------------------- FUNCIONES -------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void checkGLError()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "Error de OpenGL: " << err << std::endl;
    }
}
