#pragma once
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void setColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void showCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void veHCN(int toadoX, int toadoY, int chieudai, int chieucao)
{
	textcolor(240);
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}
}
void toMauHCN(int toadoX, int toadoY, int chieudai, int chieucao, int mauText)
{
	textcolor(mauText);
	for (int i = toadoY + 1; i < toadoY + chieucao; i++)
	{
		for (int j = toadoX + 1; j < chieudai + toadoX; j++)
		{
			gotoXY(j, i);
			cout << " ";
		}
	}
	textcolor(7);
}

void tittleMain(int toadoX, int toadoY){
	string str;
	ifstream FileIn;
	FileIn.open("inputTittle.txt", ios::in);
	int h = toadoY;
	setColor(12);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();
}

void titleMH(int toadoX, int toadoY){
	string str;
	ifstream FileIn;
	FileIn.open("titlemh.txt", ios::in);
	int h = toadoY;
	setColor(10);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();
}

void titleSV(int toadoX, int toadoY){
	string str;
	ifstream FileIn;
	FileIn.open("titlesv.txt", ios::in);
	int h = toadoY;
	setColor(10);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();
}

void titleLTC(int toadoX, int toadoY){
	string str;
	ifstream FileIn;
	FileIn.open("titleLTC.txt", ios::in);
	int h = toadoY;
	setColor(10);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();
}

void titleDSDK(int toadoX, int toadoY){
	string str;
	ifstream FileIn;
	FileIn.open("titleDSDK.txt", ios::in);
	int h = toadoY;
	setColor(10);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();
}

void titleDKLTC(int toadoX, int toadoY){
	string str;
	ifstream FileIn;
	FileIn.open("titleDKLTC.txt", ios::in);
	int h = toadoY;
	setColor(10);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();
}

void giaoDienThongBao(string x){
	//toMauHCN(70, 28, 50, 5, 47);
	textcolor(47);
	gotoXY(72, 40);
	cout << string((49 - x.length()) / 2, ' ') + x;
	getch();
	textcolor(7);
}
void giaoDienMain(){
	tittleMain(35, 5);
	veHCN(50, 15, 65, 22);
	veHCN(52, 13, 65, 22);
}
void giaoDienMH(){
	titleMH(45, 5);
	veHCN(42, 15, 85, 19);
	veHCN(44, 14, 85, 19);
}
void giaoDienSV(){
	titleSV(42, 3);
	veHCN(42, 13, 87, 26);
	veHCN(44, 12, 87, 26);
}
void giaoDienLTC(){
	titleLTC(40, 3);
	veHCN(42, 13, 87, 26);
	veHCN(44, 12, 87, 26);
}
void giaoDienDSDK(){
	titleDSDK(45,3);
	veHCN(42, 13, 87, 22);
	veHCN(44, 12, 87, 22);
}
void giaoDienDKLTC(){
	titleDKLTC(38,3);
	veHCN(42, 13, 87, 22);
	veHCN(44, 12, 87, 22);
}
void giaoDienThemLopTC(int toadoX, int toadoY){
	giaoDienLTC();
	gotoXY(toadoX - 10, 15);
	cout << "Ma Lop Tin Chi:";
	gotoXY(toadoX - 20, 18);
	cout << "Ma Mon Hoc:";
	gotoXY(toadoX - 20, 21);
	cout << "Nien Khoa:";
	gotoXY(toadoX - 20, 24);
	cout << "Hoc Ki:";
	gotoXY(toadoX - 20, 27);
	cout << "Nhom:";
	gotoXY(toadoX - 20, 30);
	cout << "So Sinh Vien Max:";
	gotoXY(toadoX - 20, 33);
	cout << "So Sinh Vien Min:";

	gotoXY(toadoX + 15, toadoY + 20);
	cout << "Xac Nhan";
	gotoXY(toadoX + 30, toadoY + 20);
	cout << "Thoat";

	veHCN(toadoX , toadoY, 50, 2);
	veHCN(toadoX , toadoY + 3, 50, 2);
	veHCN(toadoX , toadoY + 6, 50, 2);
	veHCN(toadoX, toadoY + 9, 50, 2);
	veHCN(toadoX, toadoY + 12, 50, 2);
	veHCN(toadoX, toadoY + 15, 50, 2);
	textcolor(240);
}
void giaoDienThemSinhVien(int toadoX, int toadoY){
	
	gotoXY(toadoX - 20, 15);
	cout << "Ma Lop:";
	gotoXY(toadoX - 20, 18);
	cout << "Ma Sinh Vien:";
	gotoXY(toadoX - 20, 21);
	cout << "Ho Va Ten Lot:";
	gotoXY(toadoX - 20, 24);
	cout << "Ten:";
	gotoXY(toadoX - 20, 27);
	cout << "Phai(Nam:1, Nu:2):";
	gotoXY(toadoX - 20, 30);
	cout << "SDT:";
	gotoXY(toadoX - 20, 33);
	cout << "Nam Nhap Hoc:";
	
	gotoXY(toadoX + 15, toadoY + 20);
	cout << "Xac Nhan";
	gotoXY(toadoX + 30, toadoY + 20);
	cout << "Thoat";
	
	veHCN(toadoX, toadoY-3, 50, 2);
	veHCN(toadoX, toadoY, 50, 2);
	veHCN(toadoX, toadoY + 3, 50, 2);
	veHCN(toadoX, toadoY + 6, 50, 2);
	veHCN(toadoX, toadoY + 9, 50, 2);
	veHCN(toadoX, toadoY + 12, 50, 2);
	veHCN(toadoX, toadoY + 15, 50, 2);
	giaoDienSV();
	textcolor(240);
}
void giaoDienThemMonHoc(int toadoX, int toadoY){
	giaoDienMH();
	gotoXY(toadoX - 20, 18);
	cout << "Ma Mon Hoc:";
	gotoXY(toadoX - 20, 21);
	cout << "Ten Mon Hoc:";
	gotoXY(toadoX - 20, 24);
	cout << "So TCLT:";
	gotoXY(toadoX - 20, 27);
	cout << "So TCTH:";

	gotoXY(toadoX + 15, toadoY + 15);
	cout << "Xac Nhan";
	gotoXY(toadoX + 30, toadoY + 15);
	cout << "Thoat";

	veHCN(toadoX, toadoY, 50, 2);
	veHCN(toadoX, toadoY + 3, 50, 2);
	veHCN(toadoX, toadoY + 6, 50, 2);
	veHCN(toadoX, toadoY + 9, 50, 2);
	textcolor(240);
}

