#include "Shader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    if (vShaderFile.is_open() == false)
    {
        throw std::exception();
    }
    if (fShaderFile.is_open() == false)
    {
        throw std::exception();
    }

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const GLchar* vertexSource = vertexCode.c_str();
    const GLchar* fragmentSource = fragmentCode.c_str();

    SetupShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{

}

void Shader::SetupShader(const GLchar* vertexSource, const GLchar* fragmentSource)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);
    GLint success = 0;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < errorLog.size(); i++)
        {
            std::cout << errorLog[i];
        }

        glDeleteShader(vertexShaderID);
        return;
    }

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentShaderID, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < errorLog.size(); i++)
        {
            std::cout << errorLog[i];
        }

        glDeleteShader(fragmentShaderID);
        return;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentShaderID, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < errorLog.size(); i++)
        {
            std::cout << errorLog[i];
        }

        glDeleteProgram(programID);
        throw std::exception();
    }

    glDetachShader(programID, vertexShaderID);
    glDeleteShader(vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(fragmentShaderID);
}

void Shader::UseShader()
{
    glUseProgram(programID);
}

void Shader::BindAttributeLocation(int index, const GLchar* name)
{
    glBindAttribLocation(programID, index, name);
}

void Shader::BindMatrix(std::string location, glm::mat4 matrix)
{
    GLint matrixLocation = glGetUniformLocation(programID, location.c_str());
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}