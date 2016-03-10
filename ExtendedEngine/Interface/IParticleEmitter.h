#pragma once
#include <SceneNode.h>
#include <Mesh.h>
#include <Camera.h>
#include "IUsings.h"

namespace tle
{
	enum EEmissionType { Sphere, Circle, Cone, Arch, Line };

	const float FASTEST_EMISSION_RATE = 0.0099f;
	const string PARTICLE_MODEL = "Quad.x";
	const string PARTICLE_TEXTURE = "Transparent.png";

	class IParticleEmitter : virtual public ISceneNode
	{
	public:
		/************************************
				  Update Controls
		*************************************/

		//Starts the emitter spawning particles, default off
		virtual void Start() = 0;

		//Stops the emitter spawning particles
		virtual void Stop() = 0;

		//Sets all particles to the despawned (inactive) state
		virtual void Reset() = 0;

		//Clears local cache of particles
		//Returns all particles back to the engine
		virtual void Clear() = 0;

		//Do not call
		//Called from the engine to auto update the particles and emitter
		virtual void Update(float delta) = 0;

		//Do not call
		//Called from the engine to orientate the particles
		//To either face or hide behind the camera
		virtual void OrientateParticles(ICamera* camera) = 0;
		
		/************************************
						Sets
		*************************************/

		///////////
		//Emitter//

		//Emission type decides what direction the particles are emitted
		virtual void SetEmissionType(EEmissionType type) = 0;

		//Set the variance in the direction the particles are emitted
		//Only affects non circular/linear emissions.
		virtual void SetEmissionAngle(float angle) = 0;

		//Set the amount of time in seconds between particles being emitted
		//Note: A rate less than 0.001 (>1000 active particles) will be treated an no emission
		virtual void SetEmissionRate(float rate) = 0;

		////////////
		//Particle//

		//Set the time in seconds that the particles last
		virtual void SetParticleLife(float life) = 0;

		//Set the texture used for the particle's quad model
		virtual void SetParticleSkin(string& skin) = 0;

		//Set the base velocity of the particles
		//Does not retroactively change velcoity of existing particles
		virtual void SetParticleVelocity(CVector3& vel) = 0;

		//Set the acceleration of the particles
		//Also changes acceleration of existing particles
		virtual void SetParticleAcceleration(CVector3& acl) = 0;

		//Set the scale of the particle quad model
		//Does not retroactively change scale of existing particles
		virtual void SetParticleScale(float scale) = 0;

		/************************************
						Gets
		*************************************/

		///////////
		//Emitter//

		//Returns the emission area
		virtual EEmissionType GetEmissionType() = 0;

		//Returns the angle of variance that the particles are being emitted at
		virtual float GetEmissionAngle() = 0;

		//Returns the time in seconds between particle emissions
		virtual float GetEmissionRate() = 0;

		//Returns true is the emitter is emitting particles
		virtual bool IsEmitting() = 0;

		//Returns true if one or more of the emitter particles are still alive
		virtual bool HasActiveParticles() = 0;

		////////////
		//Particle//

		//Returns how long the particles live
		virtual float GetParticleLife() = 0;

		//Returns the texture used for the particle's quad model
		virtual string GetParticleSkin() = 0;

		//Returns the base velocity of the particles
		virtual tlx::CVector3 GetParticleVelocity() = 0;

		//Returns the acceleration of the particles
		virtual tlx::CVector3 GetParticleAcceleration() = 0;

		//Returns the scale of the particle quad model
		virtual float GetParticleScale() = 0;

		/************************************
				 Goodbye Cruel World
		*************************************/

		virtual ~IParticleEmitter() {};
	};
}