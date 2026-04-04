cmake_minimum_required(VERSION 3.16)

project(TagNotes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Charts)

set(SOURCES
    main.cpp
    mainwindow.cpp
    noteswidget.cpp
    qflowlayout.cpp
    database.cpp
    deletetagsorcategorieswidget.cpp
    mainmenuwidget.cpp
    tagsviewer.cpp
    tagsbydatewidget2.cpp
    categoriesviewer.cpp
    categoriesandtagswidget.cpp
    charts.cpp
    databasesettingswidget.cpp
)

set(HEADERS
    mainwindow.h
    noteswidget.h
    qflowlayout.h
    database.h
    deletetagsorcategorieswidget.h
    mainmenuwidget.h
    tagsviewer.h
    tagsbydatewidget2.h
    categoriesviewer.h
    categoriesandtagswidget.h
    charts.h
    databasesettingswidget.h
)

set(UI_FILES
    databasesettingswidget.ui
)

qt_add_executable(TagNotes
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

target_link_libraries(TagNotes PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Charts
)

if(WIN32)
    set_target_properties(TagNotes PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(APPLE)
    set_target_properties(TagNotes PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TagNotes
    )
endif()
