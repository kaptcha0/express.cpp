cmake_minimum_required(VERSION 3.18)
project(ExpressDotCpp CXX)
set(CMAKE_CXX_STANDARD 20)

## Submodules ##
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	# Update submodules as needed
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if (GIT_SUBMODULE)
		message(STATUS "Submodule update")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
						WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
						RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if (NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

## Express.cpp ##
set(library_name "expresscpp")
add_library(${library_name} STATIC 
	src/http/core.cpp
	src/commons/tcp_connection.cpp
	src/http/http_connection.cpp
)

if(WIN32)
	list(APPEND EXTRA_LINK_LIBS wsock32 ws2_32)

	message("-- Linking WinSock")
endif()

target_include_directories(${library_name}
	PUBLIC
	include
	PRIVATE
	asio/asio/include
)

target_link_libraries(${library_name}
	PRIVATE 
	${EXTRA_LINK_LIBS}
)

target_link_directories(${library_name} 
	PRIVATE
	src
)

## Samples ##
add_executable(BasicServer samples/basic_server/server.cpp)

target_link_libraries(BasicServer expresscpp)


