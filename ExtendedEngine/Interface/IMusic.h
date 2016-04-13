#pragma once
#include "ISound.h" //Only for the sound type enum

namespace tle
{
	//Music interface that manages a sf::music object adding some controls and hiding others
	class IMusic
	{
	public:
		//Sets the type of sound
		virtual void SetType(SoundType type) = 0;

		//Sets the volume of the music
		virtual void SetVolume(float volume) = 0;

		//Set whether or not the music should loop after reaching the end
		virtual void SetLoop(bool loop) = 0;

		//Start or resume playing the music
		virtual void Play() = 0;

		//Pause the music, Play() will resume
		virtual void Pause() = 0;

		//Stops the music, Play() will restart
		virtual void Stop() = 0;

		//Gets the music type
		virtual SoundType GetType() = 0;

		//Gets the music's unmodified volume
		virtual float GetVolume() = 0;

		//Gets whether the music will loop
		virtual bool IsLooped() = 0;

		//Returns whether the music is currently playing, paused, or stopped
		virtual sf::SoundSource::Status GetStatus() = 0;
	};
}