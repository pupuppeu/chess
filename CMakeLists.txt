cmake_minimum_required(VERSION 3.15)
project(chess)
project(chess2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

add_executable(chess main.cpp Board.cpp Board.h Stone.cpp Stone.h SingleGame.cpp SingleGame.h Step.cpp Step.h NetGame.cpp NetGame.h ChooseDlg.cpp ChooseDlg.h MainWnd.cpp MainWnd.h)
target_link_libraries(chess Qt5::Core)
target_link_libraries(chess Qt5::Widgets)
target_link_libraries(chess Qt5::Network)

add_executable(chess2 main2.cpp Board.cpp Board.h Stone.cpp Stone.h SingleGame.cpp SingleGame.h Step.cpp Step.h NetGame.cpp NetGame.h ChooseDlg.cpp ChooseDlg.h MainWnd.cpp MainWnd.h)
target_link_libraries(chess2 Qt5::Core)
target_link_libraries(chess2 Qt5::Widgets)
target_link_libraries(chess2 Qt5::Network)