void giaoDienInDSLopTC(int toadoX, int toadoY, int n){
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 30 || i == toadoX + 50 || i == toadoX + 80 || i == toadoX + 85)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 30 || i == toadoX + 50 || i == toadoX + 80 || i == toadoX + 85)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << "Ma Lop TC";
	gotoXY(toadoX + 11, toadoY + 1);
	cout << "Ma Lop";
	gotoXY(toadoX + 31, toadoY + 1);
	cout << "Ma SV";
	gotoXY(toadoX + 51, toadoY + 1);
	cout << "Ho Ten";
	gotoXY(toadoX + 81, toadoY + 1);
	cout << "Phai";
	gotoXY(toadoX + 86, toadoY + 1);
	cout << "SDT";
}
void giaoDienInDSSV(int toadoX, int toadoY, int n){
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 20 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 20|| i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << "Ma SV";
	gotoXY(toadoX + 21, toadoY + 1);
	cout << "Ho Ten";
	gotoXY(toadoX + 61, toadoY + 1);
	cout << "Phai";
	gotoXY(toadoX + 71, toadoY + 1);
	cout << "SDT";
	gotoXY(toadoX + 81, toadoY + 1);
	cout << "Nam Nhap Hoc";
}

void giaoDienInDSMH(int toadoX, int toadoY, int n){
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 30 || i == toadoX + 80 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 30 || i == toadoX + 80 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << "Ma Mon Hoc";
	gotoXY(toadoX + 31, toadoY + 1);
	cout << "Ten Mon Hoc";
	gotoXY(toadoX + 81, toadoY + 1);
	cout << "STCLT";
	gotoXY(toadoX + 91, toadoY + 1);
	cout << "STCTH";
}

void giaoDienChonLopTC(int toadoX, int toadoY){
	giaoDienDSDK();
	gotoXY(toadoX - 20, 18);
	cout << "Nien Khoa:";
	gotoXY(toadoX - 20, 21);
	cout << "Hoc Ki:";
	gotoXY(toadoX - 20, 24);
	cout << "Nhom:";
	gotoXY(toadoX - 20, 27);
	cout << "Ma Mon Hoc:";

	gotoXY(toadoX + 15, toadoY + 15);
	cout << "Xac Nhan";
	gotoXY(toadoX + 30, toadoY + 15);
	cout << "Thoat";

	veHCN(toadoX, toadoY, 50, 2);
	veHCN(toadoX, toadoY + 3, 50, 2);
	veHCN(toadoX, toadoY + 6, 50, 2);
	veHCN(toadoX, toadoY + 9, 50, 2);
	textcolor(240);
}

