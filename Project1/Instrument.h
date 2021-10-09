#pragma once

#include <functional>
#include "SoundGenerator.h"

class Instrument : public SoundGenerator {

public:
	Instrument(std::function<double(double, double)> wave);
	virtual ~Instrument();

	virtual double sample(double time) = 0;
	virtual void holdNote(double frequency) = 0;
	virtual void releaseNote(double frequency) = 0;

protected:
	std::function<double(double, double)> mWave;
};