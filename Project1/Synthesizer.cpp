#include"Synthesizer.h"

void fillBuffer(void *userData, Uint8 *buffer, int length) {

	Sint16* sampleBuffer = (Sint16*)buffer;
	SynthData* synthData = (SynthData*)userData;
	double sampleDeltaTime = synthData->sampleDeltaTime;

	int numToWrite = length / (sizeof(Sint16) * 2);
	
	for (int sample = 0; sample < numToWrite; sample++) {
		
		Sint16 sampleValue = 0;
		*(synthData->time) += sampleDeltaTime;

		for (auto it = synthData->soundGenerators.begin(); it != synthData->soundGenerators.end(); ++it) {
			sampleValue += (Sint16)((*it)->sample(*(synthData->time)) * (*it)->getAmplitude());
		}

		*sampleBuffer++ = sampleValue;
		*sampleBuffer++ = sampleValue;

	}

}

Synthesizer::Synthesizer(unsigned int samplingRate, unsigned int numFrames)
	: mSamplingRate(samplingRate), mNumFrames(numFrames)
{
	mSynthData.sampleDeltaTime = 1.0 / (double)mSamplingRate;
	mSynthData.time = &mTime;
}

Synthesizer::~Synthesizer() {

}

void Synthesizer::addSoundGenerator(SoundGenerator* soundGenerator) {
	mSynthData.soundGenerators.push_back(soundGenerator);
}

void Synthesizer::open() {

	mTime = 0;

	SDL_AudioSpec obtained = {};
	SDL_AudioSpec requested = {};
	requested.freq = mSamplingRate;
	//requested.samples = mSamplingRate / mNumFrames;
	requested.samples = 1024;
	requested.format = AUDIO_S16SYS;
	requested.channels = 2;
	requested.userdata = &mSynthData;
	requested.callback = &fillBuffer;

	mDeviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtained, 0);

}

void Synthesizer::close() {
	SDL_CloseAudioDevice(mDeviceID);
}

void Synthesizer::unpause() {
	SDL_PauseAudioDevice(mDeviceID, 0);
}

void Synthesizer::pause() {
	SDL_PauseAudioDevice(mDeviceID, 1);
}