#pragma once

class SoundGenerator {

public:
	SoundGenerator();
	virtual ~SoundGenerator();

	virtual double sample(double time) = 0;
	void setVolume(double percent);
	double getVolume();
	double getAmplitude();

protected:
	double mAmplitude;

};