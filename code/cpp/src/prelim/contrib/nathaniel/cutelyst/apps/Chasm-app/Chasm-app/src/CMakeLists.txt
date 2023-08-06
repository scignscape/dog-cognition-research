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

#target_compile_definitions(Chasm_app
#
 ## comment this out to prevent Cutelyst/Application
 #  from defining the "namespace_class" macro
    # (see application.h line 18 ...
 # NO_NAMESPACE_CLASS_DEF

 ## comment this out if you want to define a macro
 #  indicating that the grantlee templating
 #  library is being used from an installation
 #  specific to this archive or cutelyst build ...
 # USE_LOCAL_GRANTLEE
#
# )

