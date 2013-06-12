# ----------------------------------------------------------------------------
# prepare

cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# ============================================================================



# ----------------------------------------------------------------------------
# configure the project

project(april)
set(april_MAJOR_VERSION 1)
set(april_MINOR_VERSION 0)
set(april_PATCH_VERSION 0)
set(april_VERSION
  ${april_MAJOR_VERSION}.${april_MINOR_VERSION}.${april_PATCH_VERSION})

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}")

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/april/april_config.h.in ${PROJECT_BINARY_DIR}/april/april_config.h )
CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/april/april_version.h.in ${PROJECT_BINARY_DIR}/april/april_version.h )

set(CMAKE_DEBUG_POSTFIX  "_debug")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# ============================================================================



# ----------------------------------------------------------------------------
# external libraries

find_package(LibBBB REQUIRED)
include_directories(${LIBBBB_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LIBBBB_LIBRARIES})

find_package(ArgTable REQUIRED)
include_directories(${ARGTABLE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${ARGTABLE_LIBRARIES})

add_subdirectory(googletest)
include_directories(googletest/include)

find_package(CmdTest)
# ============================================================================




# ----------------------------------------------------------------------------
# Qt related packages

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
# ============================================================================



# ----------------------------------------------------------------------------
# core library

add_library(april-core SHARED
    april/aprillibrary.cc
    april/april_debug.cc
    april/logic/world.cc
    april/logic/uniqueid.cc
    april/logic/actor.cc
    april/logic/factory.cc
    april/logic/component.cc
    april/logic/dna.cc
    april/logic/dnaview.cc
    april/logic/sensorfactory.cc
    april/logic/eventfactory.cc
    april/logic/actuatorfactory.cc
    april/logic/actorfactory.cc
    april/logic/sensor.cc
    april/logic/reflex.cc
    april/logic/brain.cc
    april/logic/actuator.cc
    april/logic/brainfactory.cc
    april/logic/reflexfactory.cc
    april/logic/actorcomp.cc
    april/logic/eventline.cc
    april/logic/eventdata.cc
    april/logic/director.cc
    april/logic/eventsource.cc
    april/plugins/aprilplugininterf.cc
    april/logic/worldfactory.cc
    april/logic/genericactorfactory.cc
    april/logic/aoutput.cc
)
qt5_use_modules(april-core Core)
set_target_properties(april-core PROPERTIES COMPILE_DEFINITIONS APRIL_LIBRARY )
target_link_libraries(april-core ${LIBS})
# ============================================================================



# ----------------------------------------------------------------------------
# command library

add_library(april-cmd SHARED
    april/cmd/commandmap.cc
    april/cmd/aprilmodule.cc
    april/cmd/apriltokenizer.cc
    april/cmd/modules/amodapril.cc
    april/cmd/modules/amoddna.cc
    april/cmd/modules/amodplugins.cc
    april/cmd/modules/amodworld.cc
    april/cmd/modules/amodid.cc
    april/cmd/modules/amodactor.cc
    april/cmd/modules/amodsensor.cc
    april/cmd/modules/amodreflex.cc
    april/cmd/modules/amodbrain.cc
    april/cmd/modules/amodactuator.cc
    april/cmd/modules/amodevents.cc
)
qt5_use_modules(april-cmd Core)
set_target_properties(april-cmd PROPERTIES COMPILE_DEFINITIONS APRIL_LIBRARY )
target_link_libraries(april-cmd april-core ${LIBS})
# ============================================================================



# ----------------------------------------------------------------------------
# graphical library library

add_library(april-gui SHARED
    april/gui/worlds/worldqscene.cc
    april/gui/worlds/wqstauto.cc
    april/gui/actors/agui.cc
    april/gui/actors/agui3d.cc
    april/gui/actors/agui2d.cc
    april/gui/geometry/p3d.cc
    april/gui/geometry/p2d.cc
    april/gui/geometry/abox3d.cc
    april/gui/geometry/abox2d.cc
    april/gui/actors/aqscene.cc
)
qt5_use_modules(april-gui Core Widgets)
set_target_properties(april-gui PROPERTIES COMPILE_DEFINITIONS APRIL_LIBRARY,APRIL_GUI_LIBRARY )
target_link_libraries(april-gui april-cmd april-core ${LIBS})
# ============================================================================



# ----------------------------------------------------------------------------
# abstracta utility

qt5_add_resources(abstracta_res april/abstracta/abstracta.qrc)
add_executable(abstracta
    april/abstracta/abstracta-main.cc
    april/abstracta/abstractapril.cc
    ${abstracta_res}
)
target_link_libraries(abstracta ${LIBS} april-core april-cmd)
qt5_use_modules(abstracta Core Widgets)
# ============================================================================



# ----------------------------------------------------------------------------
# AprilDream GUI application

qt5_wrap_ui(AprilDream_UIS
    april/AprilDream/gui/mw.ui
    april/AprilDream/gui/newworlddlg.ui
    april/AprilDream/gui/pluginsdlg.ui
    april/AprilDream/gui/dnaeditordlg.ui
    april/AprilDream/gui/newactordlg.ui
    april/AprilDream/gui/cmdlog.ui
)
qt5_add_resources(AprilDream_res april/AprilDream/aprildream.qrc)
add_executable(AprilDream
    april/AprilDream/gui/mw.cc
    april/AprilDream/aprildream-main.cc
    april/AprilDream/propertybrowser/qtvariantproperty.cpp
    april/AprilDream/propertybrowser/qttreepropertybrowser.cpp
    april/AprilDream/propertybrowser/qtpropertymanager.cpp
    april/AprilDream/propertybrowser/qtpropertybrowserutils.cpp
    april/AprilDream/propertybrowser/qtpropertybrowser.cpp
    april/AprilDream/propertybrowser/qtgroupboxpropertybrowser.cpp
    april/AprilDream/propertybrowser/qteditorfactory.cpp
    april/AprilDream/propertybrowser/qtbuttonpropertybrowser.cpp
    april/AprilDream/gui/dock.cc
    april/AprilDream/gui/dockworld.cc
    april/AprilDream/gui/docktree.cc
    april/AprilDream/gui/dockids.cc
    april/AprilDream/gui/dockcrtsel.cc
    april/AprilDream/gui/sceneviewer.cc
    april/AprilDream/gui/newworlddlg.cc
    april/AprilDream/gui/pluginsdlg.cc
    april/AprilDream/gui/dnaeditordlg.cc
    april/AprilDream/gui/newactordlg.cc
    april/AprilDream/gui/cmdlog.cc
    april/AprilDream/gui/dockcmdlog.cc
    ${AprilDream_res}
    ${AprilDream_UIS}
)
target_link_libraries(AprilDream ${LIBS} april-gui april-cmd april-core  )
qt5_use_modules(AprilDream Core Widgets)
set_target_properties(AprilDream PROPERTIES COMPILE_DEFINITIONS QT_DISABLE_DEPRECATED_BEFORE=0 )
# ============================================================================



# ----------------------------------------------------------------------------
# internal tests

add_executable(internal-test
    april/tests/aprillibrary.cc
    april/tests/world.cc
    april/tests/dna.cc
    april/tests/actor.cc
    april/tests/actuator.cc
    april/tests/sensor.cc
    april/tests/reflex.cc
    april/tests/event.cc
    april/tests/brain.cc
    april/tests/simplerun.cpp
    april/tests/eventline.cc
    april/tests/plugins.cc
    april/tests/saveload.cc
    april/tests/saveload2.cc
    april/tests/apriltokenizer.cc
)
target_link_libraries(internal-test ${LIBS} april-cmd april-core gtest_main gtest )
qt5_use_modules(internal-test Core Widgets)
set_target_properties(internal-test PROPERTIES COMPILE_DEFINITIONS APRIL_INTERNAL_TESTS=1 )
# ============================================================================



# ----------------------------------------------------------------------------
# install

install(TARGETS abstracta AprilDream april-core april-cmd april-gui
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

IF (WIN32)
    function(installQt func_list)
        STRING(REGEX REPLACE "/lib/cmake/Qt5Core" "/bin/THELIB.dll" 
                             QtBin "${Qt5Core_DIR}")
        FOREACH (binfile ${func_list})
            STRING(REGEX REPLACE "THELIB" ${binfile} 
                                 QtBin_File "${QtBin}")
            INSTALL(FILES "${QtBin_File}" DESTINATION bin)
        ENDFOREACH(binfile)
    endfunction(installQt)

    set(QtInstallList 
        "Qt5Core"
        "Qt5Widgets"
        "Qt5Gui"
        "libgcc_s_sjlj-1"
        "libstdc++-6"
        "libwinpthread-1"
        "icudt49"
        "icuin49"
        "icuuc49"
        "libGLESv2"
        "D3DCompiler_43"
    )
    installQt( "${QtInstallList}" )
    INSTALL(FILES "${LIBBBB_LIBRARIES}" DESTINATION bin)
ENDIF (WIN32)
# ============================================================================



# ----------------------------------------------------------------------------
# Packing

set(CPACK_PACKAGE_VERSION_MAJOR "${april_MAJOR_VERSION}" )
set(CPACK_PACKAGE_VERSION_MINOR "${april_MINOR_VERSION}" )
set(CPACK_PACKAGE_VERSION_PATCH "${april_PATCH_VERSION}" )
set(CPACK_PACKAGE_DESCRIPTION "Package to run worlds")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Package to run worlds")
set(CPACK_PACKAGE_CONTACT "Nicu Tofan nicu.tofan@gmail.com")
SET(CPACK_PACKAGE_VENDOR "Nicu Tofan")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "April-${april_MAJOR_VERSION}.${april_MINOR_VERSION}")
SET(CPACK_PACKAGE_EXECUTABLES "AprilDream" "AprilDream")

IF (APPLE)
    SET(CPACK_BINARY_DRAGNDROP ON)
ENDIF (APPLE)

IF (WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    # SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
    SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\AprilDream.exe")
    SET(CPACK_NSIS_DISPLAY_NAME "April")
    # SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
    # SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
    SET(CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT})
    SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
    SET(CPACK_STRIP_FILES "bin/AprilDream")
    SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)

