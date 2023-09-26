//
// Created by user on 29.12.22.
//

#ifndef LAB3_PROCESSMANAGER_H
#define LAB3_PROCESSMANAGER_H

#include <sstream>
#include <string>
#include <vector>
#include "../ConfigReader/ConfigReader.h"
#include "../Consts/Consts.h"
#include "../Converter/Converter.h"
#include "../WaveEdit/WaveEdit.h"
#include "../Exceptions/Exceptions.h"

using WAV::WAVFile;
using Converters::ConvArgs;
using Config::CnfReader;
using Converters::Consts::comandsNames;
using Converters::AbstrConv;
using AbstrConvsAndArgs = std::vector<std::pair<AbstrConv*, ConvArgs>>;
using WAV::Consts::FileOptions;

namespace ProcessManager {
    class Manager {
    public:
        Manager(fileNames input, std::string configPath);

        ~Manager();

        Manager() = delete;

        void makeOutputFile();

        ConvArgs getArgs(std::string);

        WAVFile* getFile(std::string wavPtr);

        int findEnd(ConvArgs, WAVFile* file);

    private:
        int tmpInd = Consts::firstFileInd;

        CnfReader config;

        WAVFiles tmpFiles;

        WAVFile outputFile;

        WAVFiles inputs;

    };

}


#endif //LAB3_PROCESSMANAGER_H
