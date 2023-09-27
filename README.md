Реализация проекта Algorithmic trading.

## Примененные технологии
* C++
* QT (GUI)
* clang-format (style testing)
* QCustomPlot (graph lib)

## Примененные паттерны
* MVC
* Facade
* Singleton

## Содержание

1. [Вступление]()
4. [Теория]()
2. [Part 1. Интерполяция таблично заданных функций методом кубических сплайнов]()
3. [Part 2. Аппроксимация таблично заданных функций]()


## Вступление

Мы успешно познакомились с алгоритмами интерполяции и аппроксимации в рамках данного проекта. Используя эти алгоритмы, мы строили графики вероятностного поведения котировок акций и прогнозировали их курсы для обозримого будущего на основе исторических данных. Этот анализ проводился без учета внешних факторов.

> Примечание: Важно отметить, что для точных прогнозов курсов акций часто требуется учет множества внешних факторов, и алгоритмы интерполяции и аппроксимации могут использоваться только как инструменты для приближенного анализа.

## Теория
[Теория](src/theory.md)

## Part 1. Интерполяция таблично заданных функций методом кубических сплайнов

Реализация построения графиков таблично заданной функции котировок акций с использованием метода кубических сплайнов:

- Программа разработана на языке C++ стандарта C++17
- При написании кода придерживались Google Style
- Сборка программы настроена с помощью Makefile со стандартным набором целей для GNU-программ: all, install, uninstall, clean, dvi, dist. Установка ведется в каталог myapp_release
- В программе реализован графический пользовательский интерфейс, на базе GUI-библиотеки с API для C++ Qt.
- Данные загружаются в программу из файла с котировками акций с расширением .csv:
    - В файле данные представлены в виде таблицы, где первый столбец - дата, второй столбец - значение функции (примеры файлов с данными находятся в папке materials)
- При загрузке нового файла с данными поле для рисования графиков очищается
- Пользователем задаётся количество точек, по которым должен быть построен график (количество точек не меньше, чем в загруженном файле)
- Все точки распределены равномерно между начальной и конечной датами
- На итоговом графике соседние точки соединены прямой линией
- Реализован метод интерполяции *кубическим сплайном*
- В интерфейсе есть кнопка для отрисовки графика, полученного кубическим сплайном
- В интерфейсе есть кнопка очистки поля для рисования графиков (поле очищается только при нажатии на эту кнопку или загрузке новых данных)
- На поле может быть одновременно изображено до 5 графиков (при этом все графики разного цвета)
    - Если на поле уже отображено 5 графиков, блокируются кнопки отрисовки новых графиков
- В интерфейсе указана следующая информация о графиках:
    - Цвет
    - Имя файла, из которого были взяты данные
- Предусмотрена возможность по заданному пользователем значению аргумента (дата и время) вывести значения функции котировок акций, полученные методом интерполяции

## Part 2. Аппроксимация таблично заданных функций

Реализовано построение графиков таблично заданной функции котировок акций с использованием *метода наименьших квадратов*. \
При этом график покрывает больший промежуток времени, чем исходные данные:
- Для графиков из этого задания в интерфейсе отведено отдельное окно для отрисовки
- При загрузке нового файла с данными очищается поле для рисования графиков
- Пользователем задаётся количество точек, по которым должен быть построен график (количество точек не меньше, чем в загруженном файле)
- Все точки распределены равномерно между начальной и конечной датами
- На итоговом графике соседние точки соединены прямой линией
- На графике явно отмечены точки, заданные в загруженном файле:
    - Радиус этих точек больше толщины кривой графика
    - Цвет этих точек не совпадает с цветами графиков на поле
- Пользователем задается количество дней `M`, на которое нужно продлить график (на сколько дней вперёд мы хотим предсказать курс акций)
- При добавлении на поле отрисовки нового графика аппроксимации, у которого `M` отличается от `M` уже отрисованных графиков, предварительно выполняется очистка поля отрисовки
- На поле может быть одновременно изображено до 5 графиков с одним и тем же значением числа дней `M` (при этом все графики разного цвета)
- В интерфейсе есть кнопка для отрисовки графика, полученного полиномом заданной в данный момент степени
- В интерфейсе есть поле для ввода степени полинома
- В интерфейсе есть кнопка очистки поля для рисования графиков аппроксимации
- В интерфейсе указана следующая информация о графиках:
    - Цвет
    - Файл, из которого взяты данные
    - Степень полинома
- Если на поле уже отображено 5 графиков, блокируются кнопки отрисовки новых графиков аппроксимации
- Предусмотрена возможность по заданному пользователем значению аргумента (дата и время) вывести значение аппроксимирующей функции для заданной степени полинома
