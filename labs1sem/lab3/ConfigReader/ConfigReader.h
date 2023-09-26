//
// Created by user on 29.12.22.
//

#ifndef LAB3_CONFIGREADER_H
#define LAB3_CONFIGREADER_H

#include <fstream>
#include <iostream>
#include <string>
#include "../Exceptions/Exceptions.h"
#include "../Consts/Consts.h"

namespace Config {

    class CnfReader {
    public:
        CnfReader() = delete;

        CnfReader(std::string path);

        ~CnfReader();

        std::string getNewComand();

    private:
        std::fstream config;
    };
}


#endif //LAB3_CONFIGREADER_H
