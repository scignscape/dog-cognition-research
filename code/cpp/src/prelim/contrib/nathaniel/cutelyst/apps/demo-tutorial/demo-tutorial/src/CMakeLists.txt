file(GLOB_RECURSE demo_tutorial_SRCS *.cpp *.h)

set(demo_tutorial_SRCS
 ${demo_tutorial_SRCS}
 ${TEMPLATES_SRC}
)

# Create the application
add_library(demo_tutorial SHARED ${demo_tutorial_SRCS})

# Link to Cutelyst
target_link_libraries(demo_tutorial
 Cutelyst::Core
 Qt5::Core
 Qt5::Network

 Cutelyst::View::Grantlee
)

