cmake_minimum_required(VERSION 3.16)

project(TagNotes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Поиск Qt6 с нужными компонентами
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql        # Добавили SQL
)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Список исходников
set(SOURCES
    main.cpp
    mainwindow.cpp
    noteswidget.cpp
    qflowlayout.cpp
    selecttagswidget.cpp
)

set(HEADERS
    mainwindow.h
    noteswidget.h
    qflowlayout.h
    selecttagswidget.h
)

# Создание исполняемого файла
qt_add_executable(TagNotes ${SOURCES} ${HEADERS}
    database.h database.cpp
    tagsbydatewidget.h tagsbydatewidget.cpp
    deletetagsorcategorieswidget.h deletetagsorcategorieswidget.cpp
    mainmenuwidget.h mainmenuwidget.cpp
    tagsviewer.h tagsviewer.cpp
    tagsbydatewidget2.h tagsbydatewidget2.cpp
    categoriesviewer.h categoriesviewer.cpp)

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
