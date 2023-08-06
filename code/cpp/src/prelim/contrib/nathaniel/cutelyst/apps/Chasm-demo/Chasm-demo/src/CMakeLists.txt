file(GLOB_RECURSE Chasm_demo_SRCS *.cpp *.h)

set(Chasm_demo_SRCS
 ${Chasm_demo_SRCS}
 ${TEMPLATES_SRC}
)

# Create the application
add_library(Chasm_demo SHARED ${Chasm_demo_SRCS})

# Link to Cutelyst
target_link_libraries(Chasm_demo
 Cutelyst::Core
 Qt5::Core
 Qt5::Network

 Cutelyst::View::Grantlee
)

