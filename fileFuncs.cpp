#include <cstdio>
#include <cstdint>
#include <cassert>
#include "noisemaker.h"

void writeWavHeaderFile(FILE *f, sample *inSamples, int numSamples, int sampleRateIn) {

    // Riff File Header
    const char fileId[] = "RIFF";
    // fileSize is computed later
    const char fileFormat[] = "WAVE";

    const char wavHeaderDescriptor[] = "fmt ";
    const int16_t compressionType = 1;
    const int16_t numChannels = 1;
    const int32_t sampleRate = sampleRateIn;
    const int16_t blockAlign = sizeof(sample) * numChannels; // The number of bytes for one sample including all channels
    const int32_t byteRate = sampleRate * blockAlign;
    const int16_t bitsPerSample = sizeof(sample) * 8;

    const int32_t wavHeaderSize = sizeof(compressionType) + sizeof(numChannels) + 
                                  sizeof(sampleRate) + sizeof(blockAlign) + 
                                  sizeof(byteRate) + sizeof(bitsPerSample);

    const char dataDescriptor[] = "data";
    const int32_t dataSize = numSamples * blockAlign;

    const int32_t fileSize = sizeof(fileFormat) + sizeof(wavHeaderDescriptor) + sizeof(wavHeaderSize) +
                             wavHeaderSize + sizeof(dataDescriptor) + sizeof(dataSize) + dataSize;

    fwrite(fileId, sizeof(char), 4, f);
    fwrite(&fileSize, sizeof(fileSize), 1, f);
    fwrite(fileFormat, sizeof(char), 4, f);
    fwrite(wavHeaderDescriptor, sizeof(char), 4, f);
    fwrite(&wavHeaderSize, sizeof(wavHeaderSize), 1, f);
    fwrite(&compressionType, sizeof(compressionType), 1, f);
    fwrite(&numChannels, sizeof(numChannels), 1, f);
    fwrite(&sampleRate, sizeof(sampleRate), 1, f);
    fwrite(&byteRate, sizeof(byteRate), 1, f);
    fwrite(&blockAlign, sizeof(blockAlign), 1, f);
    fwrite(&bitsPerSample, sizeof(bitsPerSample), 1, f);
    fwrite(&dataDescriptor, sizeof(dataDescriptor), 1, f);
    fwrite(&dataSize, sizeof(dataSize), 1, f);
    fwrite(inSamples, sizeof(sample), numSamples, f);
}