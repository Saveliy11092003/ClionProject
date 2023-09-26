//
// Created by user on 29.12.22.
//

#include "WaveEdit.h"


namespace WAV {

    WAVFile::WAVFile(std::string _path, FileOptions option)
            : path(_path) {
        if (option == FileOptions::empty) {
            length = 0;
            return;
        }
        file.open(path, std::ios::in | std::ios::binary);
        if (file.fail()) {
            throw Exceptions::CanNotOpenFile();
        }
        std::string str;
        std::getline(file, str);
        file.close();
        if (str.size() < sizeof(WAVHeader)) {
            throw Exceptions::InapropriateFile();
        }
        header = *(WAVHeader*)str.c_str();
        checkFileFormat();
        int firstEightBytes = 8;
        int bytes = (header.chunkDataSize + firstEightBytes) - Consts::headerSize;
        length = bytes / header.sampleRate / 2;
    }

    void WAVFile::printInterval(int beginSec, int endSec, WAVFile* toPrint) {
        short sec[samplesInSec];
        for (int second = beginSec; second < endSec; ++second) {
            toPrint->readNextSecond(sec, second);
            printSecond(sec, second);
        }
    }

    WAVFile* WAVFile::operator=(WAVFile* cpFile) {
        openFile(FileOptions::out);
        cpFile->printFullHeader(this);
        printInterval(0, cpFile->getLength(), cpFile);
        closeFile();
        return this;
    }

    void WAVFile::checkFileFormat() {
        if ( header.bitsPerSample != Consts::bitsPerSample
             || header.compresionCode != Consts::PCM
             || header.numberOfChanels != Consts::chanels
             || header.sampleRate != Consts::sampleRate
             || header.RIFFId != Consts::RIFFId
             || header.WAVEId != Consts::WAVEId
             || header.FMTId != Consts::FMTId)  {
            throw Exceptions::InapropriateFile();
        }
    }

    void WAVFile::goTo(int sec) {
        if (op == FileOptions::out) {
            file.seekp(header.avBytesPerSec * sec + Consts::headerSize + header.subChunk2DataSize);
        }
        else {
            file.seekg(header.avBytesPerSec * sec + Consts::headerSize + header.subChunk2DataSize);
        }
        if (file.fail()) {
            throw Exceptions::OutOfRange();
        }
    }

    void WAVFile::readNextSecond(short* sec, int secPos) {
        openFile(FileOptions::in);
        goTo(secPos);
        file.read((char*)sec, header.avBytesPerSec);
        closeFile();
    }

    int WAVFile::getLength() {
        if (length == 0) {
            int firstEightBytes = 8;
            int bytes = (header.chunkDataSize + firstEightBytes) - Consts::headerSize;
            length = bytes / header.sampleRate / 2;
        }
        return length;
    }

    void WAVFile::printSecond(short* sec, int secPos) {
        goTo(secPos);
        file.write((char*)sec, header.avBytesPerSec);
        if (!file.good()) {
            throw Exceptions::CanNotOpenFile();
        }
    }

    void WAVFile::openFile(FileOptions option) {
        op = option;
        if (op == FileOptions::out) {
            file.open(path, std::ios::out | std::ios::binary);
        }
        else {
            file.open(path, std::ios::in | std::ios::binary);
        }
        if (file.fail()) {
            throw Exceptions::CanNotOpenFile();
        }

    }

    void WAVFile::closeFile() {
        file.close();
    }

    void WAVFile::printHeader(const WAVHeader* head) {
        file.write((char*)head, Consts::headerSize);
    }

    const WAVHeader* WAVFile::getHeader() {
        return &header;
    }

    const void WAVFile::printFullHeader(WAVFile* copyToFile) {
        copyToFile->setHeader(getHeader());
        openFile(FileOptions::in);
        char* head = new char[Consts::headerSize + header.subChunk2DataSize];
        file.read(head, Consts::headerSize + header.subChunk2DataSize);
        copyToFile->file.write(head, Consts::headerSize + header.subChunk2DataSize);
        delete[] head;
        closeFile();
    }

    void WAVFile::setHeader(const WAVHeader* newHeader) {
        header = *newHeader;
    }

}