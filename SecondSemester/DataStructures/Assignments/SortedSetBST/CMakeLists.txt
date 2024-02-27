cmake_minimum_required(VERSION 3.24)
project(lab4_hashtable_ADT_SortedBag)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab4_hashtable_ADT_SortedBag
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedSet.cpp
        SortedSet.h
        SortedSetIterator.cpp
        SortedSetIterator.h
        )
