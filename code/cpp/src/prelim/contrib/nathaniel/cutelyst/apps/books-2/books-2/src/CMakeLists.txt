file(GLOB_RECURSE books_2_SRCS *.cpp *.h)

set(books_2_SRCS
    ${books_2_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(books_2 SHARED ${books_2_SRCS})

# Link to Cutelyst
target_link_libraries(books_2
    Cutelyst::Core
    Qt5::Core
    Qt5::Network


 Cutelyst::View::Grantlee # Add this line
)

