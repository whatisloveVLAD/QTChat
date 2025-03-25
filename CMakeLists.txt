cmake_minimum_required(VERSION 3.5)

project(chat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем только Qt5
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Network)

# Объединяем все исходные файлы проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    chatwindow.h
    chatwindow.cpp
)

# Создаём исполняемый файл для Qt5
add_executable(chat ${PROJECT_SOURCES}
    ClickLabel.h)

# Линкуем с библиотеками Qt5
target_link_libraries(chat PRIVATE Qt5::Widgets Qt5::Network)

# Настройки для сборки на macOS/Windows
set_target_properties(chat PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS chat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
