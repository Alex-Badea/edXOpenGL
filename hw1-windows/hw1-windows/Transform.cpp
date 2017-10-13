// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include "glm/ext.hpp"
#include <iostream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	float theta = glm::radians(degrees);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	glm::mat3 aaT = glm::mat3(x*x, x*y, x*z, x*y, y*y, y*z, x*z, y*z, z*z);
	glm::mat3 AStar = glm::mat3(0, z, -y, -z, 0, x, y, -x, 0);

	return glm::cos(theta)*glm::mat3() +
		(1 - glm::cos(theta))*aaT +
		glm::sin(theta)*AStar;
	// You will change this return call
	// return mat3();
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	std::cout << "eye: " << glm::to_string(eye) <<
		"; up: " << glm::to_string(up) << std::endl;

	//Interpretation: "rotate eye vector about the up axis by degrees degrees";
	eye = Transform::rotate(degrees, up)*eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	std::cout << "eye: " << glm::to_string(eye) <<
		"; up: " << glm::to_string(up) << std::endl;

	//We rotate the eye about a new reference axis;
	//Our new reference axis is the normalized cross product of up and eye;
	glm::vec3 refAxis = glm::normalize(glm::cross(up, eye));
	//Interpretation: "rotate eye vector about the reference axis by -degrees degrees";
	eye = Transform::rotate(-degrees, refAxis)*eye;
	//The old up direction is now degenerate; our new up direction is
	//given by the normalized cross product of eye and reference axis;
	up = glm::normalize(glm::cross(eye, refAxis));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	const glm::vec3 center(0.0, 0.0, 0.0);

	//Creating a new coordinate frame for the camera:
	//Obtaining the forward axis;
	glm::vec3 f = glm::normalize(center - eye);
	//Obtaining the upward axis;
	glm::vec3 u = glm::normalize(up);
	//Obtaining the sideways axis;
	glm::vec3 s = glm::normalize(glm::cross(f, u));

	//Negating the values on the forward vector due to the camera looking down -z direction;
	glm::mat4 rotMat(s.x, u.x, -f.x, 0,  s.y, u.y, -f.y, 0,  s.z, u.z, -f.z, 0,  0, 0, 0, 1);
	//Translating the eye to the origin;
	glm::mat4 transMat(1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  -eye.x, -eye.y, -eye.z, 1);
	
	//Rotation first, translation afterwards!
	//We want to make sure we're translating with respect to the
	//newly created coordinate frame of the camera;
	return rotMat*transMat;
	//SAFETY WARNING: the following is what happens when you translate prior to rotating (not good!):
	//return transMat*rotMat;

	// You will change this return call
	// return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}