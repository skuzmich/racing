INCLUDE_DIRECTORIES(../../third_party)
INCLUDE_DIRECTORIES(../lib/)

# Some flags for Freeglut and GLUI.
add_definitions( -DFREEGLUT_EXPORTS -DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS )

find_package(OpenGL REQUIRED)

# Define the framework files.
set(Framework_SRCS
	framework/Main.cpp
	framework/Render.cpp
	framework/Render.h
	framework/Test.cpp
	framework/Test.h
)

#define the test files.
set(Tests_SRCS
	TestEntries.cpp
  RacingTest.h
)

# These are used to create visual studio folders.
source_group(Framework FILES ${Framework_SRCS})
source_group(Tests FILES ${Tests_SRCS})

include_directories (
	${OPENGL_INCLUDE_DIR}
	${Box2D_SOURCE_DIR}
)

if(APPLE)
	# We are not using the Apple's framework version, but X11's
	include_directories( /usr/X11/include )
	link_directories( /usr/X11/lib )
	set (OPENGL_LIBRARIES GL GLU GLUT X11)
endif(APPLE)

add_executable(physics_test
	${Framework_SRCS}
	${Tests_SRCS}
)

target_link_libraries (
	physics_test

  physics_lib
	Box2D
	freeglut_static
	glui
	${OPENGL_LIBRARIES}
) 
