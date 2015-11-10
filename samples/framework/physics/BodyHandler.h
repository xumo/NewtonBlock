// This header file was auto-generated by ClassMate++
// Created: 5 Nov 2015 10:20:56 am
// Copyright (c) 2015, HurleyWorks

#pragma once

#include "BodyOps.h"
#include "PhysicsBody.h"
#include "util/SharedQueue.h"

class BodyHandler
{
	typedef threadsafe_stack<PhysicsBodyRef> BodyStack;

 public:
	BodyHandler (NewtonWorld * const world);
	~BodyHandler() = default;
	
	void processPhysicsBody(PhysicsBodyRef & pBody, EngineState engineState);
	void setBodyPose(PhysicsBodyRef & pBody);
	void resetPhysicsProperties(PhysicsBodyRef & pBody);

	// these calls come from Newton's thread!
	void onPostPhysicsUpdate(void * const userData, bool abort, float timeStep);
	void onPrePhysicsUpdate(void * const userData, bool abort, float timeStep) {}
		
 private:
	BodyOps ops;

	// must use thread safe containers here because Newton's
	// thread may be popping while the processBody thread is pushing
	BodyStack pendingAdds;
	BodyStack pendingRemoves_;

	void processNewBody(PhysicsBodyRef & pBody);
	void processBodyRemoval(PhysicsBodyRef & pBody);

}; // end class BodyHandler
