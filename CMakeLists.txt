cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(EXT_NAME tdlib)
set(EXT_VERSION 0.0.7)
project(${EXT_NAME} VERSION ${EXT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

find_package(Td 1.3.0 REQUIRED)
if(NOT Td_FOUND)
	message(SEND_ERROR "Failed to find Td")
	return()
endif()

#find_library(PHPCPP phpcpp)
#if(NOT PHPCPP)
#	message(SEND_ERROR "Failed to find PHP-CPP")
#	return()
#endif()

FIND_PROGRAM(PHP_CONFIG NAMES php-config)
if(NOT PHP_CONFIG)
    message(SEND_ERROR "Failed to find php-config")
    return()
endif()
execute_process(
    COMMAND ${PHP_CONFIG} --configure-options
    COMMAND sed -ne "s/^.*--with-config-file-scan-dir=\\([^ ]*\\).*/\\1/p"
    OUTPUT_VARIABLE PHP_CONFIG_DIR
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

if(PHP_VERSION_NUMBER LESS 70000)
    message(SEND_ERROR "PHP-CPP works only with PHP ^7.0. For older PHP versions, use the PHP-CPP-LEGACY instead.")
    return()
endif()

set(SOURCE_FILES tdlib.cpp include/TDLib/BaseJsonClient.cpp include/TDLib/JsonClient.cpp include/TDApi/TDLibParameters.cpp)
set(EXT_INI_FILE ${EXT_NAME}.ini)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(${EXT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${EXT_NAME} phpcpp Td::TdJson Td::TdStatic)

add_custom_command(TARGET ${EXT_NAME}
    POST_BUILD
    COMMAND echo 'extension=${CMAKE_SHARED_LIBRARY_PREFIX}${EXT_NAME}.so' > ${EXT_INI_FILE}
    COMMAND sudo cp -f ${EXT_INI_FILE}; ${PHP_CONFIG_DIR}
    COMMAND rm -f ${EXT_INI_FILE}
    COMMAND sudo cp -f $<TARGET_FILE:${EXT_NAME}> ${PHP_EXTENSIONS_DIR}
    COMMAND rm -f $<TARGET_FILE:${EXT_NAME}>
)
