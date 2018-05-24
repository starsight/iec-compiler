#!/bin/bash

# compile iec-compiler & translator.exe
cd build/
cmake ..
make
cd ../
cd src/objgen/
rm *.exe
make
cp translator.exe ../../translator
cd ../../