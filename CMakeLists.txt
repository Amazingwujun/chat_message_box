cmake_minimum_required(VERSION 3.25)
project(chat_message_box)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.14.2/5.14.2/mingw73_64")

set(QRC_FILES img.qrc)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(chat_message_box main.cpp chatmessagewrapperwidget.cpp chatmessagewrapperwidget.h ${QRC_FILES} chatwidget.cpp chatwidget.h chatwidget.ui)
target_link_libraries(chat_message_box
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )