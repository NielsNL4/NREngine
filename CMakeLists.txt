# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (NREngine)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


# Compile external dependencies
add_subdirectory (external)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")

	# For leak-checking and profiling, add '-pg' to CXX flags
	# set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11 -O2")
	# valgrind --leak-check=full ./program
	# ./program # creates cmon.out
	# gprof program gmon.out > analysis.txt
endif(UNIX)

if(WIN32)
	# Create a group for Visual Studio
	SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
	# suppress pedantic warnings
	add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)

include_directories(
	external/glfw-3.0.3/include/GLFW/
	external/glm-0.9.8.4/
	external/glad/include/
	external/assimp/include/
	.
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLAD)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLAD_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Common (libcommon.a)
add_library(common
	common/renderer.cpp
	common/renderer.h
	common/external/stb_image.cpp
	common/external/stb_image.h
	common/shader.h
	common/camera.h
	common/mesh.h
	common/model.h
	common/texture.cpp
	common/texture.h
	common/skybox.h
	common/scene.cpp
	common/scene.h
	common/entity.cpp
	common/entity.h
	common/core.cpp
	common/core.h)


# program
add_executable(NREngine
	NREngine/program.cpp
	NREngine/myscene.cpp
	NREngine/myscene.h
	NREngine/myentity.cpp
	NREngine/myentity.h
	NREngine/lamp.cpp
	NREngine/lamp.h
)

target_link_libraries(NREngine
	common
	${ALL_GRAPHICS_LIBS}
	assimp
)
# Copy assets and shaders to the build directory
# (In Visual Studio, copy these directories to either 'Release' or 'Build')
file(
	COPY NREngine/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY common/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
