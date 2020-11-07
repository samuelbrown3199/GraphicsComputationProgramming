#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, std::shared_ptr<Texture> _tex)
{
	shader = _shader;
	position = _pos;
	rotation = _rot;
	scale = _scale;

    tex = _tex;

    InitialiseCube();
}

void CubeRenderer::InitialiseCube()
{
    static const GLfloat positions[] =
    {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,

    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,

    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,

    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,

    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    static const GLfloat texCoords[] =
    {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    };

    static const GLfloat normals[] =
    {
     //bottom face
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, 1.0f,
     -1.0f, -1.0f, 1.0f,

     1.0f, -1.0f, -1.0f,
     -1.0f, -1.0f, 1.0f,
     -1.0f, -1.0f, -1.0f,

     //top face
     1.0f, 1.0f, -1.0f,
     -1.0f, 1.0f, -1.0f,
     -1.0f, 1.0f, 1.0f,

     1.0f, 1.0f, -1.0f,
     -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,

     //right face
     1.0f, -1.0f, -1.0f,
     1.0f, 1.0f, -1.0f,
     1.0f, 1.0f, 1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, -1.0f, 1.0f,

     //front face
     1.0f, -1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f,

     1.0f, -1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f,
     -1.0f, -1.0f, 1.0f,

     //left face
     -1.0f, -1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f,
     -1.0f, 1.0f, -1.0f,

     -1.0f, -1.0f, 1.0f,
     -1.0f, 1.0f, -1.0f,
     -1.0f, -1.0f, -1.0f,

     //back face
     1.0f, 1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     -1.0f, -1.0f, -1.0f,

     1.0f, 1.0f, -1.0f,
     -1.0f, -1.0f, -1.0f,
     -1.0f, 1.0f, -1.0f,

    };

    GLuint positionsVboId = 0;
    // Create a new VBO on the GPU and bind it
    glGenBuffers(1, &positionsVboId);
    if (!positionsVboId)
    {
        throw std::exception();
    }
    glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
    // Upload a copy of the data from memory into the new VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    // Reset the state
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLuint uvVboId = 0;
    glGenBuffers(1, &uvVboId);
    if (!uvVboId)
    {
        throw std::exception();
    }
    glBindBuffer(GL_ARRAY_BUFFER, uvVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalVboId = 0;
    glGenBuffers(1, &normalVboId);
    if (!normalVboId)
    {
        throw std::exception();
    }
    glBindBuffer(GL_ARRAY_BUFFER, normalVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vaoId);
    if (!vaoId)
    {
        throw std::exception();
    }
    glBindVertexArray(vaoId);
    // Bind the position VBO, assign it to position 0 on the bound VAO
    // and flag it to be used
    glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVboId);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, normalVboId);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(2);

    // Reset the state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::mat4 CubeRenderer::GetModelMatrix()
{
    glm::mat4 rtn(1.0f);

    rtn = glm::translate(rtn, position);
    rtn = glm::rotate(rtn, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    rtn = glm::rotate(rtn, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    rtn = glm::rotate(rtn, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    rtn = glm::scale(rtn, scale);

    return rtn;
}

void CubeRenderer::RenderCube(glm::mat4 projection, glm::mat4 view)
{
    shader->UseShader();
    shader->BindMatrix("u_Projection", projection);
    shader->BindMatrix("u_View", view);
    shader->BindMatrix("u_Model", GetModelMatrix());

    glBindTexture(GL_TEXTURE_2D, tex->textureID);
    glBindVertexArray(vaoId);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}