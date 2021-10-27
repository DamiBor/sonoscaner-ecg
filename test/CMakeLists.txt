find_library(libgtest libgtest)

# define the target name
set(TARGET EcgTest)

# Add an executable to the project using the specified source files
add_executable(${TARGET} main.cpp)

# Specify libraries to use when linking 
target_link_libraries(${TARGET}
    PRIVATE
    libgtest
    theECGLib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )