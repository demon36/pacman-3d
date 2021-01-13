#include "Model.h"


Model::Model(void)
{
}


Model::~Model(void)
{
}

void Model::Initialize()
{

	if(VertexData.size()>0)
	{
		glGenBuffers(1, &mVertexDataBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBufferID);
		glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(glm::vec3), &VertexData[0], GL_STATIC_DRAW);
	}
	if (ColorData.size() > 0)
	{
		glGenBuffers(1, &mColorDataBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mColorDataBufferID);
		glBufferData(GL_ARRAY_BUFFER, ColorData.size() * sizeof(glm::vec3), &ColorData[0], GL_STATIC_DRAW);
	}
	if (IndicesData.size()>0)
	{
		glGenBuffers(1, &mIndicesDataBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesDataBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesData.size() * sizeof(unsigned short), &IndicesData[0] , GL_STATIC_DRAW);
	}
	if (UVData.size() > 0)
	{
		glGenBuffers(1, &mUVDataBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mUVDataBufferID);
		glBufferData(GL_ARRAY_BUFFER, UVData.size() * sizeof(glm::vec2) , &UVData[0], GL_STATIC_DRAW);
	}
	if (NormalsData.size() > 0)
	{
		glGenBuffers(1, &mNormalsBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalsBufferID);
		glBufferData(GL_ARRAY_BUFFER, NormalsData.size() * sizeof(glm::vec3) , &NormalsData[0], GL_STATIC_DRAW);
	}
	//now all the state is save in the Vertex Array Object, we only need to bind it in the drawing code (each frame).
}

void Model::Draw(GLuint vertexPosition_modelspaceID, GLuint inputColorID, GLuint texCoordID, GLuint vertexNormal_modelspaceID)
{
	if(VertexData.size()>0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBufferID);
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glVertexAttribPointer(vertexPosition_modelspaceID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	}

	if (ColorData.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mColorDataBufferID);
		glEnableVertexAttribArray(inputColorID);
		glVertexAttribPointer(inputColorID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	}

	if (UVData.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mUVDataBufferID);
		glEnableVertexAttribArray(texCoordID);
		glVertexAttribPointer(texCoordID,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	}
	if (NormalsData.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mNormalsBufferID);
		glEnableVertexAttribArray(vertexNormal_modelspaceID);
		glVertexAttribPointer(vertexNormal_modelspaceID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	}

	if (IndicesData.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesDataBufferID);
		glDrawElements(GL_TRIANGLES, IndicesData.size(),GL_UNSIGNED_SHORT,0);
	}
	else
	{
		//no indices provided.
		glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBufferID);
		glDrawArrays(GL_TRIANGLES, 0, VertexData.size());
	}
}

void Model::Cleanup()
{
	glDeleteBuffers(1, &mVertexDataBufferID);
	glDeleteBuffers(1, &mColorDataBufferID);
	glDeleteBuffers(1, &mIndicesDataBufferID);
	glDeleteBuffers(1, &mUVDataBufferID);
	glDeleteBuffers(1, &mNormalsBufferID);
}
