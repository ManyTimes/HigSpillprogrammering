#include "../Header/sound.h"

namespace cgl
{
		//Constructor takes a physical sound file on your system, path + name
	Sound::Sound(std::string soundFile, bool PlayAsynchronous, bool LoopSound)
	{
		this->soundfile = soundFile;
		this->asynchronous = PlayAsynchronous;
		this->loopsound = LoopSound;
		this->stopsounds = false;
	}

	//Constructor takes a physical sound file on your system, path + name
	Sound::Sound(std::string soundFile, bool PlayAsynchronous, bool LoopSound, bool StopOtherSoundsUponPlaying)
	{
		this->soundfile = soundFile;
		this->asynchronous = PlayAsynchronous;
		this->loopsound = LoopSound;
		this->stopsounds = StopOtherSoundsUponPlaying;
	}

	//Constructor takes a physical sound file on your system, path + name
	Sound::Sound(std::string soundFile, bool PlayAsynchronous)
	{
		this->soundfile = soundFile;
		this->asynchronous = PlayAsynchronous;
		this->loopsound = false;
		this->stopsounds = false;
	}

	//Starts playing the sound immidateley
	void Sound::Play()
	{
		if(this->asynchronous == true)
		{
			if(this->loopsound == true)
			{
				if(this->stopsounds == true)
				{
					PlaySound(this->soundfile.c_str(), NULL, SND_ASYNC | SND_LOOP);
				}
				else
				{
					PlaySound(this->soundfile.c_str(), NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
				}
			}
			else
			{
				if(this->stopsounds == true)
				{
					PlaySound(this->soundfile.c_str(), NULL, SND_ASYNC);
				}
				else
				{
					PlaySound(this->soundfile.c_str(), NULL, SND_ASYNC | SND_NOSTOP);
				}
			}
		}
		else
		{
			if(this->loopsound == true)
			{
				cgl::Cout("Cannot play a sound synchronously and looping the sound. Infinity loop.");
			}
			if(this->stopsounds == true)
			{
				PlaySound(this->soundfile.c_str(), NULL, SND_SYNC);
			}
			else
			{
				PlaySound(this->soundfile.c_str(), NULL, SND_ASYNC | SND_NOSTOP);
			}
		}
	}

	//Stops playing the sound immidateley
	void Sound::Stop()
	{
		PlaySound(NULL, NULL, NULL);
	}

}