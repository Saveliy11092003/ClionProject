//
// Created by user on 29.12.22.
//

#include "Exceptions.h"

namespace Exceptions {
    //canNotOpenFile
    CanNotOpenFile::CanNotOpenFile() {
        std::cerr << "can not open file";
    }

    int CanNotOpenFile::errorCode() const {
        return 1;
    }

    //canNotOpenFile
    InapropriateFile::InapropriateFile() {
        std::cerr << "inapropriate file";
    }

    int InapropriateFile::errorCode() const {
        return 2;
    }

    //outOfRange
    OutOfRange::OutOfRange() {
        std::cerr << "position is out of range";
    }

    int OutOfRange::errorCode() const {
        return 3;
    }

    //InapropriateConv
    InapropriateConv::InapropriateConv() {
        std::cerr << "wrong converter is passed";
    }

    int InapropriateConv::errorCode() const {
        return 4;
    }

    //WrongParameters
    WrongParameters::WrongParameters() {
        std::cerr << "wrong parameters for a converter";
    }

    int WrongParameters::errorCode() const {
        return 5;
    }

    //WrongComandLineParameters
    WrongComandLineParameters::WrongComandLineParameters() {
        std::cerr << "wrong comand line parameters";
    }

    int WrongComandLineParameters::errorCode() const {
        return 6;
    }

}