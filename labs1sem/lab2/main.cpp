#include <iostream>
#include "Game/CompetitionWithDetail/CompetitionWithDetail.h"
#include "Game/GameMatrix/GameMatrix.h"
#include "Game/Tournament/Tournament.h"
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iterator>
using namespace std;

int  main(int ac, char* av[]) {

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("name", po::value<vector<string>>(), "strategy names")
            ("mode", po::value<string>(), "game mode")
            ("steps", po::value<int>(), "number of steps")
            ("matrix", po::value<string>()->default_value(""), "file with matrix")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);
    GameMatrix Matrix;

    string Mode = vm["mode"].as<string>();
    int Steps = vm["steps"].as<int>();

    vector<string> VectorNameStr(vm["name"].as<vector<string>>());
    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    if(Mode == "fast") {

        StrategyFactory Factory;
        vector<shared_ptr<GameStrategy>> VectorStrategies;
        for (int i = 0; i < 3; i++) {
            VectorStrategies.push_back(Factory.createStrategy(Factory.DetectionStrategyName(VectorNameStr[i]), Matrix));
        }
        if("/home/user/CLionProjects/lab2/Game/GameMatrix/FileMatrix.txt" == vm["matrix"].as<string>()){
            GameMatrix Matrix1("/home/user/CLionProjects/lab2/Game/GameMatrix/FileMatrix.txt");
            CompetitionWithoutDetail fast(VectorStrategies, vm["steps"].as<int>());
            fast.GetResult(Matrix1);
        }
        else{
            CompetitionWithoutDetail fast(VectorStrategies, vm["steps"].as<int>());
            fast.GetResult(Matrix);
        }
    }
    if(Mode == "detail"){
        StrategyFactory Factory;
        vector<shared_ptr<GameStrategy>> VectorStrategies;
        for(int i=0;i<VectorNameStr.size();i++){
            VectorStrategies.push_back(Factory.createStrategy(Factory.DetectionStrategyName(VectorNameStr[i]),  Matrix));
        }
        if("/home/user/CLionProjects/lab2/Game/GameMatrix/FileMatrix.txt" == vm["matrix"].as<string>()){
            GameMatrix Matrix1("/home/user/CLionProjects/lab2/Game/GameMatrix/FileMatrix.txt");
            CompetitionWithDetail detail(VectorStrategies);
            detail.GetResult(Matrix1);
        }
        else{
            CompetitionWithDetail detail(VectorStrategies);
            detail.GetResult(Matrix);
        }

    }
    if(Mode == "tournament"){
        StrategyFactory Factory;
        vector<shared_ptr<GameStrategy>> VectorStrategies;
        for(int i=0;i<VectorNameStr.size();i++){
            VectorStrategies.push_back(Factory.createStrategy(Factory.DetectionStrategyName(VectorNameStr[i]),  Matrix));
        }
        if("/home/user/CLionProjects/lab2/Game/GameMatrix/FileMatrix.txt" == vm["matrix"].as<string>()){
            GameMatrix Matrix1("/home/user/CLionProjects/lab2/Game/GameMatrix/FileMatrix.txt");
            Tournament tournament(VectorStrategies, Steps);
            tournament.GetResult(Matrix1);
        }
        else{
            Tournament tournament(VectorStrategies, Steps);
            tournament.GetResult(Matrix);
        }
    }
    return 0;
}




/*    StrategyFactory Factory;
    GameMatrix Matrix;
    vector<string> VectorStrings;
    VectorStrings.push_back("AlwaysChoiceC");
    VectorStrings.push_back("AlwaysChoiceD");
    VectorStrings.push_back("AlwaysChoiceC");
    VectorStrings.push_back("AlwaysChoiceD");
    vector<shared_ptr<GameStrategy>> VectorStrategies;
    for(int i=0;i<VectorStrings.size();i++){
        VectorStrategies.push_back(Factory.createStrategy(Factory.DetectionStrategyName(VectorStrings[i]),  Matrix));
    }
    CompetitionWithoutDetail game(VectorStrategies, 5, Matrix);
    game.GetResult(Matrix);
*/