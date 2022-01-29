cmake_minimum_required(VERSION 3.0)

project(libbraces_parser VERSION 0.1.0 DESCRIPTION "C library for parsing braces format `{foo}`")

set(SRCS
    braces_parser.c
    )

set(HDRS
    braces_parser.h
    )

add_library(braces_parser SHARED ${SRCS} ${HRDS})
set_target_properties(braces_parser PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(braces_parser PROPERTIES SOVERSION ${PROJECT_VERSION})

add_library(braces_parser_static STATIC ${SRCS} ${HRDS})
set_target_properties(braces_parser_static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(braces_parser_static PROPERTIES SOVERSION ${PROJECT_VERSION})

include(GNUInstallDirs)

install(TARGETS braces_parser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS braces_parser_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES "braces_parser.h" DESTINATION "include/")
