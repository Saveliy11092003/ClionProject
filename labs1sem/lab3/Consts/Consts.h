//
// Created by user on 29.12.22.
//

#ifndef LAB3_CONSTS_H
#define LAB3_CONSTS_H

#pragma once
#include<string>
#include<vector>
#include<set>

namespace WAV {

    struct WAVHeader {
        int RIFFId;
        int chunkDataSize;
        int WAVEId;
        int FMTId;
        int subChunkDataSize;
        short compresionCode;
        short numberOfChanels;
        int sampleRate;
        int avBytesPerSec;
        short blockAlign;
        short bitsPerSample;
        char LISTId[4];
        int subChunk2DataSize;
        char INFOId[4];
        int INFOVal;
    };

    namespace Consts {
        const short bitsPerSample = 16;
        const int sampleRate = 44100;
        const short chanels = 1;
        const short PCM = 1;
        const char RIFF[5] = "RIFF";
        const char FMT[5] = "fmt ";
        const char WAVE[5] = "WAVE";
        const int RIFFId = *((int*)RIFF);
        const int FMTId = *((int*)FMT);
        const int WAVEId = *((int*)WAVE);

        const int headerSize = sizeof(WAVHeader);

        enum class FileOptions {
            in,
            out,
            empty,
        };
    }
}

namespace Converters {

    namespace Consts {
        const int samplesInSec = WAV::Consts::sampleRate;
        const short int zeroValue = 0;
        const std::set< std::string> comandsNames =
                {
                        "mute", "mix", "overlap"
                };
    }

    using Times = std::vector<int>;
    using samples = std::vector<short*>;
}

namespace Config {
    namespace Consts {
        const int fitstElInd = 0;
        const char commentDelim = '#';
        const std::string endOfFileLine = "";
    }

}

namespace ProcessManager {
    using fileNames = std::vector<std::string>;
    namespace Consts {
        const int outputInd = 0;
        const int inputInd = 1;
        const char filePointer = '$';
        const int indPosInPtr = 1;
        const int firstFileInd = 0;
        const int firstSmplInd = 0;
        const int zeroSecond = 0;
        const int secondFileInd = 1;
        const int secondSmplInd = 1;
    }

}

#endif //LAB3_CONSTS_H
