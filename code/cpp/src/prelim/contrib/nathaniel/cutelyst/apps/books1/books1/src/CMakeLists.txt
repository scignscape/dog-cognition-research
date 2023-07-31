file(GLOB_RECURSE books1_SRCS *.cpp *.h)

set(books1_SRCS
    ${books1_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(books1 SHARED ${books1_SRCS})

# Link to Cutelyst
target_link_libraries(books1
    Cutelyst::Core
    Qt5::Core
    Qt5::Network
)

