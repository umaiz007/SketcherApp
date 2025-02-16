cmake_minimum_required(VERSION 3.19)
project(SketcherApp LANGUAGES CXX)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(SketcherApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    drawingscene.cpp  # Add this line
    mainwindow.h
    drawingscene.h  # Add this line
    mainwindow.ui
)

target_link_libraries(SketcherApp
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS SketcherApp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SketcherApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})