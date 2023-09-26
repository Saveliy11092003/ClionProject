//
// Created by user on 29.12.22.
//

#include "ConfigReader.h"

namespace Config {

    CnfReader::CnfReader(std::string path) {
        config.open(path, std::ios::in | std::ios::binary);
        if (config.fail()) {
            throw Exceptions::CanNotOpenFile();
        }
    }

    std::string CnfReader::getNewComand() {
        std::string newLine = { Consts::commentDelim };
        while (newLine[Consts::fitstElInd] == Consts::commentDelim || newLine.empty()) {
            if (config.eof()) {
                return Consts::endOfFileLine;
            }
            std::getline(config, newLine);
        }
        return newLine;
    }

    CnfReader::~CnfReader() {
        config.close();
    }

}