cmake_minimum_required(VERSION 3.16.3)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
add_executable(lab3 main.cpp ConfigReader/ConfigReader.h ConfigReader/ConfigReader.cpp Consts/Consts.h Converter/Converter.cpp Converter/Converter.h Exceptions/Exceptions.h Exceptions/Exceptions.cpp ProcessManager/ProcessManager.h ProcessManager/ProcessManager.cpp WaveEdit/WaveEdit.cpp WaveEdit/WaveEdit.h)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


TARGET_LINK_LIBRARIES( lab3 LINK_PUBLIC ${Boost_LIBRARIES} )