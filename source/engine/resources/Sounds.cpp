#include "Sounds.h"

Sounds::SoundEngineWrapper::SoundEngineWrapper()
{
	soundEngine = irrklang::createIrrKlangDevice();
}
Sounds::SoundEngineWrapper::~SoundEngineWrapper()
{
	soundEngine->drop();
}

Sounds::Sounds()
{

}

irrklang::ISound* Sounds::playSound(const std::string& path, bool repeat, bool paused )
{
	return soundEngine.soundEngine->play2D(path.c_str(), repeat, paused);
}

Sounds::SoundEngineWrapper Sounds::soundEngine = Sounds::SoundEngineWrapper() ;