// This header file was auto-generated by ClassMate++
// Created: 5 Nov 2015 9:23:18 am
// Copyright (c) 2015, HurleyWorks

#pragma once

#include "../../../NewtonAPI.h"
#include "PhysicsDefaults.h"

typedef std::shared_ptr<class PhysicsEngine> PhysicsEngineRef;

class PhysicsEngine
{

 public:
	static PhysicsEngineRef create(NewtonWorld * const world) { return std::make_shared<PhysicsEngine>(world); }

 public:
	PhysicsEngine (NewtonWorld * const world);
	~PhysicsEngine() = default;

	PhysicsEngine & operator=(const PhysicsEngine&) = delete;
	PhysicsEngine(const PhysicsEngine&) = delete;

	void advancePhysics();
	void debug() { db = true; }
	
 private:
	NewtonWorld * const world;
	bool db = false;

	// timing
	float graphicsFrameRate_ = DEFAULT_FRAMERATE;
	unsigned substeps_ = DEFAULT_SUBSTEPS;
	float timeStep_ = graphicsFrameRate_ / substeps_;

}; // end class PhysicsEngine
