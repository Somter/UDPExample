#include <iostream>
#include <Windows.h>
using namespace std;	

int main()
{
	/*system("color 0A");
	cout << "Hello world";

	system("color 0D");
	cout << "Hello world";*/

	COORD point{ 0,0 }; // ���������� �����
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ����� ������������ ������

	SetConsoleCursorPosition(h, point); // ������������� ������ � ��������� �������
	SetConsoleTextAttribute(h, 12); // �������� ���� ������
	cout << "Hello world";    // ������� ����� � ��������� �������

	// ������ ��������� �����
	// point.Y += 1; // ������
	point.X += 12;  // �������
	SetConsoleCursorPosition(h, point); // ������������� ������ � ��������� �������
	SetConsoleTextAttribute(h, 14);  // �������� ���� ������
	cout << "Hello world";    // ������� ����� � ��������� �������

	point.Y += 1;  // ��������� �� ����� ������	
	point.X = 0; // ������ ������
	SetConsoleCursorPosition(h, point);
	SetConsoleTextAttribute(h, 11);
	cout << "Hello world\n";

	SetConsoleTextAttribute(h, 7); // ����������� ����!

	return 0; // �������� ���������� ���������
}	
