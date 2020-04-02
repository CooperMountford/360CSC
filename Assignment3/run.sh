#!/bin/bash

set -e
make all

echo $'running 1st test\n'
cd apps
./test01

cd ..
make clean