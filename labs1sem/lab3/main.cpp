//
// Created by user on 29.12.22.
//
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "WaveEdit/WaveEdit.h"
#include "Exceptions/Exceptions.h"
#include "Converter/Converter.h"
#include "ProcessManager/ProcessManager.h"


using WAV::WAVFile;
using Converters::AbstrConv;
using WAV::Consts::FileOptions;
using ProcessManager::Manager;
namespace po = boost::program_options;
using Converters::converters;

int main(int argc, char* argv[]) {
    po::options_description desc("options");
    desc.add_options()
            ("help,h", "help screen")
            ("config,c", po::value<std::string>()->required())
            ("inputs,i", po::value<std::vector<std::string>>()->multitoken()->required());
    po::variables_map varMap;
    po::store(po::parse_command_line(argc, argv, desc), varMap);
    std::vector<std::string> inputs;
    std::string config;

    if (varMap.count("help")) {
        std::cout << desc << '\n';
        for (auto iter : converters) {
            iter.second->info();
        }
    }
    if (varMap.count("config")) {
        config = varMap["config"].as<std::string>();
    }
    if (varMap.count("inputs")) {
        inputs = varMap["inputs"].as<std::vector<std::string>>();
    }

    try {
        Manager man(inputs, config);
        man.makeOutputFile();
    }
    catch (Exceptions::AbstrExcp& excp) {
        return excp.errorCode();
    }
}