#!/bin/sh

FILE_NUM=$1
# echo ${FILE_NUM}
FILE_NAME=${FILE_NUM}.cpp
# echo ${FILE_NAME}

g++ ${FILE_NAME} -o ${FILE_NUM} `pkg-config --libs --cflags opencv`