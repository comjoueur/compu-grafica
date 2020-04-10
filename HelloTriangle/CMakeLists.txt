PROJECT(HelloTriangle)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(HelloTriangle_SRC "src/Source.cpp" "src/glad.c")

link_directories(${CMAKE_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES("include")

MESSAGE("Library Added Succesfully")

ADD_EXECUTABLE(HelloTriangle ${HelloTriangle_SRC})

TARGET_LINK_LIBRARIES(HelloTriangle PUBLIC glfw3)
TARGET_LINK_LIBRARIES(HelloTriangle PUBLIC opengl32)