void giaoDienNhapNKHK(int toadoX, int toadoY){
	gotoXY(toadoX - 15, 18);
	cout << "Nien Khoa:";
	gotoXY(toadoX - 15, 21);
	cout << "Hoc Ki:";

	gotoXY(toadoX + 15, toadoY + 15);
	cout << "Xac Nhan";
	gotoXY(toadoX + 30, toadoY + 15);
	cout << "Thoat";

	veHCN(toadoX, toadoY, 50, 2);
	veHCN(toadoX, toadoY + 3, 50, 2);
	textcolor(240);
}

void giaoDienDKLopTinChi(int toadoX, int toadoY,int n){
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 20 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 20 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}
	gotoXY(toadoX + 1, toadoY + 1);
	cout << "Ma Lop";
	gotoXY(toadoX + 11, toadoY + 1);
	cout << "Ma MH";
	gotoXY(toadoX + 31, toadoY + 1);
	cout << "Ten Mon Hoc";
	gotoXY(toadoX + 61, toadoY + 1);
	cout << "Nhom";
	gotoXY(toadoX + 71, toadoY + 1);
	cout << "STC";
	gotoXY(toadoX + 81, toadoY + 1);
	cout << "SLCL";
	gotoXY(toadoX + 91, toadoY + 1);
	cout << "Chon";

	gotoXY(toadoX +15 + 30, toadoY + 6 + 2 * n);
	cout << "Xac Nhan";
	gotoXY(toadoX + 15+ 60, toadoY + 6 + 2 * n);
	cout << "Thoat";
}

void giaoDienXuatDSLopTCDaDK(int toadoX, int toadoY, int n){
	gotoXY(toadoX+40, toadoY - 2);
	cout << "DANH SACH LUU DANG KY";

//	int chieucao = 3 + 2 * n;
//	int chieudai = 60;
//	for (int i = toadoX+30; i <= chieudai + toadoX+30; i++)
//	{
//		gotoXY(i, toadoY);
//		if (i == toadoX+30)
//			cout << (char)218;
//		else if (i == chieudai + toadoX+30)
//			cout << (char)191;
//		else
//			cout << (char)196;
//	}
//	for (int i = toadoX+30; i <= chieudai + toadoX+30; i++)
//	{
//		gotoXY(i, chieucao + toadoY);
//		if (i == toadoX+30)
//			cout << (char)192;
//		else if (i == chieudai + toadoX+30)
//			cout << (char)217;
//		else
//			cout << char(196);
//	}
//	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
//	{
//		gotoXY(toadoX+30, i);
//		cout << (char)179;
//	}
//	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
//	{
//		gotoXY(chieudai + toadoX+30, i);
//		cout << (char)179;
//	}
//	
//	// gach xuong
//	for (int i = toadoX + 31; i < chieudai + toadoX+30; i++)
//	{
//		if (i == toadoX + 40 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80 )
//		{
//			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
//			{
//				gotoXY(i, j);
//				if (j == toadoY)
//					cout << char(194);
//				else if (j == chieucao + toadoY)
//					cout << char(193);
//				else
//					cout << (char)179;
//			}
//		}
//	}
//
//	// gach ngang
//	for (int j = 3; j < chieucao; j = j + 2)
//	{
//		for (int i = toadoX+30; i <= chieudai + toadoX+30; i++)
//		{
//			gotoXY(i, toadoY + j);
//			if (i == toadoX+30)
//				cout << (char)195;
//			else if (i == chieudai + toadoX+30)
//				cout << (char)180;
//			else if (i == toadoX + 40 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80 )
//				cout << (char)197;
//			else
//				cout << (char)196;
//		}
//	}
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}


	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 20 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90 )
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}


	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 20 || i == toadoX + 60 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90 )
				cout << (char)197;
			else
				cout << (char)196;
		}
	}
	gotoXY(toadoX + 1, toadoY + 1);
	cout << "Ma Lop";
	gotoXY(toadoX + 11, toadoY + 1);
	cout << "Ma MH";
	gotoXY(toadoX + 21, toadoY + 1);
	cout << "Ten Mon Hoc";
	gotoXY(toadoX + 61, toadoY + 1);
	cout << "Nhom";
	gotoXY(toadoX + 71, toadoY + 1);
	cout << "STC";
	gotoXY(toadoX + 81, toadoY + 1);
	cout << "Si So";
	gotoXY(toadoX + 91, toadoY + 1);
	cout << "Con lai";
}

void giaoDienNhapDiem(int toadoX, int toadoY, int n){
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 40 || i == toadoX + 70 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 40 || i == toadoX + 70 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout <<"STT";
	gotoXY(toadoX + 11, toadoY + 1);
	cout << "MSSV";
	gotoXY(toadoX + 41, toadoY + 1);
	cout << "Ho";
	gotoXY(toadoX + 71, toadoY + 1);
	cout << "Ten";
	gotoXY(toadoX + 91, toadoY + 1);
	cout << "Diem";
}