IF (UNIX)
    set(CPACK_GENERATOR "DEB")

    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtgui5")
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")
ENDIF (UNIX)

include(CPack)
# ============================================================================



# ----------------------------------------------------------------------------
# Testing

IF (WIN32)
    function(copyQt func_list)
        STRING(REGEX REPLACE "/lib/cmake/Qt5Core" "/bin/THELIB.dll" 
                             QtBin "${Qt5Core_DIR}")
        FOREACH (binfile ${func_list})
            STRING(REGEX REPLACE "THELIB" ${binfile} 
                                 QtBin_File "${QtBin}")
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QtBin_File}" "${PROJECT_BINARY_DIR}/${binfile}.dll"
                WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            )
        ENDFOREACH(binfile)
    endfunction(copyQt)
    copyQt( "${QtInstallList}" )
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LIBBBB_LIBRARIES}" "${PROJECT_BINARY_DIR}/libbbb.dll")
ENDIF (WIN32)

enable_testing()
add_test( NAME Internal
          COMMAND internal-test )

IF (CMDTEST_FOUND)
    execute_process(COMMAND ${CMDTEST_PROGRAM} "${CMAKE_SOURCE_DIR}/april/tests/cmd-test-abstracta/all-tests.txt" 
                    WORKIND_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test( NAME CmdTest
              COMMAND ${CMDTEST_PROGRAM} "${CMAKE_SOURCE_DIR}/april/tests/cmd-test-abstracta/all-tests.txt"
              )
ENDIF (CMDTEST_FOUND)

# ============================================================================

