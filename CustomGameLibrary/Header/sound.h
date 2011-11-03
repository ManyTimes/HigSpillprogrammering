#ifndef _SOUND_H
#define _SOUND_H

#include "include.h"
#include "windows.h"
#include "function.h"

namespace cgl
{
	class DECLARE Sound
	{
	private:
		std::string soundfile;
		bool asynchronous;
		bool loopsound;
		bool stopsounds;
	public:
		Sound::Sound(std::string soundFile, bool PlayAsynchronous);
		Sound::Sound(std::string soundFile, bool PlayAsynchronous, bool LoopSound);
		Sound::Sound(std::string soundFile, bool PlayAsynchronous, bool LoopSound, bool StopOtherSoundsUponPlaying);
		void Sound::Play();
		void Sound::Stop();
	};
}

#endif