#!/bin/bash

mkdir ../build
cmake -B ../build -S ..
make -C ../build
