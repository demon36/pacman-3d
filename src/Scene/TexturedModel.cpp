#include "TexturedModel.h"
#include <GL/glew.h>


TexturedModel::TexturedModel(void)
{
}


TexturedModel::~TexturedModel(void)
{
}

void TexturedModel::Draw(GLuint vertexPosition_modelspaceID, GLuint inputColorID, GLuint texCoordID, GLuint vertexNormal_modelspaceID)
{
	texture->Bind();
	Model::Draw( vertexPosition_modelspaceID,  inputColorID,  texCoordID,  vertexNormal_modelspaceID);
}