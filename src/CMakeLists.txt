file(GLOB OMEGA_SOURCES *.c)

list(APPEND OMEGA_LINK_LIBRARIES
    ${CURSES_LIBRARIES}
    ${LUAJIT_LIBRARIES}
    m)

add_executable(omega ${OMEGA_SOURCES})
target_link_libraries(omega ${OMEGA_LINK_LIBRARIES})

