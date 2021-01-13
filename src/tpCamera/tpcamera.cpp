#include "tpcamera.h"
#include <stdio.h>

tpCamera::tpCamera(void)
{
	pi = 3.14159265359;
	mAngleX = 0;
	mAngleY = 0;
	mCentre = glm::vec3(3.0f, 0.0f, 0.0f);
	this->Reset(0, 0, 0, 
		3, 0, 0, 
		0, 1, 0);
	r = 9;
	theta = (45*pi)/180;
	alpha = (180*pi)/180;

	SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
}

tpCamera::~tpCamera(void)
{
}

glm::vec3 tpCamera::GetLookDirection()
{
	return -mDirection;
}

void tpCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void tpCamera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	float x = mCentre.x + r*sin(theta)*sin(alpha);
	float y = mCentre.y + r*cos(theta);
	float z = mCentre.z + r*sin(theta)*cos(alpha);

	mPosition = glm::vec3(x,y,z);
	printf("mposition = %f,%f,%f \n",x,y,z);
	printf("center = %f,%f,%f \n",center.x,center.y,center.z);
	//still needs normalization
	mDirection = center - mPosition;
	//i = j x k
	mRight = glm::cross( mDirection,up );
	//j = k x i
	mUp = up;
	//normalize all
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);

	mViewMatrix = glm::lookAt(mPosition,center,mUp);
	//UpdateViewMatrix();
}

glm::mat4 tpCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void tpCamera::UpdateViewMatrix()
{
	const float PI = 3.14f;
	mDirection = glm::vec3(
		-cos(mAngleY)*sin(mAngleX), 
		 sin(mAngleY), 
		-cos(mAngleY)*cos(mAngleX));
	

	mDirection = glm::normalize(mDirection);

	mRight = glm::cross(mDirection,glm::vec3(0,1,0));

	mUp = glm::cross(mRight,mDirection);

	float x = mCentre.x + r*sin(theta)*sin(alpha);
	float y = mCentre.y + r*cos(theta);
	float z = mCentre.z + r*sin(theta)*cos(alpha);

	mPosition = glm::vec3(x,y,z);
	mViewMatrix = glm::lookAt(mPosition,mCentre,mUp);

	//glm::mat4 view = glm::mat4(	mRight.x,		mRight.y,		mRight.z,		-glm::dot(mPosition,mRight),
	//	mUp.x,			mUp.y,			mUp.z,			-glm::dot(mPosition,mUp),
	//	mDirection.x,	mDirection.y,	mDirection.z,	-glm::dot(mPosition,mDirection),
	//	0,				0,				0,				1);
	//mViewMatrix = glm::transpose(view);
}

glm::mat4 tpCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void tpCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV,aspectRatio,near,far);
}

void tpCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void tpCamera::lookAround(float dX,float dY)
{
	alpha += dX;
	theta += dY;

	if (theta > 0.5 * pi)
		theta = 0.5  * pi;
	else if (theta < 0.2 * pi)
		theta = 0.2  *pi;

	float x = mCentre.x + r*sin(theta)*sin(alpha);
	float y = mCentre.y + r*cos(theta);
	float z = mCentre.z + r*sin(theta)*cos(alpha);

	mPosition = glm::vec3(x,y,z);

	/*float Z = sqrt( abs( r*r - mPosition.x*mPosition.x - mPosition.y*mPosition.x ));
	printf("Z = %f \n",Z);
	mPosition.z = Z;*/
	UpdateViewMatrix();
}

void tpCamera::setCentrePosition(float x, float z){
	mCentre = glm::vec3(x, 2.0f, z);
	UpdateViewMatrix();
}

void tpCamera::Walk(float dist)
{
	mPosition += dist * mDirection;
}

void tpCamera::Strafe(float dist)
{
	mPosition += dist *mRight;
}

void tpCamera::Fly(float dist)
{
	mPosition += dist * mUp;
}

glm::vec3 tpCamera::GetEyePosition()
{
	return mPosition;

}