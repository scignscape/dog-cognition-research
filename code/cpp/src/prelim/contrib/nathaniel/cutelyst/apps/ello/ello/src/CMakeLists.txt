file(GLOB_RECURSE ello_SRCS *.cpp *.h)

set(ello_SRCS
    ${ello_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(ello SHARED ${ello_SRCS})

# Link to Cutelyst
target_link_libraries(ello
    Cutelyst::Core
    Qt5::Core
    Qt5::Network
)

