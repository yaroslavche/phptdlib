cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(tdlib VERSION 0.0.4 LANGUAGES CXX)

find_package(Td 1.1.1 REQUIRED)

set(PHP_CONFIG_DIR /etc/php7/conf.d)
set(PHP_CONFIG php-config)
set(PHPINIFILE tdlib.ini)

set(SOURCE_FILES tdlib.cpp)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_library(tdlib SHARED ${SOURCE_FILES})
target_link_libraries(tdlib phpcpp Td::TdJson)
execute_process(COMMAND ${PHP_CONFIG} --extension-dir
        OUTPUT_VARIABLE LIBRARY_DIR)
add_custom_command(TARGET tdlib
        POST_BUILD
        COMMAND cp -f ${CMAKE_SOURCE_DIR}/${PHPINIFILE}; ${PHP_CONFIG_DIR}
        COMMAND cp -f $<TARGET_FILE:tdlib> ${LIBRARY_DIR})
