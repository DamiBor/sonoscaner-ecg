find_library(libQt5Widgets libQt5Widgets)
find_library(libQt5Core libQt5Core)
find_library(libstdc++ libstdc++)

set(LIB theECGLib)
add_library(${LIB} STATIC
    EcgDataManager.cpp
)

target_link_libraries(${LIB} PUBLIC 
    libQt5Widgets
    libQt5Core
    libstdc++
)

target_include_directories(${LIB} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    "/mingw64/qt5-static/include"
)

set(EXE theECG)

# add the executable
add_executable(${EXE} 
    main.cpp
)

target_link_libraries(${EXE} 
    ${LIB}
)


