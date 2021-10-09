#pragma once

struct ADSREnvelope {
	
	ADSREnvelope(double attack, double sustain, double attackTime, double decayTime, double releaseTime, bool sustainable = true)
		: attack(attack),
		sustain(sustain),
		attackTime(attackTime),
		decayTime(decayTime),
		releaseTime(releaseTime),
		sustainable(sustainable)
	{

	}

	double attack, sustain;
	double attackTime, decayTime, releaseTime;
	bool sustainable;
};

class Envelope {

public:
	Envelope(const ADSREnvelope adsr);
	Envelope();
	virtual ~Envelope();

	double getAmplitude() const;
	void update(double deltaTime);
	void setADSR(const ADSREnvelope adsr);
	void hold();
	void release();

private:
	enum Curves {
		ATTACK,
		DECAY,
		SUSTAIN,
		RELEASE,
		INACTIVE
	} mCurrentCurve;

	ADSREnvelope mADSR;

	bool mHold;
	double mAmplitude;
};