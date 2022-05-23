#! /bin/bash

OPTIONS="-D DEBUG -Wno-format"
gcc -o test_svg $OPTIONS test_svg.c svg.c && ./test_svg