cmake_minimum_required (VERSION 2.6)

project (SoftRender)

file(GLOB SoftRender_src "src/*.h" "src/*.cpp" "main.cpp")

include_directories(3rdparty/assimp-3.1.1/include)

link_directories(${PROJECT_SOURCE_DIR}/3rdparty/assimp-3.1.1/lib)

add_executable(SoftRender ${SoftRender_src} )
target_link_libraries (SoftRender assimp)

set(CMAKE_CXX_FLAGS "-std=c++11")
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SoftRender)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -EHsc -D_USE_MATH_DEFINES")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif (MSVC)