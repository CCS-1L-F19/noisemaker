#include <vector>
#include "fileFuncs.h"
#include "noisemaker.h"
#include "signal.h"
#include "oscillator.h"
#include "constant.h"
#include "premadeSignals.h"
#include "adder.h"
#include "note.h"
using namespace std;

#define NOTE_DURATION 10000
#define NOTE_PAUSE 2000

int main() {
    //                                           D         A        G#       G        F        D        F        G
    std::vector<Note> phrase {{1,293}, {1,293}, {2,587}, {3, 440}, {2,415}, {2,392}, {2,349}, {1,293}, {1,349}, {1,392},
                            {1,261}, {1,261}, {2,587}, {3, 440}, {2,415}, {2,392}, {2,349}, {1,293}, {1,349}, {1,392},
                            {1,247}, {1,261}, {2,587}, {3, 440}, {2,415}, {2,392}, {2,349}, {1,293}, {1,349}, {1,392},
                            {1,233}, {1,261}, {2,587}, {3, 440}, {2,415}, {2,392}, {2,349}, {1,293}, {1,349}, {1,392},
                            };
    std::vector<writableSample> output {};

    Oscillator o = formSineWave();
    o.setAmpSignal(Constant(noisemaker::maxSample));

    for (Note n : phrase) {
        Adder a = formVibratoFreqSignal(n.frequency, 20, n.frequency * .2);
        o.setFrequencySignal(a);
        for (int i = 0; i < NOTE_DURATION * n.duration; i++) {
            output.push_back((writableSample) o.step());
        }
        o.setFrequencySignal(Constant(0));
        for (int i = 0; i < NOTE_PAUSE; i++) {
            output.push_back((writableSample) o.step());
        }
    }

    writeWavFile(fopen("megalovania.wav", "w"), &output[0], output.size(), noisemaker::sampleRate);
}