cmake_minimum_required(VERSION 3.0)

project(libssfmt VERSION 0.1.0 DESCRIPTION "C library for parsing braces format `{foo}`")

set(SRCS
    ssfmt.c
    )

set(HDRS
    ssfmt.h
    )

add_library(ssfmt SHARED ${SRCS} ${HRDS})
set_target_properties(ssfmt PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ssfmt PROPERTIES SOVERSION ${PROJECT_VERSION})

add_library(ssfmt_static STATIC ${SRCS} ${HRDS})
set_target_properties(ssfmt_static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ssfmt_static PROPERTIES SOVERSION ${PROJECT_VERSION})

include(GNUInstallDirs)

install(TARGETS ssfmt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS ssfmt_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES "ssfmt.h" DESTINATION "include/")
