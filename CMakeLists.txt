cmake_minimum_required(VERSION 3.20.0)

set(ProjectName "textGame")

project(${ProjectName} CXX)

set_property(GLOBAL PROPERTY CXX_STANDARD 14)

add_compile_options(
    -O0
)

add_executable( ${ProjectName}
    "challenge/main.cpp"
    "challenge/Hero.cpp"
    "challenge/Map.cpp"
)

include_directories(
    "../challenge"
)
target_link_options(${ProjectName} PUBLIC
    -lncurses
)
set_target_properties(${ProjectName} PROPERTIES SUFFIX ".elf")

# add_custom_command(TARGET ${ProjectName} PRE_LINK
#     COMMAND "g++"
#     ARGS -g -L ${CMAKE_SOURCE_DIR} -o ${ProjectName} -lncurses
# )