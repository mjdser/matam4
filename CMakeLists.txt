cmake_minimum_required(VERSION 3.27)
project(HW4_2425A)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(HW4_2425A
        Events/Barlog.cpp
        Events/Event.h
        Events/Pack.cpp
        Events/Slime.cpp
        Events/Snail.cpp
        Players/Character.h
        Players/Job.h
        Players/Player.cpp
        Players/Player.h
        main.cpp
        MatamStory.cpp
        MatamStory.h
        Utilities.cpp
        Utilities.h)
