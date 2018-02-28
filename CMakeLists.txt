cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(tdlib VERSION 0.0.5 LANGUAGES CXX)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Td 1.1.1 REQUIRED)

FIND_PROGRAM(PHP_CONFIG NAMES php-config)
#MESSAGE("PHP_CONFIG = ${PHP_CONFIG}")
if (PHP_CONFIG)
    execute_process(
        COMMAND ${PHP_CONFIG} --configure-options
        COMMAND sed -ne "s/^.*--with-config-file-scan-dir=\\([^ ]*\\).*/\\1/p"
        OUTPUT_VARIABLE PHP_CONFIG_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${PHP_CONFIG} --includes
        COMMAND tr -d "I-"
        OUTPUT_VARIABLE PHP_INCLUDE_DIRS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${PHP_CONFIG} --extension-dir
        OUTPUT_VARIABLE PHP_EXTENSIONS_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${PHP_CONFIG} --vernum
        OUTPUT_VARIABLE PHP_VERSION_NUMBER
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif (PHP_CONFIG)
#MESSAGE("PHP_CONFIG_DIR     = ${PHP_CONFIG_DIR}")
#MESSAGE("PHP_EXTENSIONS_DIR = ${PHP_EXTENSIONS_DIR}")
#MESSAGE("PHP_INCLUDE_DIRS   = ${PHP_INCLUDE_DIRS}")
#MESSAGE("PHP_VERSION_NUMBER = ${PHP_VERSION_NUMBER}")

#include_directories(${PHP_INCLUDE_DIRS})
#$(CXX) $(CPPFLAGS) $(shell php-config --includes) $(CXXFLAGS) -c "$<" -o "$@"

set(PHPINIFILE tdlib.ini)

set(SOURCE_FILES tdlib.cpp)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_library(tdlib SHARED ${SOURCE_FILES})
target_link_libraries(tdlib phpcpp Td::TdJson)
add_custom_command(TARGET tdlib
    POST_BUILD
    COMMAND cp -f ${CMAKE_SOURCE_DIR}/${PHPINIFILE}; ${PHP_CONFIG_DIR}
    COMMAND cp -f $<TARGET_FILE:tdlib> ${PHP_EXTENSIONS_DIR})
