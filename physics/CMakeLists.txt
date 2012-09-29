#trunk/physics/lib

INCLUDE_DIRECTORIES(../../third_party)

set (HEADERS 
car.h 
predecls.h 
track.h
objects.h)

set (SOURCES 
car.cpp 
track.cpp
objects.cpp)

add_library (physics_lib ${HEADERS} ${SOURCES})
