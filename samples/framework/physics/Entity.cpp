// This source file was auto-generated by ClassMate++
// Created: 18 Apr 2015 9:28:00 am
// Copyright (c) 2015, HurleyWorks

#include "Entity.h"
#include "PhysicsBody.h"
#include <string>

using namespace ci;

// applyForceAndTorqueCallback
void Entity::applyForceAndTorqueCallback(const NewtonBody * newtonBody,
									     dFloat timestep,
										 int threadIndex)
{

	PhysicsBody * const pBody = (PhysicsBody*)NewtonBodyGetUserData(newtonBody);
	if (!pBody) return;

	dFloat Ixx;
	dFloat Iyy;
	dFloat Izz;
	dFloat mass;
	NewtonBodyGetMassMatrix(newtonBody, &mass, &Ixx, &Iyy, &Izz);

	dVector gravityForce;
	for (int i = 0; i < 3; i++)
		gravityForce[i] = mass * pBody->desc.force[i];

	NewtonBodySetForce(newtonBody, &gravityForce[0]);

	// add the emit impulse if any
	if (pBody->state.isEmitted() && pBody->st.speed > 0.0f)
	{
		vec3 f = pBody->st.direction * pBody->st.speed;
		
		//http://stackoverflow.com/questions/17918033/glm-decompose-mat4-into-translation-and-rotation
		vec3 translate = glm::vec3(pBody->st.worldTransform[3]); 

		dVector impulse(f[0], f[1], f[2]);
		dVector pos(translate[0], translate[1], translate[2]);
		NewtonBodyAddImpulse(newtonBody, &impulse.m_x, &pos.m_x);

		pBody->state.getState() ^= PBodyState::HasImpulseApplied;
	}
}

// destroyBodyCallback
void Entity::destroyBodyCallback(const NewtonBody * newtonBody)
{
	PhysicsBody * const pBody = (PhysicsBody*)NewtonBodyGetUserData(newtonBody);
	if (!pBody) return;

	pBody->userData = nullptr;
}

// transformCallback
void Entity::transformCallback(const NewtonBody * newtonBody,
									 const dFloat * matrix,
									 int threadIndex)
{
	PhysicsBody * const pBody = (PhysicsBody*)NewtonBodyGetUserData(newtonBody);
	if (!pBody) return;
	
	pBody->st.worldTransform = glm::make_mat4(matrix);
}