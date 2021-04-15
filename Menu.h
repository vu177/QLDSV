#include"KhaiBao.h"
#include"mylib.h"
#include"XuLyNhap.h"
#include"Data.h"
#include"DocGhiFile.h"
#include"XuLy.h"

string menuMain[] = {
	" 1. THEM LOP TIN CHI        ",
	" 2. XOA LOP TIN CHI         ",
	" 3. SUA LOP TIN CHI         ",
	" 4. IN DS SINH VIEN DANG KY ",
	" 5. THEM SINH VIEN          ",
	" 6. XOA SINH VIEN           ",
	" 7. SUA SINH VIEN           ",
	" 8. IN DANH SACH SINH VIEN  ",
	" 9. THEM MON HOC            ",
	" 10.XOA MON HOC             ",
	" 11.SUA MON HOC             ",
	" 12.IN DANH SACH MON HOC    ",
	" 13.DANG KY LOP TIN CHI     ",
	" 14.NHAP DIEM SINH VIEN     ",
	" 15.IN BANG DIEM MON HOC    ",
	" 16.KET THUC CHUONG TRINH   "
};


void menu(){
	textcolor(240);
	int j = 17;
	for (int i = 0; i < sizeof(menuMain) / sizeof(*menuMain); i++)
	{
		gotoXY(70, j++);
		cout << menuMain[i];
	}
}

void run(DsLopTC& dsLTC,DsSinhVien &dsSV,DsMonHoc &dsMH){
	if (kbhit()) {
		char c = getch();
		if (c == -32){
			c = getch();
			if (c == 72) 
			{
				if (pointer == 17){
					menu();
					pointer = 17 - 1 + sizeof(menuMain) / sizeof(*menuMain);
				}
				else{
					menu();
					pointer--;
				}
			}
			else if (c == 80) 
			{
				if (pointer == 17 - 1 + sizeof(menuMain) / sizeof(*menuMain)){
					menu();
					pointer = 17;
				}
				else{
					menu();
					pointer++;
				}
			}
		}
		else if (c == 13){
			system("cls");
			system("color F0");

			switch (pointer){
			case 17: 
				themLopTC(dsLTC,dsMH, 70, 17);
				break;
				
			case 18: 
				xoaLopTC(dsLTC,dsMH, 70, 17);
				break;
				
			case 19:
				sualopTC(dsLTC,dsMH, 70, 17);
				break ;
			
			case 20:
				inDSSVDK(dsLTC,dsSV,dsMH, 70, 17);
				break;
			
			case 21:
				themSinhVien(dsSV, 70, 17);
				break;
			
			case 22:
				xoaSinhVien(dsSV, dsLTC, 65, 17);
				break;
			
			case 23:
				suaSinhVien(dsSV, 70, 17);
				break;
			
			case 24:
				inDSSVTheoLop(dsSV, 55, 17);
				break;
			
			case 25:
				themMonHoc(dsMH, 70, 17);
				break;
			
			case 26:
				xoaMonHoc(dsMH, dsLTC, 65, 17);
				break;
			
			case 27:
				suaMonHoc(dsMH, 70, 17);
				break;
			
			case 28:
				inDSMH(dsMH, 35, 7);
				break;
			
			case 29:
				dangKiMonHoc(dsSV, dsLTC, dsMH, 55, 17);
				break;
			
			case 30:
				nhapDiem(dsSV, dsLTC, dsMH, 70, 17);
				break;
			
			case 31:
				inBangDiemCuaLopTC(dsSV, dsLTC, dsMH, 70, 17);
				break;
			
			case 32:
				deleteMemorySV(dsSV);
				deleteMemoryMonHoc(dsMH);
				deleteMemoryLopTC(dsLTC);
				exit(0);
			}

			system("cls");
			system("color F0");
			giaoDienMain();
			menu();
		}
	}

	// to mau 
	textcolor(180);
	gotoXY(70, pointer);
	cout << menuMain[pointer - 17];
	textcolor(7);
}

void init(DsLopTC &dsLTC,DsSinhVien &dsSV,DsMonHoc &dsMH){
	system("mode 650");
	system("color F0");

	loadDSSoRanDom();
	loadDSSV(dsSV);
	loadDSMH(dsMH);
	loadDSLTC(dsLTC);
	

	showCur(0);
	giaoDienMain();
	menu();
}

