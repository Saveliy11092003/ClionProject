cmake_minimum_required(VERSION 3.21)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp Test.cpp Game/StrategyFactory/StrategyFactory.cpp Game/StrategyFactory/StrategyFactory.h Game/Strategies/AlwaysVoteC/AlwaysVoteCGameStrategy.cpp Game/Strategies/AlwaysVoteC/AlwaysVoteCGameStrategy.h Game/GameMatrix/GameMatrix.cpp Game/GameMatrix/GameMatrix.h Game/Choice.h Game/GameStrategy.h Game/Strategies/AlwaysVoteD/AlwaysVoteDGamesStrategy.cpp Game/Strategies/AlwaysVoteD/AlwaysVoteDGamesStrategy.h Game/Strategies/TitForTatSoft/TitForTatSoft.cpp Game/Strategies/TitForTatSoft/TitForTatSoft.h Game/GameMatrix/GameScore.cpp Game/GameMatrix/GameScore.h Game/CompetitionWithoutDetail/CompetitionWithoutDetail.cpp Game/CompetitionWithoutDetail/CompetitionWithoutDetail.h Game/CompetitionWithDetail/CompetitionWithDetail.cpp Game/CompetitionWithDetail/CompetitionWithDetail.h Game/CompetitionWithDetail/Button.cpp Game/CompetitionWithDetail/Button.h Game/Tournament/Tournament.cpp Game/Tournament/Tournament.h Game/Strategies/Alternating/AlternatingVoteStrategy.cpp Game/Strategies/Alternating/AlternatingVoteStrategy.h Game/Strategies/TitForTatHard/TitForTatHard.cpp Game/Strategies/TitForTatHard/TitForTatHard.h Game/Strategies/RandomStrategy/RandomStrategy.cpp Game/Strategies/RandomStrategy/RandomStrategy.h Game/InterfaceGame/InterfaceGame.cpp Game/InterfaceGame/InterfaceGame.h)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


TARGET_LINK_LIBRARIES(lab2 LINK_PUBLIC ${Boost_LIBRARIES} )

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(lab2 PUBLIC gtest_main)