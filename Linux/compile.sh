#!/usr/bin/env bash
# testModOSM.cpp ModJson.cpp

g++ -c main.cpp -o main.o
g++ -c ModJson.cpp -o ModJson.o
g++ main.o ModJson.o -o updateOSM

# ./updateOSM
