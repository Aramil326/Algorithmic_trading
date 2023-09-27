CC = gcc -std=c++17
WWW = -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Linux)
	CHFLAGS = -lpthread -lrt -lm -lsubunit -lstdc++
else
	CHFLAGS = -lm -lstdc++
endif

all: clean install

clean:
	rm -rf *.o

install:
	rm -rf myapp_release
	rm -rf instal_release
	mkdir instal_release
	mkdir myapp_release
	cd instal_release && \
		cmake -DCMAKE_BUILD_TYPE=Release -D EXECUTABLE_OUTPUT_PATH="../myapp_release" ../ &&  \
		cmake --build ../instal_release/. && \
		rm -rf ../instal_release

uninstall:
	rm -rf myapp_release

dist: install
	tar -cf my_app.tar.gz myapp_release/
	rm -rf myapp_release

dvi:
	open dvi.md

style:
	clang-format -style=google -n \
	controller/controller.cc \
	controller/controller.h \
    libs/qcustomplot/qcustomplot.cc \
    libs/qcustomplot/qcustomplot.h \
	model/cubic_spline/cubic_spline.cc \
	model/cubic_spline/cubic_spline.h \
	model/facade/facade.cc \
	model/facade/facade.h \
	model/math_algorithms/gauss.cc \
	model/math_algorithms/gauss.h \
	model/file_reader/error_load_type.h \
    model/file_reader/file_reader.cc \
    model/file_reader/file_reader.h \
	model/matrix/matrix.cc \
	model/matrix/matrix.h \
	model/polynomial_approximation/polynomial_approximation.cc \
	model/polynomial_approximation/polynomial_approximation.h \
	view/graph_widget/graph_widget.cc \
	view/graph_widget/graph_widget.h \
	view/main_window/mainwindow.cc \
	view/main_window/mainwindow.h \
	view/second_window/second_window.cc \
	view/second_window/second_window.h \
	view/error_handler.cc \
	view/error_handler.h \
	main.cpp