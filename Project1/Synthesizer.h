#pragma once


#include<vector>
#include<SDL.h>
#include"SoundGenerator.h"

struct SynthData {
	double* time;
	double sampleDeltaTime;
	std::vector<SoundGenerator*> soundGenerators;
	//std::vector<SynthMiddleware*> middleware;
};

class Synthesizer {

public:
	Synthesizer(unsigned int samplingRates = 48000, unsigned int numFrames = 20);
	virtual ~Synthesizer();

	void open();
	void close();
	void pause();
	void unpause();
	void addSoundGenerator(SoundGenerator* soundGenerator);
	//void addMiddleware(SynthMiddleware* middleware);

private:
	SDL_AudioDeviceID mDeviceID;
	double mTime;
	unsigned int mSamplingRate;
	unsigned int mNumFrames;

	SynthData mSynthData;
};