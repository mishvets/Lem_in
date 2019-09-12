cmake_minimum_required(VERSION 3.14)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

AUX_SOURCE_DIRECTORY(libft LIBA)

add_executable(Lem_in
        ${LIBA}
        src/main.c
        inc/lem-in.h
        src/parsing.c
        src/parsing_room.c
        src/parsing_link.c
        src/find_way.c
        src/ants_move.c
        )

link_libraries(libft/libft.a)