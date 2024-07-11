#!/bin/bash


SRCS="Answer.cpp
      Exception.cpp
      Question.cpp 
      SingleTest.cpp
      TestsSession.cpp
      methodics_loader/methodics/Methodology.cpp
      methodics_loader/methodics/beka/Beka.cpp
      methodics_loader/methodics/hanin/Hanin.cpp
      methodics_loader/methodics/mmpi/Mmpi.cpp
      methodics_loader/methodics/scl/Scl.cpp
      methodics_loader/methodics/tobol/Tobol.cpp
      methodics_loader/methodics/zung/Zung.cpp
      methodics_loader/MethodicsLoader.cpp"


INCS="-I.
      -I./methodics_loader/
      -I./methodics_loader/methodics/
      -I./methodics_loader/methodics/beka
      -I./methodics_loader/methodics/hanin
      -I./methodics_loader/methodics/mmpi
      -I./methodics_loader/methodics/scl
      -I./methodics_loader/methodics/tobol
      -I./methodics_loader/methodics/zung"


g++ main.cpp ${SRCS} -o a.out --std=c++20 -DDEBUG ${INCS}
