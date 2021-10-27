set(EXE theECG)

find_library(libQt5Widgets libQt5Widgets /c/msys64/mingw64/qt5-static/lib)
find_library(libQt5Core libQt5Core /mingw64/qt5-static/lib)
find_library(libstdc++ libstdc++)

# add the executable
add_executable(${EXE} 
    main.cpp
    EcgDataManager.cpp
)

target_link_libraries(${EXE} 
    libQt5Widgets
    libQt5Core
    libstdc++
)

target_include_directories(${EXE} PUBLIC "/mingw64/qt5-static/include")