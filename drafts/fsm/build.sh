#!/bin/bash


SRCS="src/Answer.cpp
      src/Client.cpp
      src/Exception.cpp
      src/Question.cpp 
      src/SingleTest.cpp
      src/TestsSession.cpp
      src/MethodicsLoader/methodics/Methodology.cpp
      src/MethodicsLoader/methodics/beka/Beka.cpp
      src/MethodicsLoader/methodics/hanin/Hanin.cpp
      src/MethodicsLoader/methodics/mmpi/Mmpi.cpp
      src/MethodicsLoader/methodics/scl/Scl.cpp
      src/MethodicsLoader/methodics/tobol/Tobol.cpp
      src/MethodicsLoader/methodics/zung/Zung.cpp
      src/MethodicsLoader/MethodicsLoader.cpp"


INCS="-I./src
      -I./src/MethodicsLoader/
      -I./src/MethodicsLoader/methodics/
      -I./src/MethodicsLoader/methodics/beka
      -I./src/MethodicsLoader/methodics/hanin
      -I./src/MethodicsLoader/methodics/mmpi
      -I./src/MethodicsLoader/methodics/scl
      -I./src/MethodicsLoader/methodics/tobol
      -I./src/MethodicsLoader/methodics/zung"


g++ main.cpp ${SRCS} -o a.out --std=c++20 -DDEBUG ${INCS}
