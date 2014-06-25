set(GENCLR_SOURCES
    genclr.c)

add_executable(genclr ${GENCLR_SOURCES})

file(GLOB CLRGEN_SOURCES *.c *.h)

add_custom_command(
    OUTPUT clrgen.h
    COMMAND ${CMAKE_C_COMPILER} -E -DOMEGA_CLRGEN -I${LUAJIT_INCLUDE_DIR} -I${CURSES_INCLUDE_DIR} ${CLRGEN_SOURCES} | ./genclr clrgen.c clrgen.h 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating clrgen.h"
    VERBATIM)

add_custom_target(
    clrgen ALL
    DEPENDS genclr
    VERBATIM)

add_dependencies(clrgen genclr)

file(GLOB OMEGA_SOURCES *.c)

foreach(sfile ${OMEGA_SOURCES})
    get_filename_component(f ${sfile} NAME)
    if(${f} MATCHES "^(genclr.c)$")
        list(APPEND remove_these ${sfile})
    endif()
endforeach()

list(REMOVE_ITEM OMEGA_SOURCES ${remove_these})

list(APPEND OMEGA_LINK_LIBRARIES
    ${CURSES_LIBRARIES}
    ${LUAJIT_LIBRARIES}
    m)

add_executable(omega ${OMEGA_SOURCES})
target_link_libraries(omega ${OMEGA_LINK_LIBRARIES})

add_dependencies(omega clrgen)
