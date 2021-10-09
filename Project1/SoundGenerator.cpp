#include <algorithm>
#include"SoundGenerator.h"

static const double MAX_AMPLITUDE = 10000;

SoundGenerator::SoundGenerator() :
	mAmplitude(MAX_AMPLITUDE) {

}

SoundGenerator::~SoundGenerator() {

}

double linearToLog(double linear) {
	return (exp(linear) - 1) / 1.718;
}

double logToLinear(double logarithmic) {
	return log((logarithmic * 1.718) + 1);
}

void SoundGenerator::setVolume(double percent) {

	percent = std::max(percent, 0.0);
	percent = std::min(percent, 100.0);
	mAmplitude = linearToLog(percent / 100) * MAX_AMPLITUDE;
}

double SoundGenerator::getVolume() {
	return logToLinear(mAmplitude / MAX_AMPLITUDE) * 100;
}

double SoundGenerator::getAmplitude() {
	return mAmplitude;
}