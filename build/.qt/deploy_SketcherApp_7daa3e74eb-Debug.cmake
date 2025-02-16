include(E:/Projects/SketcherApp/build/.qt/QtDeploySupport-Debug.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/SketcherApp-plugins-Debug.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE E:/Projects/SketcherApp/build/Debug/SketcherApp.exe
    GENERATE_QT_CONF
)
