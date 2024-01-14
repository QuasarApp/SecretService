#
# Copyright (C) 2024-2024 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)

get_filename_component(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CURRENT_PROJECT "${PROJECT_NAME}_${CURRENT_PROJECT_DIR}")
option(SIGN_APP "This option enable od disabled sign apk and aab files" ON)

file(GLOB_RECURSE SOURCE_CPP
    "*.cpp" "*.h"
)

file(GLOB_RECURSE SOURCE_QRC
    "*.qrc"
)

set(ALL_SOURCES ${SOURCE_CPP} ${SOURCE_QRC})

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

updateGitVars()

qt_add_executable(${CURRENT_PROJECT} ${ALL_SOURCES})

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME})

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

SET(TARGET_DIR "${CMAKE_SOURCE_DIR}/Distro")
file(MAKE_DIRECTORY ${TARGET_DIR})



