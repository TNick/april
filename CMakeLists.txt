cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(april)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(LibBBB REQUIRED)
include_directories(${LIBBBB_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LIBBBB_LIBRARIES})

find_package(ArgTable REQUIRED)
include_directories(${ARGTABLE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${ARGTABLE_LIBRARIES})

add_subdirectory(googletest)
include_directories(googletest/include)


# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

add_library(april-core
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

add_library(april-cmd
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

add_library(april-gui
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
set_target_properties(april-gui PROPERTIES COMPILE_DEFINITIONS APRIL_LIBRARY )
set_target_properties(april-gui PROPERTIES COMPILE_DEFINITIONS APRIL_GUI_LIBRARY )

qt5_add_resources(abstracta_res april/abstracta/abstracta.qrc)
add_executable(abstracta
    april/abstracta/abstracta-main.cc
    april/abstracta/abstractapril.cc
    ${abstracta_res}
)
target_link_libraries(abstracta ${LIBS} april-cmd april-core)
qt5_use_modules(abstracta Core Widgets)


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



install(TARGETS abstracta AprilDream april-core april-cmd april-gui
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
    #message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

