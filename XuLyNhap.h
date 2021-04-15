#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<iomanip>
#include<math.h>

int countNumInt(int n)
{
	int dem = 0;
	while (n > 0)
	{
		n = n / 10;
		dem++;
	}
	return dem;
}
char convertIntToChar(int n)
{
	switch (n)
	{
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 0:
		return '0';
	}
}
void formatString(string& str)
{
	//Xoa khoang trong
	while (str[0] == ' ')
	{
		str.erase(str.begin() + 0);
	}
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.begin() + (str.length() - 1));
	}

	for (int i = 1; i < str.length() - 1; i++)
	{
		if (str[i + 1] == ' ' && str[i] == ' ')
		{
			str.erase(str.begin() + i);
			i--;
		}
	}
	//Viet thuong all lai
	for (int i = 0; i < str.length(); i++)
	{
		if ((65 <= str[i] && str[i] <= 90) && str[i] != ' ')
		{
			str[i] = str[i] + 32;
		}
	}
	//Viet hoa
	for (int i = 0; i < str.length(); i++)
	{
		if (i == 0 && (97 <= str[i] && str[i] <= 122))
		{
			str[0] = str[0] - 32;
		}
		if (str[i] == ' ' && (97 <= str[i+1] && str[i + 1] <= 122))
		{
			str[i + 1] = str[i + 1] - 32;
		}
	}

}
string convertIntToString(int n)
{
	string str="";
	int a;
	while (n > 0)
	{
		a = n % 10;
		convertIntToChar(a);
		str.insert(str.begin(), convertIntToChar(a));
		n = n / 10;
	}
	return str;
}

