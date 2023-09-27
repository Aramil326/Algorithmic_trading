## Интерполяция таблично заданных функций методом кубических сплайнов
Кубический сплайн — гладкая функция, область определения которой разбита на конечное число отрезков, на каждом из которых она совпадает с некоторым кубическим многочленом (полиномом)

![cubic_splain_1.png](../misc/images/cubic_splain_1.png)

Нужно найти коэффициенты A B C D

Т.к. имеются условия, которым должен удовлетворять кубический сплайн, то выводят формулы для вычисления коэффициентов:
 - Коэффициент А <br>
![cubic_splain_2.png](../misc/images/cubic_splain_2.png)
 - Коэффициент B <br>
![cubic_splain_3.png](../misc/images/cubic_splain_3.png)
 - Коэффициент D <br>
![cubic_splain_4.png](../misc/images/cubic_splain_4.png)
 - Коэффициент C <br>
![cubic_splain_5.png](../misc/images/cubic_splain_5.png)
Где h<sub>i</sub> = x<sub>i</sub> - x<sub>i-1</sub>

Если учесть, что C<sub>0</sub> = C<sub>n</sub> = 0, то вычисление коэффициента C можно провести с помощью метода прогонки для трёхдиагональной матрицы.

Сначала нужно рассчитать прогоночные коэффициенты. <br>
Выводятся следующие формулы для прогоночных коэффициентов.
![cubic_splain_6.png](../misc/images/cubic_splain_6.png)
Где к и l- прогоночные коэффициенты
![cubic_splain_7.png](../misc/images/cubic_splain_7.png)

Вычислив прогоночные коэффициенты можно вычислить коэффициенты С
![cubic_splain_8.png](../misc/images/cubic_splain_8.png)

Вычислив коэффициенты С можно вычислить остальные коэффициенты.

http://nickolay.info/algorithms/pas_ispline.html

http://www.machinelearning.ru/wiki/index.php?title=Интерполяция_кубическими_сплайнами


## Аппроксимация функций полиномом методом наименьших квадратов.
Требуется определить параметры a<sub>i</sub> многочлена вида
![approc_1.png](../misc/images/approc_1.png)

Путем математической магии все сводится к тому, что нужно составить и решить следующую SLE:
![approc_2.png](../misc/images/approc_2.png)

Получив все коэффициенты, подставляем в функцию X и находим Y.