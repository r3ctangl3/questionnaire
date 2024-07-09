#!/bin/bash


SRCS="Question.cpp
      Answer.cpp 
      Exception.cpp
      methodics/Methodology.cpp 
      methodics/beka/Beka.cpp
      methodics/zung/Zung.cpp"


INCS="-I.
      -I./Methodics/"


g++ main.cpp ${SRCS} -o a.out --std=c++20 -DDEBUG ${INCS}
