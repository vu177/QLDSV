#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include"Menu.h"

void fileRandom(){
	ofstream fileOut;
	fileOut.open("RanDom.txt", ios::out);

	int count = 10000;
	const int maxNum = 32000;
	bool a[maxNum]{ false };

	int i = 0, value;
	fileOut << count<<endl;
	while (i < count)
	{
		value= rand() % (maxNum + 1);
		if (!a[value])
		{
			a[value] = true;
			fileOut << value << " ";
			i++;
		}
	}
	fileOut.close();
}

int main(){
	//fileRandom();
	DsLopTC dsLTC;
	DsSinhVien dsSV;
	DsMonHoc dsMH;

	init(dsLTC, dsSV, dsMH);

	while (true){
		run(dsLTC,dsSV,dsMH);
	}
	return 0;
}
