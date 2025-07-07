#ifndef SOUNDS_H
#define SOUNDS_H

#include <irrklang/irrKlang.h>
#include <string>

class Sounds
{
	class SoundEngineWrapper
	{
		irrklang::ISoundEngine* soundEngine;

		SoundEngineWrapper();
		~SoundEngineWrapper();

		friend class Sounds;
	};

	static SoundEngineWrapper soundEngine;

	Sounds();
	
public:

	static irrklang::ISound* playSound(const std::string& path, bool repeat = false, bool paused = false);
};

#endif