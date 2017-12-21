cmake_minimum_required (VERSION 2.6)
project (MyAwesomeGame)

add_subdirectory(../../oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS} ${OXYGINE_FREETYPE_CXX_FLAGS}")

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(SOURCES 
	${SRC}/example.cpp 
	${SRC}/main.cpp 
	${SRC}/example.h 
	)

add_executable(MyAwesomeGame ${SOURCES})

if (WIN32) #disable console mode for VC++
	set_target_properties(MyAwesomeGame PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

target_link_libraries(MyAwesomeGame ${OXYGINESOUND_LIBS} oxygine-flow ${OXYGINE_CORE_LIBS} ${OXYGINE_FREETYPE_LIBS} oxygine-freetype)


if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648")
	em_link_pre_js(MyAwesomeGame  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)