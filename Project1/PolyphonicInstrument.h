#pragma once

#include<vector>
#include<mutex>

#include"Instrument.h"
#include"Envelope.h"

class PolyphonicInstrument : public Instrument {

public:
	PolyphonicInstrument(
		std::function<double(double, double)> wave,
		const ADSREnvelope& adsr);

	virtual ~PolyphonicInstrument();
	
	double sample(double time);
	void holdNote(double frequency);
	void releaseNote(double frequency);

private:
	ADSREnvelope mADSR;

	std::mutex mEnvLock;
	std::vector<std::pair<double, Envelope>> mEnvelopes;

	double mPrevSample;
};