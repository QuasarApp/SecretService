#
# Copyright (C) 2024-2024 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)

get_filename_component(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CURRENT_PROJECT "QA${PROJECT_NAME}")
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

# Desctop deploying
# sets qifw variable
set(ApplicationsDir "@HomeDir@")
set(QIFW_PLATFORM linux)
set(INSTALLER_SUFIX ".run")
if (WIN32)
    set(QIFW_PLATFORM windows)
    set(INSTALLER_SUFIX ".exe")
    set(ApplicationsDir "@ApplicationsDir@")

endif()

message(GIT_COMMIT_COUNT = ${GIT_COMMIT_COUNT})
configure_file_in(${CURRENT_PROJECT} "${CMAKE_CURRENT_SOURCE_DIR}/deploy/SecretService.json")
# snap
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/deploy/snapcraft.yaml.in" "${CMAKE_SOURCE_DIR}/snap/snapcraft.yaml" @ONLY)
add_custom_target(${name}Templates ALL
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/deploy/snapcraft.yaml.in"
)

addDeployFromCustomFile(${CURRENT_PROJECT} "${CMAKE_CURRENT_SOURCE_DIR}/deploy/SecretService.json")

addDeploySnap(${CURRENT_PROJECT} "${CMAKE_SOURCE_DIR}/Distro/")

addReleaseSnap( ${CURRENT_PROJECT} "stable/edge")

set(LANGS ${CMAKE_CURRENT_SOURCE_DIR}/languages/en.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ru.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/uk.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ja.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/tr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/zh.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/de.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/fr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/es.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/pl.ts)

prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/../ "${LANGS}")


