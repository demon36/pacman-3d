#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include "OBJLoader/objloader.hpp"

glm::mat4 basic_scale(float x, float y, float z){
	return glm::scale(glm::vec3(x, y ,z));
}

glm::mat4 basic_translate(float x, float y, float z){
	return glm::translate(glm::vec3(x, y ,z));
}


Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	//myCamera = std::unique_ptr<FPCamera>(new FPCamera());
	cameraType = 1; //euler's
	myCamera = std::unique_ptr<EulerCamera>(new EulerCamera());
	mytpCamera = std::unique_ptr<tpCamera>(new tpCamera());
	collisionManager = std::unique_ptr<CollisionManager>( new CollisionManager());

	//init engine
	mazeEngine = std::unique_ptr<engine>(new engine());
	mazeEngine->init();


	
	maze = std::unique_ptr<Model3D>(new Model3D());
	maze->LoadFromFile("data/models/maze/maze0.obj", true);
	maze->Initialize();
	//mazeM = basic_translate(-2.0f, 0.0f, 0.0f);

	//////////////////////////////////////////////////////////////////////////
	gameOver =  "GAME OVER";



	square = std::unique_ptr<Model>(new Model());

	square->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	square->UVData.push_back(glm::vec2(0.0f, 0.0f));
	square->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	square->UVData.push_back(glm::vec2(1.0f, 0.0f));
	square->VertexData.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	square->UVData.push_back(glm::vec2(1.0f, 1.0f));
	square->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	square->UVData.push_back(glm::vec2(0.0f, 1.0f));

	square->IndicesData.push_back(0);
	square->IndicesData.push_back(1);
	square->IndicesData.push_back(3);

	square->IndicesData.push_back(1);
	square->IndicesData.push_back(2);
	square->IndicesData.push_back(3);
	glm::vec3 squareNormal = glm::vec3(0.0, 0.0, 1.0);
	square->NormalsData.push_back(squareNormal);
	square->NormalsData.push_back(squareNormal);
	square->NormalsData.push_back(squareNormal);
	square->NormalsData.push_back(squareNormal);
	square->Initialize();
	//bottom = std::unique_ptr<Texture>(new Texture("data/textures/Side1.png", 0));
	top = std::unique_ptr<Texture>(new Texture("data/textures/Side6.png", 0));
	left = std::unique_ptr<Texture>(new Texture("data/textures/Side3.png", 0));
	right = std::unique_ptr<Texture>(new Texture("data/textures/Side4.png", 0));
	back = std::unique_ptr<Texture>(new Texture("data/textures/Side2.png", 0));
	front = std::unique_ptr<Texture>(new Texture("data/textures/Side5.png", 0));
	floorTexture = std::unique_ptr<Texture>(new Texture("data/textures/Side1.png", 0));
	topM = basic_translate(0.0f, 45.0f, 0.0f) * basic_scale(30.0f, 30.0f, 30.0f) * glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//bottomM = basic_translate(0.0f, -30.0f, 0.0f) * basic_scale(30.0f, 30.0f, 30.0f) * glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	leftM = basic_translate(0.0f, 15.0f, 30.0f) * basic_scale(30.0f, 30.0f, 30.0f);
	rightM = basic_translate(0.0f, 15.0f, -30.0f) * basic_scale(30.0f, 30.0f, 30.0f);
	backM = basic_translate(30.0f, 15.0f, 0.0f) * basic_scale(30.0f, 30.0f, 30.0f) * glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	frontM = basic_translate(-30.0f, 15.0f, 0.0f) * basic_scale(30.0f, 30.0f, 30.0f) * glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	floorM = basic_translate(0.0f, -0.01f, 0.0f)*basic_scale(30.0f, 30.0f, 30.0f)*glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	Raven.LoadModel("data/models/raven/raven.md2");
	RavenAnimationState =Raven.StartAnimation(animType_t::fly);
	RavenM = glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))* basic_translate(-1.0f, 0.0f, 0.0f) *  basic_scale(0.1f, 0.1f, 0.1f);

	//RavenM = glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))* basic_translate(-7.0f, -2.0f, 2.0f) *  basic_scale(0.1f, 0.1f, 0.1f);

	//////////////////////////////////////////////////////////////////////////
	

	
	// Create and compile our GLSL program from the shaders
	animatedModelShader.LoadProgram();
	animatedModelShader.UseProgram();

	staticModelShader.LoadProgram();
	staticModelShader.UseProgram();
	staticModelShaderAttr.vertexPosition_modelspaceID = glGetAttribLocation(staticModelShader.programID, "vertexPosition_modelspace");
	staticModelShaderAttr.inputColorID = glGetAttribLocation(staticModelShader.programID, "inputColor");
	staticModelShaderAttr.texCoordID = glGetAttribLocation(staticModelShader.programID, "texCoord");
	staticModelShaderAttr.vertexNormal_modelspaceID = glGetAttribLocation(staticModelShader.programID,"vertexNormal_modelspace");
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
	mytpCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);

	// View matrix : 
	myCamera->Reset(0.0,1.0,2.0,
					0,0,0,
					0,1,0);
	mytpCamera->Reset(0.0,0.0,5.0,
					3,0,0,
					0,1,0);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	staticModelShader.UseProgram();

	PointLightPositionID = glGetUniformLocation(staticModelShader.programID, "LightPosition_worldspace");
	pointlightPosition = glm::vec3(5.0, 15.0, 0.0);
	glUniform3fv(PointLightPositionID, 1, &pointlightPosition[0]);
	SpotLightPositionID = glGetUniformLocation(staticModelShader.programID, "SpotLightPosition_worldspace");
	spotlightPosition = glm::vec3(4.1f, 10.0f, 4.0f);
	glUniform3fv(SpotLightPositionID, 1, &spotlightPosition[0]);
	SpotLightDirectionID = glGetUniformLocation(staticModelShader.programID, "SpotLightDirection");
	spotlightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
	glUniform3fv(SpotLightDirectionID, 1, &spotlightDirection[0]);
	GLint lightSpotCutOffLoc = glGetUniformLocation(staticModelShader.programID, "cutoff");
	glUniform1f(lightSpotCutOffLoc, glm::cos(glm::radians(30.0f)));
	//setup the ambient light component.
	AmbientPointLightID = glGetUniformLocation(staticModelShader.programID, "ambientPointLight");
	ambientPointLight = glm::vec3(0.3, 0.3, 0.3);
	glUniform3fv(AmbientPointLightID, 1, &ambientPointLight[0]);
	//diffuse
	DiffusePointLightID = glGetUniformLocation(staticModelShader.programID, "diffusePointLight");
	diffusePointLight = glm::vec3(1.0, 1.0, 1.0);
	glUniform3fv(DiffusePointLightID, 1, &diffusePointLight[0]);
	DiffuseSpotLightID = glGetUniformLocation(staticModelShader.programID, "diffuseSpotLight");
	diffuseSpotLight = glm::vec3(1.0, 0.0, 0.0);
	glUniform3fv(DiffuseSpotLightID, 1, &diffuseSpotLight[0]);
	//specular
	SpecularPointLightID = glGetUniformLocation(staticModelShader.programID, "specularPointLight");
	specularPointLight = glm::vec3(1.0, 1.0, 1.0);
	glUniform3fv(SpecularPointLightID, 1, &specularPointLight[0]);
	SpecularSpotLightID = glGetUniformLocation(staticModelShader.programID, "specularSpotLight");
	specularSpotLight = glm::vec3(1.0, 0.0, 0.0);
	glUniform3fv(SpecularSpotLightID, 1, &specularSpotLight[0]);

	//setup the eye position.
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	if(cameraType == 0)
		glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
	else if(cameraType == 1)
		glUniform3fv(EyePositionID,1, &mytpCamera->GetEyePosition()[0]);
	

	///////////////////////////////////////////////////
	//repeat the process for the animated models shader.
	animatedModelShader.UseProgram();
	PointLightPositionID = glGetUniformLocation(animatedModelShader.programID, "LightPosition_worldspace");
	pointlightPosition = glm::vec3(0.0, 15.0, 0.0);
	glUniform3fv(PointLightPositionID, 1, &pointlightPosition[0]);
	SpotLightPositionID = glGetUniformLocation(animatedModelShader.programID, "SpotLightPosition_worldspace");
	spotlightPosition = glm::vec3(4.1f, 11.0f, 4.0f);
	glUniform3fv(SpotLightPositionID, 1, &spotlightPosition[0]);
	SpotLightDirectionID = glGetUniformLocation(animatedModelShader.programID, "SpotLightDirection");
	spotlightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
	glUniform3fv(SpotLightDirectionID, 1, &spotlightDirection[0]);
	lightSpotCutOffLoc = glGetUniformLocation(animatedModelShader.programID, "cutoff");
	glUniform1f(lightSpotCutOffLoc, glm::cos(glm::radians(30.0f)));
	//setup the ambient light component.
	AmbientPointLightID = glGetUniformLocation(animatedModelShader.programID, "ambientPointLight");
	ambientPointLight = glm::vec3(0.1, 0.1, 0.1);
	glUniform3fv(AmbientPointLightID, 1, &ambientPointLight[0]);
	//diffuse
	DiffusePointLightID = glGetUniformLocation(animatedModelShader.programID, "diffusePointLight");
	diffusePointLight = glm::vec3(1.0, 1.0, 1.0);
	glUniform3fv(DiffusePointLightID, 1, &diffusePointLight[0]);
	DiffuseSpotLightID = glGetUniformLocation(animatedModelShader.programID, "diffuseSpotLight");
	diffuseSpotLight = glm::vec3(1.0, 0.0, 0.0);
	glUniform3fv(DiffuseSpotLightID, 1, &diffuseSpotLight[0]);
	//specular
	SpecularPointLightID = glGetUniformLocation(animatedModelShader.programID, "specularPointLight");
	specularPointLight = glm::vec3(1.0, 1.0, 1.0);
	glUniform3fv(SpecularPointLightID, 1, &specularPointLight[0]);
	SpecularSpotLightID = glGetUniformLocation(animatedModelShader.programID, "specularSpotLight");
	specularSpotLight = glm::vec3(1.0, 0.0, 0.0);
	glUniform3fv(SpecularSpotLightID, 1, &specularSpotLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	if(cameraType == 0)
		glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
	else if(cameraType == 1)
		glUniform3fv(EyePositionID,1, &mytpCamera->GetEyePosition()[0]);

	//////////////////////////////////////////////////////////////////////////




}
void Renderer::drawText(const char *text, int length, int x, int y){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 200, 0, 200, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2i(x, y);
	//glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);


}
void Renderer::Draw()
{		

		//Bind the VP matrix (Camera matrices) to the current shader.
		glm::mat4 VP;
		if(cameraType == 0)
			VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
		else if(cameraType == 1){
			mytpCamera->setCentrePosition(mazeEngine->pacman->pos.x, mazeEngine->pacman->pos.z);
			VP = mytpCamera->GetProjectionMatrix() * mytpCamera->GetViewMatrix();
		}

		//skybox
		staticModelShader.UseProgram();
		staticModelShader.BindVPMatrix(&VP[0][0]);

		//staticModelShader.BindModelMatrix(&bottomM[0][0]);
		//bottom->Bind();
		//square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindModelMatrix(&topM[0][0]);
		top->Bind();
		square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindModelMatrix(&leftM[0][0]);
		left->Bind();
		square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindModelMatrix(&rightM[0][0]);
		right->Bind();
		square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindModelMatrix(&backM[0][0]);
		back->Bind();
		square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindModelMatrix(&frontM[0][0]);
		front->Bind();
		square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindModelMatrix(&floorM[0][0]);
		floorTexture->Bind();
		square->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);
		for (int i = 0; i < mazeEngine->foodPosVector.size(); i++)
			mazeEngine->food->Render(&staticModelShader, glm::translate(mazeEngine->foodPosVector[i].second) * mazeEngine->foodMmx);

		drawText(mazeEngine->score.data(), mazeEngine->score.size(), 5, 105);
		if (mazeEngine->lives == 0){
			drawText(gameOver.data(), gameOver.size(), 90, 90);
		}
		
		mazeEngine->pacman->Render(&staticModelShader,mazeEngine->pacman->MMX);
		maze->Render(&staticModelShader, mazeM);

		for(int i = 0; i < 4; i++)
		mazeEngine->ghosts[i]->Render(&staticModelShader, mazeEngine->ghosts[i]->MMX);

		for(int i = 0; i < mazeEngine->foodPosVector.size() ; i++)
			if(mazeEngine->foodPosVector[i].first)
				mazeEngine->food->Render(&staticModelShader, glm::translate(mazeEngine->foodPosVector[i].second) * mazeEngine->foodMmx);

		for(int i = 0; i < mazeEngine->lives ; i++)
			mazeEngine->pacman->Render(&staticModelShader, basic_translate(-1.0f, 1.0f, 0.0f + (float)i) * basic_scale(mazeEngine->pacmanR,mazeEngine->pacmanR,mazeEngine->pacmanR));


		animatedModelShader.UseProgram();
		animatedModelShader.BindVPMatrix(&VP[0][0]);
		animatedModelShader.BindModelMatrix(&RavenM[0][0]);
		Raven.RenderModel(&RavenAnimationState, &animatedModelShader);

		
}

