cmake_minimum_required(VERSION 3.23)
project(AEDOutro)

set(CMAKE_CXX_STANDARD 17)

add_executable(AEDOutro main.cpp Headers/CSVReader.h Source/CSVReader.cpp Headers/UCTurma.h Source/UCTurma.cpp Headers/Slot.h Source/Slot.cpp Headers/Student.h Source/Student.cpp Source/Interface.cpp Headers/Interface.h Headers/Request.h Source/Request.cpp)

