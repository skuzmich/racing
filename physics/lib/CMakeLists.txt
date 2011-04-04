#trunk/physics/lib

INCLUDE_DIRECTORIES(../../third_party)

set (HEADERS Car.h Predecls.h Track.h BeginContacts.h EndContacts.h)

set (SOURCES Car.cpp Track.cpp BeginContacts.cpp EndContacts.cpp)

add_library (physics_lib ${HEADERS} ${SOURCES})
