#!/bin/bash

for FILE in RScf WScf WSdcs cf dcs
do
    g++ -Ofast -shared -rdynamic --std=c++14 -fPIC -march=native ${FILE}.cpp -o ${FILE}.so
done