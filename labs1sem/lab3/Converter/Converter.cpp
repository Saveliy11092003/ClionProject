//
// Created by user on 29.12.22.
//

#include "Converter.h"

namespace Converters {
    AbstrConv* createConverter(std::string name) {
        if (factories.find(name) == factories.end()) {
            throw Exceptions::InapropriateConv();
        }
        return factories[name]->createConv();
    }

    //mute
    void Mute::makeChanges(samples smpls) {
        short* sample = smpls[0];
        for (int i = 0; i < Consts::samplesInSec; ++i) {
            sample[i] = Consts::zeroValue;
        }
    }

    bool Mute::checkInput(ConvArgs args) {
        return args.files.size() == numOfFiles && args.times.size() == numOfTimePoints ? 1 : 0;
    }

    void Mute::info() {
        std::cout << "mute:\n";
        std::cout << "mutes passed interval\n";
        std::cout << "this parameters must be past:\n";
        std::cout << "files: " << numOfFiles << ", timePoints: " << numOfTimePoints << '\n';
        std::cout << '\n';
    }

    //mix
    void Mix::makeChanges(samples smpls) {
        short* sample = smpls[0], *otherSample = smpls[1];
        for (int i = 0; i < Consts::samplesInSec; ++i) {
            sample[i] = (sample[i] + otherSample[i])/2;
        }
    }

    bool Mix::checkInput(ConvArgs args) {
        return args.files.size() == numOfFiles && args.times.size() == numOfTimePoints ? 1 : 0;
    }

    void Mix::info() {
        std::cout << "mix:\n";
        std::cout << "takes two files and mixes them - takes average sample\n";
        std::cout << "begining from passed timepoint and ending by the end of one of the files\n";
        std::cout << "this parameters must be past:\n";
        std::cout << "files: " << numOfFiles << ", timePoints: " << numOfTimePoints << '\n';
        std::cout << '\n';
    }

    //Overlap
    void Overlap::makeChanges(samples smpls) {
        short* sample = smpls[0], * otherSample = smpls[1];
        for (int i = 0; i < Consts::samplesInSec; ++i) {
            sample[i] = otherSample[i];
        }
    }

    bool Overlap::checkInput(ConvArgs args) {
        return args.files.size() == numOfFiles && args.times.size() == numOfTimePoints ? 1 : 0;
    }

    void Overlap::info() {
        std::cout << "overlap:\n";
        std::cout << "overlaps one file by another file - changes file's samples by another's\n";
        std::cout << "begining from passed timepoint and ending by the end of one of the files\n";
        std::cout << "this parameters must be past:\n";
        std::cout << "files: " << numOfFiles << ", timePoints: " << numOfTimePoints << '\n';
        std::cout << '\n';
    }

}