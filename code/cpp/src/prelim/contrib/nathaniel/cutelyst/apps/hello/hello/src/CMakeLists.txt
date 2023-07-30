file(GLOB_RECURSE hello_SRCS *.cpp *.h)

set(hello_SRCS
    ${hello_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(hello SHARED ${hello_SRCS})

# Link to Cutelyst
target_link_libraries(hello
    Cutelyst::Core
    Qt5::Core
    Qt5::Network
)

