//
// Created by user on 29.12.22.
//

#ifndef LAB3_CONVERTER_H
#define LAB3_CONVERTER_H

#include <map>
#include "../WaveEdit/WaveEdit.h"
#include "../Consts/Consts.h"
#include "../Exceptions/Exceptions.h"


using WAV::WAVFiles;

namespace Converters {

    struct ConvArgs {

        std::string name;
        WAVFiles files;
        Times times;
    };

    class AbstrConv {
    public:
        virtual void makeChanges(samples) = 0;
        virtual bool checkInput(ConvArgs) = 0;
        virtual ~AbstrConv() {};
        virtual void info() = 0;

    private:
    };

    class Mute : public AbstrConv {
    public:
        virtual void makeChanges(samples) override;
        virtual bool checkInput(ConvArgs) override;
        virtual void info() override;

    private:
        int numOfFiles = 0;
        int numOfTimePoints = 2;
    };

    class Mix : public AbstrConv {
    public:
        virtual void makeChanges(samples) override;
        virtual bool checkInput(ConvArgs) override;
        virtual void info() override;

    private:
        int numOfFiles = 1;
        int numOfTimePoints = 1;
    };

    class Overlap : public AbstrConv {
    public:
        virtual void makeChanges(samples) override;
        virtual bool checkInput(ConvArgs) override;
        virtual void info() override;

    private:
        int numOfFiles = 1;
        int numOfTimePoints = 1;
    };

    class AbstrCreator {
    public:
        virtual AbstrConv*  createConv() = 0;
    };

    template <class T>
    class Creator : public AbstrCreator {
    public:
        virtual AbstrConv* createConv() override {
            return new(T);
        }
    };

    static std::map<std::string, AbstrCreator*> factories = {
            { {"mute", new Creator<Mute>},
              {"mix", new Creator<Mix>},
              {"overlap", new Creator<Overlap>}}
    };

    static std::map<std::string, AbstrConv*> converters = {
            { {"mute", new Mute},
              {"mix", new Mix},
              {"overlap", new Overlap}}
    };

    AbstrConv* createConverter(std::string name);

}


#endif //LAB3_CONVERTER_H
