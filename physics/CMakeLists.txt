INCLUDE_DIRECTORIES(../third_party)

# Some flags for Freeglut and GLUI.
add_definitions( -DFREEGLUT_EXPORTS -DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS )

find_package(OpenGL REQUIRED)

# Define the framework files.
set(Framework_SRCS
	Framework/Main.cpp
	Framework/Render.cpp
	Framework/Render.h
	Framework/Test.cpp
	Framework/Test.h
)

#define the test files.
set(Tests_SRCS
	Tests/TestEntries.cpp
	Tests/BeginContacts.h
	Tests/EndContacts.h
	Tests/Car.h
	Tests/Lib.h
	Tests/TestEntries.cpp
	Tests/Track.h
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
	Box2D
	freeglut_static
	glui
	${OPENGL_LIBRARIES}
) 
