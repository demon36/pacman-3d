#ifndef Renderer_h__
#define Renderer_h__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include <memory>


#include "Shaders/shader.hpp"
#include "Model/Model.h"
#include "EulerCamera/EulerCamera.h"
#include "tpCamera/tpcamera.h"
#include "Texture/texture.h"
#include "GraphicsDevice/ShaderProgram.h"
#include "Scene/Model3D.h"
#include "GraphicsDevice/KeyFrameAnimationShader.h"
#include "MD2Model/md2model.h"
#include "CollisionDetection/CollisionManager.h"
#include "gameChar.h"
#include "engine.h"

struct StaticModelShaderAttributes
{
public:
	// Vertex attributes
	GLuint vertexPosition_modelspaceID, inputColorID, texCoordID, vertexNormal_modelspaceID;
};


class Renderer
{


    KeyFrameAnimationShader animatedModelShader;
	ShaderProgram staticModelShader;
	//// Transformation
	GLuint AmbientPointLightID;
	GLuint AmbientSpotLightID;
	GLuint PointLightPositionID;
	GLuint SpotLightPositionID;
	GLuint SpotLightDirectionID;
	GLuint EyePositionID;

	GLuint DiffusePointLightID;
	GLuint DiffuseSpotLightID;
	GLuint SpecularPointLightID;
	GLuint SpecularSpotLightID;
	GLuint PointLightAID;
	GLuint SpotLightAID;
	GLuint PointLightBID;
	GLuint SpotLightBID;
	GLuint PointLightCID;
	GLuint SpotLightCID;

	

	std::unique_ptr<Model> floor;
	std::unique_ptr<Texture> floorTexture;
	std::unique_ptr<Model3D> maze;
	std::unique_ptr<engine> mazeEngine;
	std::unique_ptr<EulerCamera> myCamera;
	std::unique_ptr<tpCamera> mytpCamera;

	std::string gameOver;// = "GAME OVER";
	
	glm::vec3 ambientPointLight;
	glm::vec3 ambientSpotLight;
	glm::vec3 diffusePointLight;
	glm::vec3 diffuseSpotLight;
	glm::vec3 specularPointLight;
	glm::vec3 specularSpotLight;
	glm::vec3 pointlightPosition;
	glm::vec3 spotlightPosition;
	glm::vec3 spotlightDirection;

	std::unique_ptr<CollisionManager> collisionManager;
	StaticModelShaderAttributes staticModelShaderAttr;




	CMD2Model Raven;
	animState_t RavenAnimationState;

	std::unique_ptr<Texture> front;
	std::unique_ptr<Texture> back;
	std::unique_ptr<Texture> top;
	std::unique_ptr<Texture> right;
	std::unique_ptr<Texture> left;
	std::unique_ptr<Texture> bottom;

	std::unique_ptr<Model> square;

	glm::mat4 frontM;
	glm::mat4 backM;
	glm::mat4 topM;
	glm::mat4 rightM;
	glm::mat4 leftM;
	glm::mat4 bottomM;
	glm::mat4 mazeM;
	glm::mat4 floorM;
	glm::mat4 RavenM;

	void drawText(const char*, int, int, int);

public:

	GLuint cameraType;
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void HandleKeyboardInput_tpc(int key);
	void HandleMouse_tpc(double deltaX,double deltaY);
	void HandleScroll_tpc(double deltaY);
	void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__