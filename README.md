# PROG_Project1
First programming project of the Programming module of the course. Team work with [@Gaspar99](https://github.com/Gaspar99).

# Introduction
This repository contains all files developed for the first project of the Programming module whose goal was to make a program
that would isolate entries from a text file representing a dictionary (which can be found [here](http://www.gutenberg.org/files/29765/29765-8.zip))
and to write those entries in a different text file (procdic). 
It was also part of the project to create a second program to allow users to play a game with the words from the previously 
generated file (playwords).

# Project Structure
There are two versions of the programs:
* procdic and playwords - Contain all source files from the first attempt at making each of the programs mentioned above.
* procdic_STL and playwords_STL - Contain all source files for the improved version of each of the programs. Improvements are described
                                  in readme files in the respective directories.

# Running Instructions
procdic can be run by doing:
```
$ g++ procdic.cpp -o procdic && ./procdic
```

For playwords, use:
```
$ g++ playwords.cpp -o playwords && ./playwords
```

For playwords_STL:
```
$ g++ Game.cpp Game.h main.cpp stringManip.cpp stringManip.h -o playwords && ./playwords
```

For procdic_STL:
```
$ g++ extractor.cpp extractor.h main.cpp stringManip.cpp stringManip.h -o procdic && ./procdic
```
