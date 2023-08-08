cmake_minimum_required(VERSION 3.14)

project(pgame)
message(STATUS "Project " ${PROJECT_NAME})

include_directories(${HHUOS_SRC_DIR})

# Set source files
set(SOURCE_FILES
        ${HHUOS_SRC_DIR}/application/pgame/pgame.cpp
        ${HHUOS_SRC_DIR}/application/pgame/Player.cpp
        ${HHUOS_SRC_DIR}/application/pgame/PGame.cpp
        ${HHUOS_SRC_DIR}/application/pgame/RectangleParticleSystem.cpp
        ${HHUOS_SRC_DIR}/application/pgame/Ground.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} lib.user.crt0 lib.user.base lib.user.game)