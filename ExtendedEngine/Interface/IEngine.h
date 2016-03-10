#pragma once
#include "TL-Engine.h"
#include "IAnimation.h"
#include "IParticleEmitter.h"
#include "IUsings.h"

namespace tle
{
	class IEngine : public I3DEngine
	{
	public:
		/***************************************************
							New functions
		****************************************************/

		/////////////
		//Animation//

		//Creates an animation at the given location
		//Runs through the frames at a tick rate
		//Return 0 if failed to load any of the animation frames
		virtual IAnimation* CreateAnimation(const std::vector<string>& frameList,
								const CVector3& position	= CVector3(0.0f, 0.0f, 0.0f),	/*Default location is the origin*/
								const float		tickRate	= 0.1f,							/*Default rate is 10 frames per second*/
								const bool		looped		= true							/*Set to loop the frames by default*/
							) = 0;

		//Creates an animation at the given location
		//Runs through the frames at a tick rate
		//Return 0 if failed to load any of the animation frames
		virtual IAnimation* CreateAnimation(string& name, string& extension, int amount,
								const CVector3& position	= CVector3(0.0f, 0.0f, 0.0f),	/*Default location is the origin*/
								const float		tickRate	= 0.1f,							/*Default rate is 10 frames per second*/
								const bool		looped		= true							/*Set to loop the frames by default*/
							) = 0;

		//Remove the animation if it exists
		virtual void RemoveAnimation(IAnimation* pAnimation) = 0;

		////////////////////
		//Particle Emitter//

		//Create a particle emitter at the given location
		virtual IParticleEmitter* CreateEmitter(EEmissionType type,
								const string&	particleSprite	= PARTICLE_TEXTURE,				/*Default texture is Transparent.png*/
								const float		emissionRate	= 0.01f,						/*Default spawn rate of the particles*/
								const CVector3& position		= CVector3(0.0f, 0.0f, 0.0f)	/*Default location is the origin*/
							) = 0;

		//Create a particle emitter at the given location
		virtual IParticleEmitter* CreateEmitter(EEmissionType type,
								const std::vector<string>&	particleSprite,						/*Animated texture*/
								const float		emissionRate	= 0.01f,						/*Default spawn rate of the particles*/
								const CVector3& position		= CVector3(0.0f, 0.0f, 0.0f)	/*Default location is the origin*/
							) = 0;

		//Remove the particle emitter if it exists
		virtual void RemoveEmitter(IParticleEmitter* emitter) = 0;

		/***************************************************
						Additional Controls
		****************************************************/

		//Pauses any auto updated entity eg animations and particles
		virtual void PauseAutoUpdates() = 0;

		//Unpauses any auto updated entities eg animations and particles
		virtual void UnpauseAutoUpdates() = 0;
	};
}