void Renderer::Cleanup()
{
}

void Renderer::Update(double deltaTime)
{
	
	Raven.UpdateAnimation(&RavenAnimationState, deltaTime / 1000);
	mazeEngine->update();
	//mazeEngine->UpdateGhosts();
	//update the eye position uniform.
	staticModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &mytpCamera->GetEyePosition()[0]);

	animatedModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &mytpCamera->GetEyePosition()[0]);
	
}

void Renderer::HandleKeyboardInput(int key)
{
	float step = 0.1f;


	switch (key)
	{
		//switch camera
	case GLFW_KEY_F3:
		cameraType = 1;
		glUniform3fv(EyePositionID,1, & mytpCamera->GetEyePosition()[0]);
		printf("camerType = %f \n",cameraType);
		break;
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		myCamera->Walk(step);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		myCamera->Walk(-step);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		myCamera->Strafe(step);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		myCamera->Strafe(-step);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->Fly(step);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		myCamera->Fly(-step);
		break;
	default:
		break;
	}


	//mazeEngine->UpdateGhosts();
	//continue the remaining movements.
	myCamera->UpdateViewMatrix();

	//update the eye position uniform.
	staticModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);

	animatedModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();
}

//tpcamera

void Renderer::HandleKeyboardInput_tpc(int key)
{
	//printf("Renderer::KEY = %d \n",key);
	switch (key)
	{
		//switch camera
	case GLFW_KEY_F4:
		cameraType = 0;
		glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
		printf("camerType = %f \n",cameraType);
		break;
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		mazeEngine->pacmanUp();
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		mazeEngine->pacmanDown();
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		mazeEngine->pacmanRight();
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		mazeEngine->pacmanLeft();
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		mazeEngine->pacmanJump();
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		//mytpCamera->Fly(-0.1);
		break;
	default:
		break;
	}


	//continue the remaining movements.

	mytpCamera->UpdateViewMatrix();

}

void Renderer::HandleMouse_tpc(double deltaX,double deltaY)
{
	
	mytpCamera->lookAround(deltaX/10,deltaY/10);

	

}

void Renderer::HandleScroll_tpc(double deltaY)
{
	mytpCamera->r += -deltaY/10;
	if (mytpCamera->r < 5.0f)
		mytpCamera->r = 5.0f;
	else if (mytpCamera->r > 15.0f)
		mytpCamera->r = 15.0f;
	mytpCamera->UpdateViewMatrix();

}