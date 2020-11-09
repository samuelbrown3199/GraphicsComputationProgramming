#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, std::shared_ptr<Material> _mat, std::string _fileName)
{
	shader = _shader;
	position = _pos;
	rotation = _rot;
	scale = _scale;
	material = _mat;

	fileName = _fileName;
	InitialiseMesh();
}

void MeshRenderer::InitialiseMesh()
{
	vaoId = buLoadModel(fileName, &drawCount);
}

glm::mat4 MeshRenderer::GetModelMatrix()
{
	glm::mat4 rtn(1.0f);

	rtn = glm::translate(rtn, position);
	rtn = glm::rotate(rtn, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	rtn = glm::rotate(rtn, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	rtn = glm::rotate(rtn, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	rtn = glm::scale(rtn, scale);

	return rtn;
}

void MeshRenderer::RenderMesh(glm::mat4 projection, glm::mat4 view)
{
	shader->UseShader();
	shader->BindMatrix("u_Projection", projection);
	shader->BindMatrix("u_View", view);
	shader->BindMatrix("u_Model", GetModelMatrix());
	shader->BindInt("material.diffuse", 0);
	shader->BindInt("material.specular", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material->diffuse->textureID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, material->specular->textureID);

	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}