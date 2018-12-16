cmake_minimum_required (VERSION 2.6)
project (Graphie)

add_subdirectory(../../oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_subdirectory(../../oxygine-sound/ oxygine-sound)
add_definitions(${OXYGINESOUND_DEFINITIONS})
include_directories(${OXYGINESOUND_INCLUDE_DIRS})
link_directories(${OXYGINESOUND_LIBRARY_DIRS})

add_subdirectory(../../oxygine-flow/ oxygine-flow)
include_directories(${OXYGINE_FLOW_INCLUDE_DIRS})

add_subdirectory(../../oxygine-freetype/ oxygine-freetype)
include_directories(${OXYGINE_FREETYPE_INCLUDE_DIRS})
include_directories(../../oxygine-freetype/src)
link_directories(${OXYGINE_FREETYPE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS} ${OXYGINE_FREETYPE_CXX_FLAGS}")

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(SOURCES 
	${SRC}/main.cpp
	${SRC}/Game.cpp 
	${SRC}/Game.h
	${SRC}/MainMenu.cpp
	${SRC}/MainMenu.h
	${SRC}/GameScreen.cpp 
	${SRC}/GameScreen.h
	${SRC}/ChapterScreen.cpp 
	${SRC}/ChapterScreen.h
	${SRC}/SettingsScreen.cpp 
	${SRC}/SettingsScreen.h
	${SRC}/MusicPlayer.cpp
	${SRC}/MusicPlayer.h
	${SRC}/Helpers/ScreenSwitcher.cpp
	${SRC}/Helpers/ScreenSwitcher.h
	${SRC}/Helpers/Configuration.cpp
	${SRC}/Helpers/Configuration.h
	${SRC}/Helpers/GridView.cpp
	${SRC}/Helpers/GridView.h
	${SRC}/Helpers/Theme.cpp
	${SRC}/Helpers/Theme.h ../src/Entities/Chapter.h)

add_executable(Graphie ${SOURCES})

if (WIN32) #disable console mode for VC++
	set_target_properties(Graphie PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

target_link_libraries(Graphie ${OXYGINESOUND_LIBS} oxygine-flow ${OXYGINE_CORE_LIBS} ${OXYGINE_FREETYPE_LIBS} oxygine-freetype)


if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648")
	em_link_pre_js(Graphie  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)
