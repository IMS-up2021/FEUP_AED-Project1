cmake_minimum_required(VERSION 3.23)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp Headers/CSVReader.h Source/CSVReader.cpp Headers/UCTurma.h Source/UCTurma.cpp Headers/Slot.h Source/Slot.cpp Headers/Student.h Source/Student.cpp Source/ProcessingTool.cpp Headers/ProcessingTool.h)
