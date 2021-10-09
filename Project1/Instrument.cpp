#include "Instrument.h"

Instrument::Instrument(
	std::function<double(double,double)> wave) 
	: mWave(wave)
{

}

Instrument::~Instrument() {

}