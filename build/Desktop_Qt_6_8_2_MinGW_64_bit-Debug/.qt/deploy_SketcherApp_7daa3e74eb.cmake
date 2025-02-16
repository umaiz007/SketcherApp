include(E:/Projects/SketcherApp/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/SketcherApp-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE E:/Projects/SketcherApp/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/SketcherApp.exe
    GENERATE_QT_CONF
)
