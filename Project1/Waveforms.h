#pragma once
namespace Waveforms {

	const double pulse(double frequency, double time, double percent, double phase = 0);
	const double square(double frequency, double time, double phase = 0);
	const double sine(double frequency, double time, double phase = 0);
	const double sawtooth(double frequency, double time, double phase = 0);
	const double triangle(double frequency, double time, double phase = 0);
	const double noise();

};