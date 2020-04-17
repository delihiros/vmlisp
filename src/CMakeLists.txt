project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        util.h
        token.h
        lexer.h
        ast.h
        parser.h
        codegen.h
        )

set(SOURCE_FILES
        token.cpp
        lexer.cpp
        ast.cpp
        parser.cpp
        codegen.cpp
        )

add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${SOURCE_FILES} ${HEADER_FILES})
