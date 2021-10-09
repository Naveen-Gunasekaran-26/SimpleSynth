#include"Envelope.h"

Envelope::Envelope(const ADSREnvelope adsr)
	: mADSR(adsr), mHold(false), mAmplitude(0) {

}

Envelope::Envelope() 
	: mADSR({0,0,0,0,0}), mHold(false), mAmplitude(0) {

}

Envelope::~Envelope() {

}

double Envelope::getAmplitude() const {
	return mAmplitude;
}

void Envelope::update(double deltaTime) {

	double attackSlope = (mADSR.attack / mADSR.attackTime);
	double decaySlope = ((mADSR.attack - mADSR.sustain) / mADSR.decayTime);
	double releaseSlope = (mADSR.sustain / mADSR.releaseTime);

	switch (mCurrentCurve) {

	case Curves::ATTACK:
		mAmplitude += (attackSlope * deltaTime);
		if (mAmplitude >= mADSR.attack) {
			mAmplitude = mADSR.attack;
			mCurrentCurve = Curves::DECAY;
		}
		break;

	case Curves::DECAY:
		mAmplitude -= (decaySlope * deltaTime);
		if (mAmplitude <= mADSR.sustain) {
			mAmplitude = mADSR.sustain;
			mCurrentCurve = Curves::SUSTAIN;
		}
		break;

	case Curves::SUSTAIN:
		if (!mHold) {
			mCurrentCurve = Curves::RELEASE;
		}
		break;

	case Curves::RELEASE:
		mAmplitude -= (releaseSlope * deltaTime);
		if (mAmplitude <= 0) {
			mAmplitude = 0;
			mCurrentCurve = Curves::INACTIVE;
		}
		break;
	}
	if (mAmplitude <= 0.0001)
		mAmplitude = 0;
}

void Envelope::setADSR(const ADSREnvelope adsr) {
	mADSR = adsr;
}

void Envelope::hold() {
	mHold = mADSR.sustainable ? true : false;
	mCurrentCurve = Curves::ATTACK;
}

void Envelope::release() {
	mHold = false;
}