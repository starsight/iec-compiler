all : objgen.exe translator.exe

%.exe : %.cc
	g++ $< -o $@ -std=c++11 -g
