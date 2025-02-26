cmake_minimum_required(VERSION 3.19)
project(SketcherApp LANGUAGES CXX)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Svg SvgWidgets)

qt_standard_project_setup()

qt_add_executable(SketcherApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    drawingscene.cpp
    mainwindow.h
    drawingscene.h
    mainwindow.ui
)

target_link_libraries(SketcherApp
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Svg
        Qt6::SvgWidgets
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