cmake_minimum_required(VERSION 3.5)

project(TRADING VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        view/main_window/mainwindow.cc
        view/main_window/mainwindow.h
        view/main_window/mainwindow.ui

        view/second_window/second_window.h
        view/second_window/second_window.cc
        view/second_window/second_window.ui

        libs/qcustomplot/qcustomplot.h
        libs/qcustomplot/qcustomplot.cc
        model/file_reader/file_reader.cc
        model/file_reader/file_reader.h
        controller/controller.cc
        controller/controller.h
        model/facade/facade.cc
        model/facade/facade.h

        view/graph_widget/graph_widget.cc
        view/graph_widget/graph_widget.h

        model/cubic_spline/cubic_spline.cc
        model/cubic_spline/cubic_spline.h
        model/polynomial_approximation/polynomial_approximation.cc
        model/polynomial_approximation/polynomial_approximation.h
        model/matrix/matrix.cc
        model/matrix/matrix.h
        model/file_reader/error_load_type.h
        view/error_handler.cc
        view/error_handler.h model/math_algorithms/gauss.cc model/math_algorithms/gauss.h)

add_executable(algorithmic_trading ${PROJECT_SOURCES} )

install(TARGETS algorithmic_trading
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(algorithmic_trading PRIVATE Qt${QT_VERSION_MAJOR}::Widgets -lstdc++)