string floatToStr(float n, int soTP){
	string str;
	int a = 0;
	int nguyen = int(n);
	float thapPhan = n - nguyen;

	while (soTP > 0){ //soTP=2 -> lay 2 chu so TP
		thapPhan = thapPhan * 10;
		soTP--;
	}

	int tempTP = thapPhan;
	while (tempTP > 0){
		a = tempTP % 10;
		str.insert(str.begin() + 0, convertIntToChar(a)); //them phan TP vao str
		tempTP = tempTP / 10;
	}

	str.insert(str.begin() + 0, '.'); //them . phia truoc phan TP

	if (nguyen == 0)
	{
		str.insert(str.begin() + 0, '0');
	}
	while (nguyen > 0)
	{
		a = nguyen % 10;
		str.insert(str.begin() + 0, convertIntToChar(a));
		nguyen = nguyen / 10;
	}
	return str;
}
void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}
string ftos(float n, int soTP)
{
	char res[20];
	int ipart = (int)n;

	float fpart = n - (float)ipart;

	int i = intToStr(ipart, res, 0);

	if (soTP != 0) {
		res[i] = '.';

		fpart = fpart * pow(10, soTP);

		intToStr((int)fpart, res + i + 1, soTP);
	}

	return res;
}
string xuLyNhapMa()
{
	string input;
	showCur(1);
	gotoXY(whereX(), whereY());
	while (true)
	{
		char c = getch();
		if ((c >= 48 && c <= 57) || c == '_' || (c >= 65 && c <= 90) && input.length()<6)
		{
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c >= 97 && c <= 122)
		{
			c = c - 32;
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c == 8 && input.length() > 0)
		{
			input.erase(input.begin() + input.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 27)
		{
			input.clear();
			showCur(0);
			return input;
		}
		else if (c == 13 && input.length() > 0)
		{
			showCur(0);
			return input;
		}
	}
}

int xuLyNhapSo()
{
	int n;
	showCur(1);
	gotoXY(whereX(), whereY());
	string x="";
	char c;
	while (true)
	{
		c = getch();
		if ((c >= 48 && c <= 57))
		{
			x.insert(x.begin() + x.length(), c);
			cout << c;
		}
		else if (c == 8 && x.length()>0)
		{
			x.erase(x.begin() + x.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 27)
		{
			showCur(0);
			return -1;
		}
		else if (c == 13 && x.length() > 0)
		{
		
			n = atoi(x.c_str());
			showCur(0);
			return n;
		}
		
	}
}

void xuLyNhapMa(string& input, int toadoX, int& toadoY,int lenghtMax=48)
{
	char c;
	showCur(1);
	while (true)
	{
		c = getch();
		if (((c >= 48 && c <= 57) || (c >= 65 && c <= 90)) && input.length() < lenghtMax)
		{
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if ((c >= 97 && c <= 122) && input.length() < lenghtMax)
		{
			c = c - 32;
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c == 8 && input.length()>0)
		{
			input.erase(input.begin() + input.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 13 && input.length() > 0)
		{
			toadoY = toadoY + 3;
			showCur(0);
			return;
		}
		else if (c == -32)
		{
			c = getch();
			if (c == 80)
			{
				toadoY = toadoY + 3;
				showCur(0);
				return;
			}
			else if (c == 72)
			{
				toadoY = toadoY - 3;
				showCur(0);
				return;
			}
		}
	}
}
void xuLyNhapSo(int& n, int toadoX, int& toadoY,int lenghtMax = 48)
{
	string x;
	x = convertIntToString(n);
	char c;
	showCur(1);
	while (true)
	{
		c = getch();
		if (c >= 48 && c <= 57 && x.length()<lenghtMax)
		{
			x.insert(x.begin() + x.length(), c);
			cout << c;
		}
		else if (c == 8 && x.length()>0)
		{
			x.erase(x.begin() + x.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 13 && x.length() > 0)// nếu là phím enter
		{
			toadoY = toadoY + 3;
			n = atoi(x.c_str());
			showCur(0);
			return;
		}
		else if (c == -32)
		{
			c = getch();
			
			if (c == 80)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					n = atoi(x.c_str());
				}
				toadoY = toadoY + 3;
				showCur(0);
				return;
			}
			else if (c == 72)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					n = atoi(x.c_str());
				}
				toadoY = toadoY - 3;
				showCur(0);
				return;
			}
		}
	}
}
void xuLyNhapNienKhoa(int& n, int toadoX, int& toadoY)
{
	string x;
	x = convertIntToString(n);
	char c;
	bool kt = false;
	showCur(1);
	while (true)
	{
		if (x.length() == 4)
		{
			n = atoi(x.c_str());
			x += "-" + convertIntToString(n+1);
			gotoXY(toadoX, toadoY+1);
			cout << x;
			kt = true;
		}

		c = getch();
		if (c >= 48 && c <= 57 &&x.length()<9)
		{
			x.insert(x.begin() + x.length(), c);
			cout << c;
		}
		else if (c == 8 && x.length() > 0)
		{
			if (x.length() == 9)
			{
				x.erase(3,9);
				gotoXY(toadoX, toadoY+1);
				cout << "         ";
				gotoXY(toadoX, toadoY + 1);
				cout << x;
			}
			else
			{
				x.erase(x.begin() + x.length() - 1);
				cout << "\b";
				cout << " ";
				cout << "\b";
			}
		}
		else if (c == 13 && x.length() > 0 && kt)
		{
			toadoY = toadoY + 3;
			showCur(0);
			return;
		}
		else if (c == -32)
		{
			c = getch();

			if (c == 80)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					n = atoi(x.c_str());
				}
				toadoY = toadoY + 3;
				showCur(0);
				return;
			}
			else if (c == 72)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					n = atoi(x.c_str());
				}
				toadoY = toadoY - 3;
				showCur(0);
				return;
			}
		}
	}
}
void xuLyNhapChu(string& input, int toadoX, int& toadoY, int lenghtMax=48)
{
	char c;
	showCur(1);
	while (true)
	{
		char c = _getch();
		if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122) ) && input.length() < lenghtMax)
		{
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c == 8 && input.length()>0)
		{
			input.erase(input.begin() + input.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 32 && input.length() < lenghtMax && input.length() != 0 && input[input.length()-2] != ' ')
		{
			input.insert(input.begin() + input.length(), ' ');
			cout << c;
		}
		else if (c == 13 && input.length() > 0)// nếu là phím enter
		{
			toadoY = toadoY + 3;
			showCur(0);
			return;
		}
		else if (c == -32)
		{
			c = getch();
			if (c == 80)
			{
				toadoY = toadoY + 3;
				showCur(0);
				return;
			}
			else if (c == 72)
			{
				toadoY = toadoY - 3;
				showCur(0);
				return;
			}
		}
	}
}
void xuLyNhapTenMonHoc(string& input, int toadoX, int& toadoY, int lenghtMax = 48)
{
	char c;
	showCur(1);
	while (true)
	{
		char c = _getch();
		if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57)) && input.length() < lenghtMax)
		{
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c == 8 && input.length() > 0)
		{
			input.erase(input.begin() + input.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 32 && input.length() < lenghtMax && input.length() != 0 && input[input.length() - 2] != ' ')
		{
			input.insert(input.begin() + input.length(), ' ');
			cout << c;
		}
		else if (c == 13 && input.length() > 0)
		{
			toadoY = toadoY + 3;
			showCur(0);
			return;
		}
		else if (c == -32)
		{
			c = getch();
			if (c == 80)
			{
				toadoY = toadoY + 3;
				showCur(0);
				return;
			}
			else if (c == 72)
			{
				toadoY = toadoY - 3;
				showCur(0);
				return;
			}
		}
	}
}
bool xuLyNhapDiem(float& n, int toadoX, int& toadoY)
{
	string x = floatToStr(n,2);
	if (n == -1)
	{
		x = "";
	}
	else if (n == 0)
	{
		x = "0.00";
	}
	else if (n == 10)
	{
		x = "10.0";
	}

	showCur(1);
	char c;
	while (true)
	{
		c = getch();
		if (((c >= 48 && c <= 57) || c == 46) && x.length() < 4 && x.substr(0,2) != "10") //substr lay 2 ki tu tu 0
		{
			if (x.length() == 1)
			{
				if ((x == "1" && c == 48) || c == 46)// 1&&0 or .
				{
					x.insert(x.begin() + x.length(), c);
					cout << c;
				}
			}
			else {
				x.insert(x.begin() + x.length(), c);
				cout << c;
			}
		}
		else if (c == 8 && x.length() > 0) 
		{
			x.erase(x.begin() + x.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 13 && x.length() > 0)
		{
			toadoY = toadoY + 2;

			if (x.length() == 2 && x[1] == '.')
			{
				x += '0';
			}
			n = atof(x.c_str());
			
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if (c == 80)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					if (x.length() == 2 && x[1] == '.')
					{
						x += '0';
					}
					n = atof(x.c_str());
				}
				
				toadoY = toadoY + 2;
				break;
			}
			else if (c == 72)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					if (x.length() == 2 && x[1] == '.')
					{
						x += '0';
					}
					n = atof(x.c_str());
				}
				
				toadoY = toadoY - 2;
				break;
			}
		}
		else if (c == 27 )
		{
			if (x.empty())
			{
				n = 0;
			}
			else
			{
				if (x.length() == 2 && x[1] == '.')
				{
					x += '0';
				}
				n = atof(x.c_str());
			}
			showCur(0);
			return false;
		}
	}
	showCur(0);
	return true;
}
void xuLyNhapFloat(string &x, int toadoX, int& toadoY)
{
	showCur(1);
	char c;
	while (true)
	{
		c = getch();
		if (((c >= 48 && c <= 57) || c == 46) && x.length() < 4 )
		{
			if (c == 46 && x[x.length() - 1] == '.')
			{
				
			}
			else
			{
				x.insert(x.begin() + x.length(), c);
				cout << c;
			}	
		}
		else if (c == 8 && x.length() > 0)
		{
			x.erase(x.begin() + x.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
			
		}
		else if (c == 13 && x.length() > 0)
		{
			toadoY = toadoY + 3;
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if (c == 80)
			{
				toadoY = toadoY + 3;
				break;
			}
			else if (c == 72)
			{
				toadoY = toadoY - 3;
				break;
			}
		}
	}
	showCur(0);
}

string getTrangThaiGioiTinh(int phai)
{
	if (phai == 1)
	{
		return "Nam";
	}
	return "Nu";
}
string getNienKhoa(int nienKhoa)
{
	return convertIntToString(nienKhoa) + "-" + convertIntToString(nienKhoa + 1);
}
void xoaManHinhTuyChon(int toadoX, int toadoY, int chieudai, int chieucao)
{
	textcolor(240);
	for (int i = toadoY; i < chieucao + toadoY; i++)
	{
		for (int j = toadoX; j < toadoX + chieudai; j++)
		{
			gotoXY(j, i);
			cout << " ";
		}
	}
}
bool checkHocKi(int hocKi)
{
	if (hocKi != 1 && hocKi != 2 && hocKi != 3)
	{
		return false;
	}
	return true;
}
bool checkPhai(int phai)
{
	if (phai != 1 && phai!=2)
	{
		return false;
	}
	return true;
}
bool checkNienKhoa(int nienKhoa)
{
	if (nienKhoa > 2000 && nienKhoa < 2021)
	{
		return true;
	}
	return false;
}

void tachLayTenVaHo(string str, string &ten, string &ho)
{
	int k = 0;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
		{
			k = i;
			break;
		}
	}

	for (int i = 0; i < k; i++)
	{
		ho += str[i];
	}

	for (int i = k+1; i < str.length(); i++)
	{
		ten += str[i];
	}
}
