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

Shader::Shader(std::string vertexPath, std::string geometryPath, std::string fragmentPath)
{
    vShaderFile.open(vertexPath);
    gShaderFile.open(geometryPath);
    fShaderFile.open(fragmentPath);

    if (vShaderFile.is_open() == false)
    {
        throw std::exception();
    }
    if (gShaderFile.is_open() == false)
    {
        throw std::exception();
    }
    if (fShaderFile.is_open() == false)
    {
        throw std::exception();
    }

    std::stringstream vShaderStream, gShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    gShaderStream << gShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    gShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    geometryCode = gShaderStream.str();
    fragmentCode = fShaderStream.str();

    const GLchar* vertexSource = vertexCode.c_str();
    const GLchar* geometrySource = geometryCode.c_str();
    const GLchar* fragmentSource = fragmentCode.c_str();

    SetupShader(vertexSource, geometrySource, fragmentSource);
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
        std::cout << "Failed to compile vertex shader!" << std::endl;

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
        std::cout << "Failed to compile fragment shader!" << std::endl;

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

void Shader::SetupShader(const GLchar* vertexSource, const GLchar* geometrySource, const GLchar* fragmentSource)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);
    GLint success = 0;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "Failed to compile vertex shader!" << std::endl;

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

    GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShaderID, 1, &geometrySource, NULL);
    glCompileShader(geometryShaderID);
    glGetShaderiv(geometryShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "Failed to compile geometry shader!" << std::endl;

        GLint maxLength = 0;
        glGetShaderiv(geometryShaderID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(geometryShaderID, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < errorLog.size(); i++)
        {
            std::cout << errorLog[i];
        }

        glDeleteShader(geometryShaderID);
        return;
    }

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "Failed to compile fragment shader!" << std::endl;

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
    glAttachShader(programID, geometryShaderID);
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
    glDetachShader(programID, geometryShaderID);
    glDeleteShader(geometryShaderID);
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

void Shader::BindFloat(std::string location, float value)
{
    GLint floatLocation = glGetUniformLocation(programID, location.c_str());
    glUniform1f(floatLocation, value);
}

void Shader::BindInt(std::string location, int value)
{
    GLint floatLocation = glGetUniformLocation(programID, location.c_str());
    glUniform1i(floatLocation, value);
}

void Shader::BindVector3(std::string location, glm::vec3 vector)
{
    GLint vectorLocation = glGetUniformLocation(programID, location.c_str());
    glUniform3f(vectorLocation, vector.x, vector.y, vector.z);
}