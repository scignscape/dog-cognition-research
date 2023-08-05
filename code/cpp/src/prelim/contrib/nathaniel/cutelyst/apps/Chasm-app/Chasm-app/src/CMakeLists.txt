file(GLOB_RECURSE Chasm_app_SRCS *.cpp *.h)

set(Chasm_app_SRCS
 ${Chasm_app_SRCS}
 ${TEMPLATES_SRC}
)

# Create the application
add_library(Chasm_app SHARED ${Chasm_app_SRCS})

# Link to Cutelyst
target_link_libraries(Chasm_app
 Cutelyst::Core
 Qt5::Core
 Qt5::Network

 Cutelyst::View::Grantlee
)

