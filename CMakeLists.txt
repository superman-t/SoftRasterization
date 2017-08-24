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

    add_custom_command(OUTPUT
        ${CMAKE_BINARY_DIR}/bin/assimpd.dll
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/3rdparty/assimp-3.1.1/lib/assimpd.dll"
        ${CMAKE_BINARY_DIR}/bin/assimpd.dll
    DEPENDS TMP
	)

	add_custom_target(copy_files ALL
	    DEPENDS ${CMAKE_BINARY_DIR}/bin/assimpd.dll
	)
    install (TARGETS SoftRender
     RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

else()
	set(CMAKE_CXX_COMPILER      "clang++" )         # 显示指定使用的C++编译器
	set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
	set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

	set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化
endif (MSVC)