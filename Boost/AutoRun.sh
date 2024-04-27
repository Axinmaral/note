#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Error: Please provide the name of the .cpp file to compile as an argument."
  echo "Usage: $0 <file_name.cpp>"
  exit 1
else
  SOURCE_FILE="$1"
fi

EXECUTE_FILE="${1%.*}"
echo $EXECUTE_FILE

echo "****************Start to clean***********************"
rm -rf $EXECUTE_FILE
echo "****************Clean End***********************"

echo "****************Start to Build***********************"
g++ -std=c++11 -o $EXECUTE_FILE ./$SOURCE_FILE -lboost_thread -lboost_system -lboost_chrono -lpthread
echo "****************Build End***********************"

echo "****************Start to Test***********************"
if [ $? -eq 0 ]; then
  ./$EXECUTE_FILE
  echo "****************Test End***********************"
else
  echo "Compilation failed, no test performed."
fi
