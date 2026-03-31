cmake_minimum_required(VERSION 3.16)

project(TagNotes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

set(SOURCES
    main.cpp
    mainwindow.cpp
    noteswidget.cpp
    qflowlayout.cpp
    selecttagswidget.cpp
    database.cpp
)

set(HEADERS
    mainwindow.h
    noteswidget.h
    qflowlayout.h
    selecttagswidget.h
    database.h
)

# Создание исполняемого файла
qt_add_executable(TagNotes ${SOURCES} ${HEADERS}
    tagsbydatewidget.h tagsbydatewidget.cpp
    deletetagsorcategorieswidget.h deletetagsorcategorieswidget.cpp
    mainmenuwidget.h mainmenuwidget.cpp
    tagsviewer.h tagsviewer.cpp
    tagsbydatewidget2.h tagsbydatewidget2.cpp
    categoriesviewer.h categoriesviewer.cpp
    categoriesandtagswidget.h categoriesandtagswidget.cpp)

# Линковка с Qt библиотеками
target_link_libraries(TagNotes PRIVATE
    Qt6::Widgets
    Qt6::Sql      # Вот здесь добавляем SQL
)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)
target_link_libraries(TagNotes PRIVATE Qt6::Widgets)

# Настройки для Windows
if(WIN32)
    set_target_properties(TagNotes PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Настройки для macOS
if(APPLE)
    set_target_properties(TagNotes PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TagNotes
    )
endif()
