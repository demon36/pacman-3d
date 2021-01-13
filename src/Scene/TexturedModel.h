#ifndef TexturedModel_h__
#define TexturedModel_h__

#include <glm/glm.hpp>
#include <vector>
#include "Texture/texture.h"
#include "GraphicsDevice/ShaderProgram.h"
#include "Model/Model.h"
#include <GL/glew.h>

class TexturedModel : public Model
{
	
public:
	TexturedModel();
	~TexturedModel();
	Texture* texture;
	 void Draw(GLuint vertexPosition_modelspaceID, GLuint inputColorID, GLuint texCoordID, GLuint vertexNormal_modelspaceID);
};
#endif // Model_h__

