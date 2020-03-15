cmake_minimum_required (VERSION 3.4)

project (hopa CXX)

option(USING_DOCKER OFF)

# Add external projects
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

if(USING_DOCKER)
	set(SeqAn3_DIR "/deps/seqan3/build_system")
else()
	set(SeqAn3_DIR "${CMAKE_SOURCE_DIR}/deps/seqan3/build_system")
endif(USING_DOCKER)
unset(USING_DOCKER CACHE)

find_package (SeqAn3 REQUIRED)

add_executable (hopa main.cpp)


# arg_parse library
add_library(arg_parse arg_parse.cpp)
target_include_directories( arg_parse PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  )
target_link_libraries(arg_parse LINK_PUBLIC seqan3::seqan3)

# aligner library
add_library(aligner aligner.cpp)

target_include_directories( aligner PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  )
target_link_libraries(aligner LINK_PUBLIC seqan3::seqan3)

target_include_directories(hopa PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  )

target_link_libraries(hopa LINK_PUBLIC arg_parse aligner seqan3::seqan3)

install(TARGETS hopa DESTINATION bin)
