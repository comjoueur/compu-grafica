PROJECT(TwoTriangles)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(TwoTriangles_SRC "src/Source.cpp" "src/glad.c")

link_directories(${CMAKE_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES("include")

MESSAGE("Library Added Succesfully")

ADD_EXECUTABLE(TwoTriangles ${TwoTriangles_SRC})

TARGET_LINK_LIBRARIES(TwoTriangles PUBLIC glfw3)
TARGET_LINK_LIBRARIES(TwoTriangles PUBLIC opengl32)
