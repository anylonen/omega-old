set(CRYPT_SOURCES
    crypt.c
    bwt.c)

set(DECRYPT_SOURCES
    decrypt.c)

set(MAKEDATE_SOURCES
    makedate.c)

set(GENCLR_SOURCES
    genclr.c)

add_executable(crypt ${CRYPT_SOURCES})
add_executable(decrypt ${DECRYPT_SOURCES})
add_executable(makedate ${MAKEDATE_SOURCES})
add_executable(genclr ${GENCLR_SOURCES})

# Generate clrgen.h and clrgen.c
file(GLOB CLRGEN_H ${CMAKE_SOURCE_DIR}/src/*.h)
file(GLOB CLRGEN_C ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(APPEND CLRGEN_SOURCES ${CLRGEN_H} ${CLRGEN_C})

set(GENCLR_PRG ${CMAKE_CURRENT_SOURCE_DIR}/genclr)

add_custom_command(
    OUTPUT clrgen.cpp clrgen.h
    COMMAND ${CMAKE_C_COMPILER} -E -DOMEGA_CLRGEN -I${LUAJIT_INCLUDE_DIR} -I${CURSES_INCLUDE_DIR} ${CLRGEN_SOURCES} | ${GENCLR_PRG} clrgen.cpp clrgen.h 
    COMMAND ${CMAKE_COMMAND} -E rename clrgen.h ${CMAKE_SOURCE_DIR}/src/clrgen.h
    COMMAND ${CMAKE_COMMAND} -E rename clrgen.cpp ${CMAKE_SOURCE_DIR}/src/clrgen.cpp
    VERBATIM)

add_custom_target(
    clrgen ALL
    DEPENDS clrgen.cpp
    VERBATIM)

add_dependencies(clrgen genclr)

# Generate date.c
set(MAKEDATE_PRG ${CMAKE_CURRENT_SOURCE_DIR}/makedate)
add_custom_command(
    OUTPUT date.c 
    COMMAND ${MAKEDATE_PRG} > date.c 
    COMMAND ${CMAKE_COMMAND} -E rename date.c ${CMAKE_SOURCE_DIR}/src/date.c
    VERBATIM)

add_custom_target(
    date ALL
    DEPENDS date.c
    VERBATIM)

add_dependencies(date makedate)

# Generate maps.dat
file(GLOB MAPS ${CMAKE_SOURCE_DIR}/maps/*.map)
set(CRYPT_PRG ${CMAKE_CURRENT_SOURCE_DIR}/crypt)
add_custom_command(
    OUTPUT maps.dat 
    COMMAND ${CRYPT_PRG} maps.dat ${MAPS} 
    COMMAND ${CMAKE_COMMAND} -E rename maps.dat ${CMAKE_SOURCE_DIR}/lib/maps.dat
    VERBATIM)

add_custom_target(
    maps ALL
    DEPENDS maps.dat
    VERBATIM)

add_dependencies(maps crypt)
