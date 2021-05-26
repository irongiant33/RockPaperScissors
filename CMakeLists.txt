#https://cmake.org/cmake/help/latest/guide/tutorial/index.html#a-basic-starting-point-step-1
cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "RockPaperScissors")
project(${PROJECT_NAME} "C")

set(ITEM_CODE ${PROJECT_NAME}_code)
set(ITEM_EXEC ${PROJECT_NAME})

add_library(${ITEM_CODE} SHARED "src/play.c" "src/bots.c" "src/display.c" "include/functions.h" "include/structs.h" "include/define.h")

# add the executable
add_executable(${ITEM_EXEC} src/play.c)

target_link_libraries(${ITEM_EXEC} ${ITEM_CODE})
target_compile_options(${ITEM_EXEC} PUBLIC "-Wall" "-Wextra" "-g")