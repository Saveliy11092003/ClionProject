//
// Created by user on 29.12.22.
//

#include "ProcessManager.h"

using Converters::samples;
using Converters::Consts::samplesInSec;
using Converters::AbstrConv;
using Converters::createConverter;
using ProcessManager::Consts::firstFileInd;
using ProcessManager::Consts::firstSmplInd;
using ProcessManager::Consts::zeroSecond;
using ProcessManager::Consts::secondFileInd;
using ProcessManager::Consts::secondSmplInd;

namespace ProcessManager {
    Manager::Manager(fileNames input, std::string configPath)
            : config(configPath),
              outputFile(input[Consts::outputInd], FileOptions::empty) {

        input.erase(input.begin());
        if (input.empty()) {
            throw Exceptions::WrongComandLineParameters();
        }
        for (auto iter : input) {
            WAVFile* file = new WAVFile(iter);
            inputs.push_back(file);
        }
        tmpFiles = { { new WAVFile("tmp1.wav", FileOptions::empty) },
                     { new WAVFile("tmp2.wav", FileOptions::empty) } };

        inputs[firstFileInd]->printFullHeader(tmpFiles[firstFileInd]);
        inputs[firstFileInd]->printFullHeader(tmpFiles[secondFileInd]);
        /*tmpFiles[firstFileInd]->setHeader(inputs[firstFileInd]->getHeader());
        tmpFiles[secondFileInd]->setHeader(inputs[firstFileInd]->getHeader());*/
    }

    Manager::~Manager() {
        for (auto iter : inputs) {
            iter->~WAVFile();
        }
    }

    void Manager::makeOutputFile() {
        samples smpls;
        short smpl1[samplesInSec], smpl2[samplesInSec];
        smpls.push_back(smpl1);
        smpls.push_back(smpl2);
        WAVFile* convInput = inputs[firstSmplInd];


        while (true) {
            std::string comand = config.getNewComand();
            if (comand == Config::Consts::endOfFileLine) {
                break;
            }
            ConvArgs args = getArgs(comand);

            int begin = 0, end = args.times[firstSmplInd];
            tmpFiles[tmpInd]->openFile(FileOptions::out);
            convInput->printFullHeader(tmpFiles[tmpInd]);
            tmpFiles[tmpInd]->printInterval(begin, end, convInput);

            int second = end;
            end = findEnd(args, convInput);
            AbstrConv* conv = createConverter(args.name);
            if (!conv->checkInput(args)) {
                throw Exceptions::WrongParameters();
            }

            if (args.files.size() > 0) {
                for (; second < end; ++second) {
                    if (second > args.files[firstFileInd]->getLength()) {
                        end = second;
                        break;
                    }
                    args.files[firstFileInd]->readNextSecond(smpls[secondSmplInd], second);
                    convInput->readNextSecond(smpls[firstSmplInd], second);
                    conv->makeChanges(smpls);
                    tmpFiles[tmpInd]->printSecond(smpls[firstSmplInd], second);
                }
            }
            else {
                for (; second < end; ++second) {
                    convInput->readNextSecond(smpls[firstSmplInd], second);
                    conv->makeChanges(smpls);
                    tmpFiles[tmpInd]->printSecond(smpls[firstSmplInd], second);
                }
            }

            begin = end, end = convInput->getLength();
            tmpFiles[tmpInd]->printInterval(begin, end, convInput);
            tmpFiles[tmpInd]->closeFile();


            convInput = tmpFiles[tmpInd];
            ++tmpInd %= 2;
        }
        ++tmpInd %= 2;
        outputFile = tmpFiles[tmpInd];
    }

    ConvArgs Manager::getArgs(std::string comand) {
        std::stringstream ss(comand);
        ConvArgs args;
        ss >> args.name;
        if (comandsNames.find(args.name) == comandsNames.end()) {
            throw Exceptions::WrongParameters();
        }
        std::string arg;
        ss >> arg;
        while (!ss.fail()) {
            if (arg[0] == Consts::filePointer) {
                //int fileInd = atoi(arg.substr(1, arg.size()).c_str());
                args.files.push_back(getFile(arg));
            }
            else {
                args.times.push_back(atoi(arg.c_str()));
            }
            ss >> arg;
        }
        int time = 0;
        for (auto iter : args.times) {
            if (iter < time) {
                throw Exceptions::WrongParameters();
            }
            time = iter;
        }
        return args;
    }

    WAVFile* Manager::getFile(std::string wavPtr) {
        int indSize = wavPtr.size();
        std::string ind = wavPtr.substr(Consts::indPosInPtr, indSize);
        int index = atoi(ind.c_str()) - 1; // -1 to begin with 0
        if (index >= inputs.size()) {
            throw Exceptions::WrongParameters();
        }
        return inputs[index];
    }

    int Manager::findEnd(ConvArgs args, WAVFile* file) {
        if (args.times.size() < 2) {
            return file->getLength();
        }
        return std::min<int>(args.times[1], file->getLength());
    }

}