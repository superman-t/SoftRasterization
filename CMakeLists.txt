cmake_minimum_required (VERSION 2.6)

project (SoftRender)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/$<CONFIGURATION>)

# Disable building extras
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL " " FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL " " FORCE)
set(SYSTEM_IRRXML OFF CACHE BOOL " " FORCE)

set(BIN_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

message(STATUS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/assimp)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/assimp/include)

file(GLOB SoftRender_src "src/*.h" "src/*.cpp" "main.cpp")

add_executable(SoftRender ${SoftRender_src} )
target_link_libraries (SoftRender assimp)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++")


function(PostCopyDir src dst)
message(STATUS "copy dir:${src} to ${dst}")
add_custom_command(TARGET SoftRender POST_BUILD 			# Adds a post-build event
    COMMAND ${CMAKE_COMMAND} -E copy_directory					# which executes "cmake - E copy"
        "${src}"      	                                # <--this is in "${PROJECT_BINARY_DIR}/3rdparty/assimp/code/$<CONFIGURATION>"
        ${dst})										    # <--this is out path $<TARGET_FILE_DIR:SoftRender>
endfunction(PostCopyDir src dst)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SoftRender)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -EHsc -D_USE_MATH_DEFINES")
    PostCopyDir(${PROJECT_SOURCE_DIR}/res ${PROJECT_SOURCE_DIR}/bin/res)

else()
	set(CMAKE_CXX_COMPILER      "clang++" )         # 显示指定使用的C++编译器
	set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
	set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

	set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化
endif (MSVC)