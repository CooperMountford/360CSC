#!/bin/bash

set -e
make test01

echo $'running 1st test\n'
apps/test01
