find_package(Qt5 COMPONENTS Core Widgets Gui)

find_library(libstdc++ libstdc++)

set(LIB theECGLib)
add_library(${LIB} STATIC
    EcgDataManager.cpp
    EcgGraph.cpp
)

target_link_libraries(${LIB} PUBLIC 
    libQt5Widgets
    libQt5Core
    libQt5Gui
    libstdc++
)

target_include_directories(${LIB} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    "/mingw64/qt5-static/include"
)

set_property(TARGET ${LIB} PROPERTY AUTOMOC ON)

set(EXE theECG)

# add the executable
add_executable(${EXE} 
    main.cpp
)

target_link_libraries(${EXE} 
    ${LIB}
)