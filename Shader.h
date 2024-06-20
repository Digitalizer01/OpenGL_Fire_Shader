#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // Constructor que carga y compila los shaders, y enlaza el programa de shaders.
    Shader(const char* vertexPath, const char* fragmentPath);

    // Método para activar el programa de shaders.
    void use();

    // Métodos para establecer valores de uniformes boolean, int y float.
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    // ID del programa de shaders.
    unsigned int ID;

    // Funciones para compilar shaders y enlazar el programa de shaders.
    unsigned int compileShader(unsigned int type, const char* source);
    unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader);

    // Función para verificar errores de compilación y enlace de shaders.
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif
