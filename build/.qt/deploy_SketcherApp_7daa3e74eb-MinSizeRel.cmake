include(E:/Projects/SketcherApp/build/.qt/QtDeploySupport-MinSizeRel.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/SketcherApp-plugins-MinSizeRel.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE E:/Projects/SketcherApp/build/MinSizeRel/SketcherApp.exe
    GENERATE_QT_CONF
)
