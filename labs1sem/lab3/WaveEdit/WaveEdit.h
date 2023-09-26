//
// Created by user on 29.12.22.
//

#ifndef LAB3_WAVEEDIT_H
#define LAB3_WAVEEDIT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include "../Consts/Consts.h"
#include "../Exceptions/Exceptions.h"

using Converters::Consts::samplesInSec;
using WAV::Consts::FileOptions;

namespace WAV {

    class WAVFile {
    public:
        WAVFile() = delete;

        WAVFile(std::string path, FileOptions option = FileOptions::out);

        WAVFile* operator=(WAVFile* file);

        void goTo(int);

        void readNextSecond(short* sec, int secPos);

        int getLength();

        void printSecond(short* sec, int secPos);

        void openFile(FileOptions option);

        void closeFile();

        void printHeader(const WAVHeader* head);

        const WAVHeader* getHeader();

        void setHeader(const WAVHeader*);

        void printInterval(int beginSec, int endSec, WAVFile* toPrint);

        const void printFullHeader(WAVFile* newHeader);

    private:
        void checkFileFormat();

        std::string path;
        FileOptions op;
        std::fstream file;
        WAVHeader header;
        int length;
    };

    using WAVFiles = std::vector<WAVFile*>;

}


#endif //LAB3_WAVEEDIT_H
