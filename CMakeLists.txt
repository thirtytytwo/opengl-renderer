cmake_minimum_required(VERSION 3.10)

project(renderer)

#find required packages

find_package(glfw3 REQUIRED)
message(STATUS "found glfw3")
find_package(glm REQUIRED)
message(STATUS "found glm")
find_package(assimp REQUIRED)
message(STATUS "found assimp")

#platform setting

if(WIN32)
    set(LIBS glfw3 opengl32)
    INCLUDE_DIRECTORIES(D:/opengl-renderer/include)
elseif(APPLE)
    INCLUDE_DIRECTORIES(/System/Library/Frameworks)
    INCLUDE_DIRECTORIES(/Users/luyicheng/Desktop/renderer/include)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
    FIND_LIBRARY(IOKit_LIBRARY IOKit)
    FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
    MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
    SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
    SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY})
    set(LIBS ${LIBS} ${APPLE_LIBS})
else()
    set(LIBS )
endif(WIN32)

#set file

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE assimp::assimp)

