#include <iostream>
#include <Windows.h>
using namespace std;	

int main()
{
	/*system("color 0A");
	cout << "Hello world";

	system("color 0D");
	cout << "Hello world";*/

	COORD point{ 0,0 }; // Координата точки
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем адрес стандартного вывода

	SetConsoleCursorPosition(h, point); // Устанавливаем курсор в указанную позицию
	SetConsoleTextAttribute(h, 12); // Изменяем цвет шрифта
	cout << "Hello world";    // Выводим текст в указанной позиции

	// Замена координат точки
	// point.Y += 1; // Строки
	point.X += 12;  // Столбцы
	SetConsoleCursorPosition(h, point); // Устанавливаем курсор в указанную позицию
	SetConsoleTextAttribute(h, 14);  // Изменяем цвет шрифта
	cout << "Hello world";    // Выводим текст в указанной позиции

	point.Y += 1;  // Переходим на новую строку	
	point.X = 0; // Начало строки
	SetConsoleCursorPosition(h, point);
	SetConsoleTextAttribute(h, 11);
	cout << "Hello world\n";

	SetConsoleTextAttribute(h, 7); // Стандартный цвет!

	return 0; // Успешное завершение программы
}	
