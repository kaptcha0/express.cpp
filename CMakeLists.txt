cmake_minimum_required(VERSION 3.18)
project(ExpressDotCpp CXX)
set(CMAKE_CXX_STANDARD 20)

# Libraries
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.66 COMPONENTS system regex date_time REQUIRED)

## Express.cpp ##
set(library_name "expresscpp")
add_library(${library_name} STATIC src/server.cpp)

if(WIN32)
	list(APPEND EXTRA_LINK_LIBS wsock32 ws2_32)

	message("-- Linking WinSock")
endif()

target_include_directories(${library_name}
	PUBLIC
	include
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(${library_name}
	PRIVATE 
	${EXTRA_LINK_LIBS}
	${Boost_LIBRARIES}
)

target_link_directories(${library_name} 
	PRIVATE
	src
	${Boost_LIBRARY_DIRS}
)

## Samples ##
add_executable(BasicServer samples/basic_server/server.cpp)

target_link_libraries(BasicServer expresscpp)


