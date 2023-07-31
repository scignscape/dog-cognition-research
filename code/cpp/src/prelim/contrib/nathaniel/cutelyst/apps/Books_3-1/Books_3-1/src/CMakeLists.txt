file(GLOB_RECURSE Books_3_1_SRCS *.cpp *.h)

set(Books_3_1_SRCS
    ${Books_3_1_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(Books_3_1 SHARED ${Books_3_1_SRCS})

# Link to Cutelyst
target_link_libraries(Books_3_1
    Cutelyst::Core
    Qt5::Core
    Qt5::Network

 Cutelyst::View::Grantlee
)



