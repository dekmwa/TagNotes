cmake_minimum_required(VERSION 3.16)

project(TagNotes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Charts)

set(SOURCES
    main.cpp

    src/mainwindow.cpp
    src/noteswidget.cpp
    src/qflowlayout.cpp
    src/database.cpp
    src/edittagsorcategorieswidget.cpp
    src/mainmenuwidget.cpp
    src/tagsviewer.cpp
    src/tagsbydatewidget.cpp
    src/categoriesviewer.cpp
    src/categoriesandtagswidget.cpp
    src/charts.cpp
    src/databasesettingswidget.cpp
    src/customcalendar.cpp
    src/statisticswidget.cpp
    src/customapppanel.cpp
)

set(HEADERS
    src/mainwindow.h
    src/noteswidget.h
    src/qflowlayout.h
    src/database.h
    src/edittagsorcategorieswidget.h
    src/mainmenuwidget.h
    src/tagsviewer.h
    src/tagsbydatewidget.h
    src/categoriesviewer.h
    src/categoriesandtagswidget.h
    src/charts.h
    src/databasesettingswidget.h
    src/customcalendar.h
    src/statisticswidget.h
    src/customapppanel.h
)

set(UI_FILES
    src/databasesettingswidget.ui
)

qt_add_executable(
    TagNotes
    resources.qrc
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    themes/purple1.qss
    themes/blue.qss
    themes/light.qss
)

target_link_libraries(TagNotes PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Charts
)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)

if(WIN32)
    set_target_properties(TagNotes PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(APPLE)
    set_target_properties(TagNotes PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TagNotes
    )
endif()
