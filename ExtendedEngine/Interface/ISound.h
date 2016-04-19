#pragma once
#include "SFML\Audio\SoundSource.hpp"

namespace tle
{
	enum SoundType {SFX, Ambient, Music, Interface, Global};

	//Sound interface that manages a sf::sound object adding some controls and hiding others
	class ISound
	{
	public:
		//Sets the type of sound
		virtual void SetType(SoundType type) = 0;

		//Sets the volume of the sound
		virtual void SetVolume(float volume) = 0;

		//Set whether or not the sound should loop after reaching the end
		virtual void SetLoop(bool loop) = 0;
	
		//Start or resume playing the sound
		virtual void Play() = 0;

		//Pause the sound, Play() will resume
		virtual void Pause() = 0;

		//Stops the sound, Play() will restart
		virtual void Stop() = 0;

		//Gets the sound type
		virtual SoundType GetType() = 0;

		//Gets the sound's unmodified volume
		virtual float GetVolume() = 0;

		//Gets whether the sound will loop
		virtual bool IsLooped() = 0;

		//Returns whether the sound is currently playing, paused, or stopped
		virtual sf::SoundSource::Status GetStatus() = 0;
	};
}