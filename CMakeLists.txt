cmake_minimum_required(VERSION 3.29)
project(VelocityChess)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_package(SFML 3.0 COMPONENTS Graphics REQUIRED)

add_executable(VelocityChess main.cpp src/board.cpp src/board.h src/precompute.cpp src/precompute.h src/misc.cpp src/misc.h src/definitions.h src/magic_search.cpp src/magic_search.h src/search.cpp src/search.h src/evaluate.cpp src/evaluate.h src/tests.cpp src/tests.h src/uci.cpp src/uci.h src/gui/gui.cpp src/gui/gui.h src/screen.cpp src/screen.h src/book.cpp src/book.h src/opening.cpp src/opening.h)
target_link_libraries(VelocityChess SFML::Graphics)