#include<iostream>
#include<SDL.h>
#include<vector>
#include"Notes.h"
#include"Instrument.h"
#include"PolyphonicInstrument.h"
#include"Envelope.h"
#include"Waveforms.h"
#include"Synthesizer.h"
#include<map>


struct PianoKey
{
    char key;
    double frequency;
};

std::vector<PianoKey> pianoKeys = {
    {SDLK_q, Notes::C4},
    {SDLK_2, Notes::Cs4},
    {SDLK_w, Notes::D4},
    {SDLK_3, Notes::Ds4},
    {SDLK_e, Notes::E4},
    {SDLK_r, Notes::F4},
    {SDLK_5, Notes::Fs4},
    {SDLK_t, Notes::G4},
    {SDLK_6, Notes::Gs4},
    {SDLK_y, Notes::A4},
    {SDLK_7, Notes::As4},
    {SDLK_u, Notes::B4},
    {SDLK_i, Notes::C5},
    {SDLK_9, Notes::Cs5},
    {SDLK_o, Notes::D5},
    {SDLK_0, Notes::Ds5},
    {SDLK_p, Notes::E5} };



int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Piano Example",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN);

    double (*piano1)(double, double) = [](double freq, double time) {
        return 0.5 * (Waveforms::sine(freq, time) +
            0.5 * Waveforms::sine(freq * 2, time) +
            0.25 * Waveforms::sine(freq * 4, time) +
            0.125 * Waveforms::sine(freq * 8, time));
    };

    double (*SawWave)(double, double) = [](double freq, double time) {
        return Waveforms::sawtooth(freq, time);
    };
    double (*SineWave)(double, double) = [](double freq, double time) {
        return Waveforms::sine(freq, time);
    };

    ADSREnvelope pianoEnvelope(0.90f, 0.8f, 0.0f, 0.1f, 0.2f);
    Instrument* piano = new PolyphonicInstrument(piano1,pianoEnvelope);

    Synthesizer synth;
    synth.addSoundGenerator(piano);

    synth.open();
    synth.unpause();

    std::map<char, bool> pressedKeys;

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else {
                for (auto it = pianoKeys.begin(); it != pianoKeys.end(); it++) {
                    if (e.key.keysym.sym == it->key) {
                        if (e.type == SDL_KEYDOWN) {
                            if (!pressedKeys[it->key]) {
                                piano->holdNote(it->frequency);
                                pressedKeys[it->key] = true;
                            }
                        }
                        else if (e.type == SDL_KEYUP) {
                            piano->releaseNote(it->frequency);
                            pressedKeys[it->key] = false;
                        }
                    }

                }
            }
        }
    }

    synth.pause();
    synth.close();

    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}