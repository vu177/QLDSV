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
#include "mylib.h"
#include "Data.h"
#include "KhaiBao.h"
#include "XuLyNhap.h"
#include "DocGhiFile.h"

//====== Xu Ly LTC ======
void xuatDSLTC(DsMonHoc dsMH, NodeLopTC* root, int toadoX, int &toadoY){
	if (root == NULL){
		return;
	}
	xuatDSLTC(dsMH, root->pLeft, toadoX, toadoY);

	gotoXY(toadoX, toadoY);
	cout << root->data.maLopTC;
	gotoXY(toadoX + 10, toadoY);
	cout << getTenMonHoc(dsMH, root->data.maMH);
	gotoXY(toadoX + 45, toadoY);
	cout << getNienKhoa(root->data.nienKhoa);
	gotoXY(toadoX + 60, toadoY);
	cout << root->data.hocKy;
	gotoXY(toadoX + 67, toadoY);
	cout << root->data.nhom;
	toadoY++;

	xuatDSLTC(dsMH, root->pRight, toadoX, toadoY);
}
void xuatDSDKLTC(DsSinhVien dsSV, NodeSinhVienDK* pHead,int toadoX,int toadoY)
{
	for (NodeSinhVienDK* k = pHead; k != NULL; k = k->pNext)
	{
		gotoXY(toadoX, toadoY);
		cout << k->data.masv;
		gotoXY(toadoX + 20, toadoY);
		NodeSinhVien *nodeSV= getNodeSinhVien(dsSV, k->data.masv);
		cout << nodeSV->data.ho + " " + nodeSV->data.ten;
		toadoY++;
	}
	getch();
}
void xuatMH(DsMonHoc dsMH, int toadoX, int toadoY){
	for (int i = 0; i < dsMH.soLuong; i++)	{
		gotoXY(toadoX + 1, toadoY + 4 + i * 2);
		cout << dsMH.nodeMH[i]->maMH;
		gotoXY(toadoX + 11, toadoY + 4 + i * 2);
		cout << dsMH.nodeMH[i]->tenMH;
	}
}
void themLopTC(DsLopTC& dsLTC, DsMonHoc dsMH, int toadoX, int toadoY){
	LopTC lopTC;
	lopTC.maLopTC = mangRanDom[soLgSoConLai - 1];
	lopTC.hocKy = 0;
	lopTC.nienKhoa = 0;
	lopTC.sosvMax = 0;
	lopTC.sosvMin = 0;
	lopTC.nhom = 0;

	int pointer1 = toadoY;
	giaoDienThemLopTC(toadoX, toadoY);
	xuatMH(dsMH,5,toadoY);
	gotoXY(toadoX + 10, toadoY - 2);
	cout << lopTC.maLopTC;

	while (true)
	{
		if (pointer1 == toadoY)
		{
			gotoXY(toadoX + 2 + lopTC.maMH.length(), pointer1 + 1);
			xuLyNhapMa(lopTC.maMH, toadoX + 2, pointer1);
			if (pointer1 < toadoY)
			{
				pointer1 = toadoY;
			}
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + countNumInt(lopTC.nienKhoa), pointer1 + 1);
			xuLyNhapNienKhoa(lopTC.nienKhoa, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + countNumInt(lopTC.hocKy), pointer1 + 1);
			xuLyNhapSo(lopTC.hocKy, toadoX + 2, pointer1,1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + countNumInt(lopTC.nhom), pointer1 + 1);
			xuLyNhapSo(lopTC.nhom, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 12)
		{
			gotoXY(toadoX + 2 + countNumInt(lopTC.sosvMax), pointer1 + 1);
			xuLyNhapSo(lopTC.sosvMax, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 15)
		{
			gotoXY(toadoX + 2 + countNumInt(lopTC.sosvMin), pointer1 + 1);
			xuLyNhapSo(lopTC.sosvMin, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 18)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true)
			{
				if (kbhit())
				{
					char c = getch();
					if (c == 13)
					{
						MonHoc* nodeMH = getNodeMonHoc(dsMH, lopTC.maMH);
						NodeLopTC* nodeLTC = NULL;
						getNodeLopTCTheoNKHK(dsLTC.root, nodeLTC, lopTC.hocKy, lopTC.nhom, lopTC.nienKhoa, lopTC.maMH);
						if (pointer2 == toadoX + 15
							&& (!lopTC.maMH.empty() && lopTC.nhom > 0
								&& lopTC.sosvMin > 0 && lopTC.sosvMin < lopTC.sosvMax
								&& checkHocKi(lopTC.hocKy)
								&& checkNienKhoa(lopTC.nienKhoa)
								&& nodeMH != NULL
								&& nodeLTC == NULL)
							)
						{
							xuLyThemLopTC(dsLTC.root, lopTC);
							nodeMH->check++;
							dsLTC.soLg++;
							soLgSoConLai--;
							saveDSSoRanDom();
							saveMonHoc(dsMH);
							saveLopTC(dsLTC);
							giaoDienThongBao("Them Thanh Cong      ");
							return;
						}
						else if (pointer2 == toadoX + 30)
						{
							return;
						}
						else
						{
							gotoXY(75, 41);
							if (nodeMH == NULL)
							{
								cout << "Mon Hoc Khong Ton Tai           ";
							}
							else if (lopTC.sosvMin >= lopTC.sosvMax)
							{
								cout << "So SV Max Khong Hop Le          ";
							}
							else if (!checkNienKhoa(lopTC.nienKhoa))
							{
								cout << "Nien Khoa Khong Hop Le          ";
							}
							else if (!checkHocKi(lopTC.hocKy))
							{
								cout << "Hoc Ki Khong Hop Le             ";
							}
							else if (nodeLTC != NULL)
							{
								cout << "Lop Tin Chi Da Ton Tai";
							}
							else
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 20);
				if (pointer2 == toadoX + 15){
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 20);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30){
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 20);
					cout << "Xac Nhan";
				}
			}
		}
	}
}
void xuatDSSVDkTheoLop(DsSinhVien dsSV, NodeSinhVienDK* pHead,int toadoX,int toadoY)
{
	for (NodeSinhVienDK* k = pHead; k != NULL; k = k->pNext)
	{
		gotoXY(toadoX, toadoY);
		cout << k->data.masv;
		gotoXY(toadoX + 20, toadoY);
		NodeSinhVien *nodeSV= getNodeSinhVien(dsSV, k->data.masv);
		cout << nodeSV->data.ho + " " + nodeSV->data.ten;
		toadoY++;
	}
	getch();
}
void xoaLopTC(DsLopTC& dsLTC, DsMonHoc dsMH, int toadoX, int toadoY){
	int maLopTC = 0;
	NodeLopTC* nodeLopTC = NULL;
	MonHoc* nodeMH = NULL;
	do{
		giaoDienLTC();
		gotoXY(50 , 15); cout<<"MA LTC";
		gotoXY(65 , 15); cout<<"TEN MON HOC";
		gotoXY(95 , 15); cout<<"NIEN KHOA";
		gotoXY(108 , 15); cout<<"HOCKY";
		gotoXY(115 , 15); cout<<"NHOM";
		int toadoYTemp = 17;
		xuatDSLTC(dsMH, dsLTC.root, 50, toadoYTemp);
		gotoXY(toadoX, toadoY+19); cout<<"ESC: Thoat";
		gotoXY(toadoX-5, toadoY+18);
		textcolor(242);
		cout << "Nhap Ma Lop Tin Chi Muon Xoa: ";
		maLopTC = xuLyNhapSo();
		if (maLopTC == -1){
			return;
		}
		nodeLopTC = getNodeLopTC(dsLTC.root, maLopTC);
		nodeMH = getNodeMonHoc(dsMH, nodeLopTC->data.maMH);
		if (nodeLopTC == NULL){
			giaoDienThongBao("Ma Lop Tin Chi Khong Ton Tai");
			system("cls");
			system("color F0");
		}
		else if (nodeLopTC != NULL  && nodeLopTC->data.dsSVDK.pHead != NULL){
			int toadoYTemp = 30;
			gotoXY(160, 25);
			cout << "DS SV Da DK Lop Tin Chi";
			xuatDSSVDkTheoLop(dsSV, nodeLopTC->data.dsSVDK.pHead, 150, toadoYTemp);
			giaoDienThongBao("Lop Tin Chi Nay Khong Duoc Xoa");
			system("cls");
			system("color F0");
		}
	} while (nodeLopTC == NULL || nodeLopTC->data.dsSVDK.pHead != NULL);

	xuLyXoaLopTC(dsLTC.root, maLopTC);
	nodeMH->check--;
	dsLTC.soLg--;
	saveMonHoc(dsMH);
	saveLopTC(dsLTC);
	giaoDienThongBao("Xoa Thanh Cong");
}

void sualopTC(DsLopTC& dsLTC, DsMonHoc dsMH, int toadoX, int toadoY){
	int maLopTC = 0;
	NodeLopTC* nodeLTC = NULL;
	do{
		giaoDienLTC();
		gotoXY(50 , 15); cout<<"MA LTC";
		gotoXY(65 , 15); cout<<"TEN MON HOC";
		gotoXY(95 , 15); cout<<"NIEN KHOA";
		gotoXY(108 , 15); cout<<"HOCKY";
		gotoXY(115 , 15); cout<<"NHOM";
		int toadoYTemp = 17;
		xuatDSLTC(dsMH, dsLTC.root, 50, toadoYTemp);
		gotoXY(toadoX, toadoY+20); cout<<"ESC: Thoat";
		gotoXY(toadoX-5, toadoY+18);
		textcolor(242);
		cout << "Nhap Ma Lop Tin Chi Muon Sua: ";
		maLopTC = xuLyNhapSo();
		if (maLopTC == -1)		{
			return;
		}

		nodeLTC = getNodeLopTC(dsLTC.root, maLopTC);
		if (nodeLTC == NULL){
			giaoDienThongBao("Ma Lop Tin Chi Khong Ton Tai");
			system("cls");
			system("color F0");
		}
	} while (nodeLTC == NULL);

	LopTC lopTC = nodeLTC->data;
	int pointer1 = toadoY+12;

	system("cls");
	system("color F0");
	textcolor(240);

	giaoDienThemLopTC(toadoX, toadoY);
	gotoXY(toadoX + 2, toadoY - 2);
	cout << lopTC.maLopTC;
	gotoXY(toadoX + 2, toadoY + 1);
	cout << lopTC.maMH;
	gotoXY(toadoX + 2, toadoY + 4);
	cout << getNienKhoa(lopTC.nienKhoa);
	gotoXY(toadoX + 2, toadoY + 7);
	cout << lopTC.hocKy;
	gotoXY(toadoX + 2, toadoY + 10);
	cout << lopTC.nhom;
	gotoXY(toadoX + 2, toadoY + 13);
	cout << lopTC.sosvMax;
	gotoXY(toadoX + 2, toadoY + 16);
	cout << lopTC.sosvMin;

	while (true){
		if (pointer1 == toadoY + 12){
			gotoXY(toadoX + 2 + countNumInt(lopTC.sosvMax), pointer1 + 1);
			xuLyNhapSo(lopTC.sosvMax, toadoX + 2, pointer1);
			if (pointer1 < toadoY + 12){
				pointer1 = toadoY + 12;
			}
		}
		else if (pointer1 == toadoY + 15){
			gotoXY(toadoX + 2 + countNumInt(lopTC.sosvMin), pointer1 + 1);
			xuLyNhapSo(lopTC.sosvMin, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 18){
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true){
				if (kbhit()){
					char c = getch();
					if (c == 13)
					{
						if (pointer2 == toadoX + 15 && lopTC.sosvMin > 0 && lopTC.sosvMin < lopTC.sosvMax)
						{
							nodeLTC->data = lopTC;
							saveLopTC(dsLTC);
							giaoDienThongBao("Sua Thanh Cong");
							return;
						}
						else if (pointer2 == toadoX + 30)
						{
							return;
						}
						else
						{
							gotoXY(75, 41);
							if (lopTC.sosvMin >= lopTC.sosvMax)
							{
								cout << "So SV Max Khong Hop Le          ";
							}
							else
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 20);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 20);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 20);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

// ======= In DSSVDK Lop tin chi ======= b
void xuatDSSVDK(NodeLopTC* lopTC, DsSinhVien dsSV, int toadoX, int toadoY)
{
	system("cls");
	gotoXY(55,10); cout<<"<<<<<<<<<< DANH SACH SINH VIEN LOP TIN CHI >>>>>>>>>>";
	int count = 0;
	for (NodeSinhVienDK* k = lopTC->data.dsSVDK.pHead; k != NULL; k = k->pNext)
	{
		NodeSinhVien* temp = getNodeSinhVien(dsSV, k->data.masv);
		if (temp == NULL)
		{
			continue;
		}

		gotoXY(toadoX + 1, toadoY + 4 + (count * 2));
		cout << lopTC->data.maLopTC;
		gotoXY(toadoX + 11, toadoY + 4 + (count * 2));
		cout << temp->data.maLop;
		gotoXY(toadoX + 31, toadoY + 4 + (count * 2));
		cout << temp->data.maSV;
		gotoXY(toadoX + 51, toadoY + 4 + (count * 2));
		cout << temp->data.ho + " " + temp->data.ten;
		gotoXY(toadoX + 81, toadoY + 4 + (count * 2));
		cout << getTrangThaiGioiTinh(temp->data.phai);
		gotoXY(toadoX + 86, toadoY + 4 + (count * 2));
		cout << temp->data.sdt;
		count++;
	}

	giaoDienInDSLopTC(toadoX, toadoY, count);
	getch();
}
void inDSSVDK(DsLopTC dsLopTC, DsSinhVien dsSV, DsMonHoc dsMH, int toadoX, int toadoY)
{
	int pointer1 = toadoY;
	int nienKhoa = 0;
	int hocKi = 0;
	int nhom = 0;
	string maMH="";
	NodeLopTC* nodeLopTC = NULL;
	giaoDienChonLopTC(toadoX, toadoY);

	while (true)
	{
		if (pointer1 == toadoY)
		{
			if (countNumInt(nienKhoa) == 4)
			{
				gotoXY(toadoX + 2 + 9, pointer1 + 1);
			}
			else
				gotoXY(toadoX + 2 + countNumInt(nienKhoa), pointer1 + 1);
			xuLyNhapNienKhoa(nienKhoa, toadoX + 2, pointer1);
			if (pointer1 < toadoY)
			{
				pointer1 = toadoY + 9;
			}
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + countNumInt(hocKi), pointer1 + 1);
			xuLyNhapSo(hocKi, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + countNumInt(nhom), pointer1 + 1);
			xuLyNhapSo(nhom, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + maMH.length(), pointer1 + 1);
			xuLyNhapMa(maMH, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 12)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true)
			{
				if (kbhit())
				{
					char c = getch();
					if (c == 13)
					{
						getNodeLopTCTheoNKHK(dsLopTC.root, nodeLopTC, hocKi, nhom, nienKhoa, maMH);
						if (pointer2 == toadoX + 15
							&& checkNienKhoa(nienKhoa)
							&& checkHocKi(hocKi)
							&& nhom > 0
							&& getNodeMonHoc(dsMH, maMH) != NULL
							&& nodeLopTC != NULL
							)
						{
							xuatDSSVDK(nodeLopTC, dsSV, 35, 12);
							system("cls");
							system("color F0");
							pointer1 = toadoY;
							nienKhoa = 0;
							hocKi = 0;
							nhom = 0;
							maMH = "";
							giaoDienChonLopTC(toadoX, toadoY);
							break;

						}
						else if (pointer2 == toadoX + 30)
						{
							return;
						}
						else
						{
							gotoXY(75, 41);
							if (!checkNienKhoa(nienKhoa))
							{
								cout << "Nien Khoa Khong Hop Le        ";
							}
							else if (!checkHocKi(hocKi))
							{
								cout << "Hoc Ki Khong Hop Le           ";
							}
							else if (nhom < 0)
							{
								cout << "Nhom Khong Hop Le             ";
							}
							else if (getNodeMonHoc(dsMH, maMH) == NULL)
							{
								cout << "Ma Mon Hoc Khong Ton Tai      ";
							}
							else if (nodeLopTC == NULL)
							{
								cout << "Lop Khong Ton Tai             ";
							}
							else
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 15);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 15);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 15);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

// ======== Xu ly Sinh Vien ========
void themSinhVien(DsSinhVien &dsSV, int toadoX, int toadoY){
	int pointer1 = toadoY - 3;
	giaoDienThemSinhVien(toadoX, toadoY);
	SinhVien sv;
	sv.phai = 1;
	string maLop;
	gotoXY(toadoX + 2, 27);
	cout << sv.phai;

	while (true){
		if (pointer1 == toadoY - 3){
			gotoXY(toadoX + 2 + maLop.length(), pointer1 + 1);
			xuLyNhapMa(maLop, toadoX + 2, pointer1,15);
			if (pointer1 < toadoY - 3)
			{
				pointer1 = toadoY + 15;
			}
		}
		else if (pointer1 == toadoY){
			gotoXY(toadoX + 2 + sv.maSV.length(), pointer1 + 1);
			xuLyNhapMa(sv.maSV, toadoX + 2, pointer1,12);
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + sv.ho.length(), pointer1 + 1);
			xuLyNhapChu(sv.ho, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + sv.ten.length(), pointer1 + 1);
			xuLyNhapChu(sv.ten, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + 1, pointer1 + 1);
			xuLyNhapSo(sv.phai, toadoX + 2, pointer1,1);
		}
		else if (pointer1 == toadoY + 12)
		{
			gotoXY(toadoX + 2 + sv.sdt.length(), pointer1 + 1);
			xuLyNhapMa(sv.sdt, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 15)
		{
			gotoXY(toadoX + 2 + countNumInt(sv.namNhapHoc), pointer1 + 1);
			xuLyNhapSo(sv.namNhapHoc, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 18)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true){
				if (kbhit()){
					char c = getch();
					if (c == 13){
						NodeSinhVien* nodeSV = getNodeSinhVien(dsSV, sv.maSV);
						if (pointer2 == toadoX + 15
							&& (!maLop.empty() && !sv.maSV.empty()
								&& !sv.ho.empty()
								&& !sv.ten.empty()
								&& !sv.sdt.empty()
								&& checkPhai(sv.phai)
								&& sv.namNhapHoc > 2000 && sv.namNhapHoc < 2021
								&& nodeSV == NULL)
							)
						{
							formatString(sv.ho);
							formatString(sv.ten);
							sv.maLop = maLop;
							xuLyThemSVTheoThuTu(dsSV, sv);
							saveSinhVien(dsSV);
							giaoDienThongBao("Them Thanh Cong");
							system("cls");
							system("color F0");
							giaoDienThemSinhVien(toadoX, toadoY);
							pointer1 = toadoY;
							gotoXY(toadoX + 2, toadoY);
							sv.ho = "";
							sv.sdt = "";
							sv.ten = "";
							sv.maSV = "";
							sv.namNhapHoc = 0;
							sv.phai = 1;
							gotoXY(toadoX + 2, toadoY - 2);
							cout << maLop;
							gotoXY(toadoX + 2, 27);
							cout << sv.phai;
							break;
						}
						else if (pointer2 == toadoX + 30){
							return;
						}
						else{
							gotoXY(75, 41);
							if (nodeSV != NULL)
							{
								cout << "Ma SV Da Ton Tai              ";
							}
							else if (!checkPhai(sv.phai))
							{
								cout << "Phai Khong Hop Le             ";
							}
							else if (sv.namNhapHoc < 2000 || sv.namNhapHoc > 2021)
							{
								cout << "Nam Nhap Hoc Khong Hop Le      ";
							}
							else
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32){
						c = getch();
						if (c == 72){
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80){
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75){
							if (pointer2 == toadoX + 30){
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77){
							if (pointer2 == toadoX + 15){
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 20);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 20);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 20);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

void xuatDSLopTCTheoSV(NodeLopTC* root, string maSV, int toadoX, int& toadoY)
{
	if (root == NULL){
		return;
	}
	xuatDSLopTCTheoSV(root->pLeft, maSV, toadoX, toadoY);

	for (NodeSinhVienDK* k = root->data.dsSVDK.pHead; k != NULL; k = k->pNext)
	{
		if(k->data.masv==maSV){
			gotoXY(toadoX, toadoY);
			cout << root->data.maLopTC;
			gotoXY(toadoX + 10, toadoY);
			cout << root->data.maMH;
			gotoXY(toadoX + 25, toadoY);
			cout << getNienKhoa(root->data.nienKhoa);
			gotoXY(toadoX + 35, toadoY);
			cout << root->data.nhom;
			gotoXY(toadoX + 40, toadoY);
			cout << root->data.hocKy;
			toadoY++;
		}
	}
	
	xuatDSLopTCTheoSV(root->pRight, maSV, toadoX, toadoY);
}

void xoaSinhVien(DsSinhVien &dsSV, DsLopTC dsLTC, int toadoX, int toadoY){
	string maSV;
	NodeSinhVien* nodeSV = NULL;
	do{
		giaoDienSV();
		gotoXY(toadoX, toadoY+3);
		cout << "ESC: Thoat";
		gotoXY(toadoX-5, toadoY);
		cout << "Nhap Ma Sinh Vien can xoa: ";
		maSV = xuLyNhapMa();
		if (maSV == "")
		{
			return;
		}
		nodeSV = getNodeSinhVien(dsSV, maSV);
		if (nodeSV == NULL)
		{
			giaoDienThongBao("Sinh Vien Khong Ton Tai");
			system("cls");
			system("color F0");
		}
		else if (nodeSV != NULL && nodeSV->data.ktXoa>0)
		{
			int toadoYTemp = 7;
			gotoXY(160, 3);
			cout << "DS Lop Tin Chi Da DK";
			xuatDSLopTCTheoSV(dsLTC.root, nodeSV->data.maSV, 150, toadoYTemp);
			giaoDienThongBao("Sinh Vien Nay Khong Duoc Xoa");
			system("cls");
			system("color F0");
		}
	} while (nodeSV == NULL || nodeSV->data.ktXoa>0);

	xuLyXoaSV(dsSV, maSV);
	saveSinhVien(dsSV);
	giaoDienThongBao("Xoa Thanh Cong");
	return;
}

void suaSinhVien(DsSinhVien &dsSV, int toadoX, int toadoY){
	string maSV;
	NodeSinhVien* temp = NULL;
	do{
		giaoDienSV();
		gotoXY(toadoX - 5, toadoY+3);
		cout << "ESC: Thoat";
		gotoXY(toadoX-10, toadoY);
		cout << "Nhap Ma Sinh Vien can hieu chinh: ";
		maSV = xuLyNhapMa();
		if (maSV == "")
		{
			return;
		}
		temp = getNodeSinhVien(dsSV, maSV);
		if (temp == NULL)
		{
			giaoDienThongBao("Sinh Vien Khong Ton Tai");
			system("cls");
			system("color F0");
		}
	} while (temp == NULL);

	system("cls");
	system("color F0");

	int pointer1 = toadoY + 3;
	giaoDienThemSinhVien(toadoX, toadoY);
	SinhVien sv = temp->data;

	gotoXY(toadoX + 2, toadoY - 2);
	cout << sv.maLop;
	gotoXY(toadoX + 2, toadoY + 1);
	cout << sv.maSV;
	gotoXY(toadoX + 2, toadoY + 4);
	cout << sv.ho;
	gotoXY(toadoX + 2, toadoY + 7);
	cout << sv.ten;
	gotoXY(toadoX + 2, toadoY + 10);
	cout << sv.phai;
	gotoXY(toadoX + 2, toadoY + 13);
	cout << sv.sdt;
	gotoXY(toadoX + 2, toadoY + 16);
	cout << sv.namNhapHoc;

	while (true){
		if (pointer1 == toadoY + 3){
			gotoXY(toadoX + 2 + sv.ho.length(), pointer1 + 1);
			xuLyNhapChu(sv.ho, toadoX + 2, pointer1);
			if (pointer1 < toadoY + 3){
				pointer1 = toadoY + 3;
			}
		}
		else if (pointer1 == toadoY + 6){
			gotoXY(toadoX + 2 + sv.ten.length(), pointer1 + 1);
			xuLyNhapChu(sv.ten, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9){
			gotoXY(toadoX + 2 + 1, pointer1 + 1);
			xuLyNhapSo(sv.phai, toadoX + 2, pointer1,1);
		}
		else if (pointer1 == toadoY + 12){
			gotoXY(toadoX + 2 + sv.sdt.length(), pointer1 + 1);
			xuLyNhapMa(sv.sdt, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 15){
			gotoXY(toadoX + 2 + countNumInt(sv.namNhapHoc), pointer1 + 1);
			xuLyNhapSo(sv.namNhapHoc, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 18){
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true){
				if (kbhit()) {
					char c = getch();
					if (c == 13){
						if (pointer2 == toadoX + 15
							&& (!sv.maLop.empty() && !sv.maSV.empty()
								&& !sv.ho.empty() && !sv.ten.empty()
								&& !sv.sdt.empty() && checkPhai(sv.phai)
								&& sv.namNhapHoc > 2000 && sv.namNhapHoc < 2021)
							)
						{
							formatString(sv.ho);
							formatString(sv.ten);
							temp->data = sv;
							saveSinhVien(dsSV);
							giaoDienThongBao("Sua Thanh Cong");
							return;
						}
						else if (pointer2 == toadoX + 30){
							return;
						}
						else{
							gotoXY(75, 41);
							if (!checkPhai(sv.phai)){
								cout << "Phai Khong Hop Le              ";
							}
							else if (sv.namNhapHoc < 2000 || sv.namNhapHoc > 2021){
								cout << "Nam Nhap Hoc Khong Hop Le      ";
							}
							else{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32){
						c = getch();
						if (c == 72){
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80){
							gotoXY(toadoX + 30, toadoY + 20);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 20);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY + 3;
							break;
						}
						else if (c == 75){
							if (pointer2 == toadoX + 30){
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77){
							if (pointer2 == toadoX + 15){
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 20);
				if (pointer2 == toadoX + 15){
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 20);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30){
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 20);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

// ======== In danh sach sinh vien 1 lop tang dan theo masv
void xuatDSSV(NodeSinhVien* nodeSVDauLop, int toadoX, int toadoY){
	int count = 0;
	string maLop = nodeSVDauLop->data.maLop;
	gotoXY(58,5);
	textcolor(242);
	cout<<"<<<<<<<<<< DANH SACH SINH VIEN THEO LOP >>>>>>>>>>";
	textcolor(240);
	for (NodeSinhVien* k = nodeSVDauLop; k != NULL; k = k->pNext){
		if (maLop != k->data.maLop){
			break;
		}

		gotoXY(toadoX + 1, toadoY + 4 + (count * 2));
		cout << k->data.maSV;
		gotoXY(toadoX + 21, toadoY + 4 + (count * 2));
		cout << k->data.ho + " " + k->data.ten;
		gotoXY(toadoX + 61, toadoY + 4 + (count * 2));
		cout << getTrangThaiGioiTinh(k->data.phai);
		gotoXY(toadoX + 71, toadoY + 4 + (count * 2));
		cout << k->data.sdt;
		gotoXY(toadoX + 81, toadoY + 4 + (count * 2));
		cout << k->data.namNhapHoc;
		count++;
	}
	giaoDienInDSSV(toadoX, toadoY, count);
	getch();
}

void xuatDSLop(NodeSinhVien* head, int X, int Y){
	int count = 0;
	gotoXY(X,Y); textcolor(242);
	cout<<"<<<<< DANH SACH LOP >>>>>";
	textcolor(240);
	
	string maloptemp[100]; 
	maloptemp[count]= head->data.maLop; 
	gotoXY(X+7,Y+2); cout<<maloptemp[count];
	
	for(NodeSinhVien* k = head; k!=NULL; k=k->pNext){ 
		if(maloptemp[count] != k->data.maLop ){
			maloptemp[count+1]=k->data.maLop;
			count++; 
			gotoXY(X+7, Y+2+1*count); 
			cout<<maloptemp[count];
		}
	}
}

void inDSSVTheoLop(DsSinhVien dsSV, int toadoX, int toadoY){
	string maLop;
	NodeSinhVien* temp = NULL;
	do	{
		giaoDienSV();
		xuatDSLop(dsSV.pHead, toadoX+25, toadoY+3);
		gotoXY(toadoX, toadoY+5);
		cout << "ESC: Thoat"; 
		gotoXY(toadoX, toadoY);
		cout << "Nhap Ma Lop can in danh sach sinh vien: ";
		maLop = xuLyNhapMa();
		if (maLop == ""){
			return;
		}
		temp = getSVDauLop(dsSV, maLop);
		if (temp == NULL)
		{
			giaoDienThongBao("Ma Lop Khong Ton Tai");
			system("cls");
			system("color F0");
		}
	} while (temp == NULL);

	system("cls");
	system("color F0");
	xuatDSSV(temp, 35, 7);
}

//=============== Mon Hoc ============
void themMonHoc(DsMonHoc& dsMH, int toadoX, int toadoY)
{
	int pointer1 = toadoY;
	giaoDienThemMonHoc(toadoX, toadoY);

	MonHoc mh;
	string str1="";
	string str2 = "";

	while (true)
	{
		if (pointer1 == toadoY)
		{
			gotoXY(toadoX + 2 + mh.maMH.length(), pointer1 + 1);
			xuLyNhapMa(mh.maMH, toadoX + 2, pointer1,10);
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + mh.tenMH.length(), pointer1 + 1);
			xuLyNhapTenMonHoc(mh.tenMH, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + str1.length(), pointer1 + 1);
			xuLyNhapFloat(str1, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + str2.length(), pointer1 + 1);
			xuLyNhapFloat(str2, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 12)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true){
				if (kbhit()){
					char c = getch();
					if (c == 13){
						mh.stclt = atof(str1.c_str());
						mh.stcth = atof(str2.c_str());
						MonHoc* nodeMonHoc = getNodeMonHoc(dsMH, mh.maMH);
						if (pointer2 == toadoX + 15
							&& (!mh.maMH.empty() && !mh.tenMH.empty()
								&& mh.stclt > -1 && mh.stcth > -1
								&& mh.stclt + mh.stcth > 0
								&& nodeMonHoc == NULL)
							)
						{
							xuLyThemMonHoc(dsMH, mh);
							saveMonHoc(dsMH);
							giaoDienThongBao("Them Thanh Cong");
							return;
						}
						else if (pointer2 == toadoX + 30){
							return;
						}
						else{
							gotoXY(75, 40);
							if (nodeMonHoc != NULL){
								cout << "Mon Hoc Da Ton Tai            ";
							}
							else{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32){
						c = getch();
						if (c == 72){
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80){
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75){
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77){
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 15);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 15);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 15);
					cout << "Xac Nhan";
				}
			}
		}
	}
}
void xuatDSLopTCTheoMon(NodeLopTC* root,string maMH, int toadoX, int& toadoY)
{
	if (root == NULL)
	{
		return;
	}

	xuatDSLopTCTheoMon(root->pLeft, maMH ,toadoX, toadoY);

	if (root->data.maMH == maMH)
	{
		gotoXY(toadoX, toadoY);
		cout << root->data.maLopTC;
		gotoXY(toadoX + 10, toadoY);
		cout << root->data.maMH;
		gotoXY(toadoX + 25, toadoY);
		cout << getNienKhoa(root->data.nienKhoa);
		gotoXY(toadoX + 35, toadoY);
		cout << root->data.nhom;
		gotoXY(toadoX + 40, toadoY);
		cout << root->data.hocKy;
		toadoY++;
	}
	
	xuatDSLopTCTheoMon(root->pRight, maMH, toadoX, toadoY);
}
void xoaMonHoc(DsMonHoc& dsMH, DsLopTC dsLTC, int toadoX, int toadoY){
	string maMH;
	MonHoc* nodeMH = NULL;
	do{
		giaoDienMH();
		gotoXY(toadoX + 5, toadoY+8);
		cout << "ESC: Thoat";
		gotoXY(toadoX, toadoY+5);
		cout << "Nhap Ma Mon Hoc can xoa: ";
		maMH = xuLyNhapMa();
		if (maMH == ""){
			return;
		}
		nodeMH = getNodeMonHoc(dsMH, maMH);
		if (nodeMH == NULL)
		{
			giaoDienThongBao("Mon Hoc Khong Ton Tai");
			system("cls");
			system("color F0");
		}
		else if (nodeMH != NULL && nodeMH->check>0)
		{
			int toadoYTemp = 7;
			gotoXY(160, 3);
			cout << "DS Lop Tin Chi Da DK Mon Nay";
			xuatDSLopTCTheoMon(dsLTC.root, nodeMH->maMH, 150, toadoYTemp);
			giaoDienThongBao("Mon Hoc Nay Khong The Xoa");
			system("cls");
			system("color F0");
		}
	} while (nodeMH == NULL || nodeMH->check>0); //mh k ton tai hoac mh da mo lop

	xuLyXoaMonHoc(dsMH, maMH);
	saveMonHoc(dsMH);
	giaoDienThongBao("Xoa Thanh Cong");
	return;
}

void suaMonHoc(DsMonHoc& dsMH, int toadoX, int toadoY){
	string maMH;
	MonHoc* temp = NULL;
	do{
		giaoDienMH();
		gotoXY(toadoX - 5, toadoY+8);
		cout << "ESC: Thoat";
		gotoXY(toadoX - 10, toadoY+5);
		cout << "Nhap Ma Mon Hoc can hieu chinh: ";
		maMH = xuLyNhapMa();
		if (maMH == "")
		{
			return;
		}
		temp = getNodeMonHoc(dsMH, maMH);
		if (temp == NULL)
		{
			giaoDienThongBao("Mon Hoc Khong Ton Tai");
			system("cls");
			system("color F0");
		}
	} while (temp == NULL);

	system("cls");
	system("color F0");
	giaoDienThemMonHoc(toadoX, toadoY);
	int pointer1 = toadoY + 3;
	MonHoc mh = *temp;
	string str1 = ftos(mh.stclt,2);
	string str2 = ftos(mh.stcth, 2);

	gotoXY(toadoX + 2, toadoY + 1);
	cout << mh.maMH; //temp->maMH
	gotoXY(toadoX + 2, toadoY + 4);
	cout << mh.tenMH;
	gotoXY(toadoX + 2, toadoY + 7);
	cout << str1 ;
	gotoXY(toadoX + 2, toadoY + 10);
	cout << str2 ;

	while (true){
		if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + mh.tenMH.length(), pointer1 + 1);
			xuLyNhapTenMonHoc(mh.tenMH, toadoX + 2, pointer1);
			if (pointer1 < toadoY + 3)
			{
				pointer1 = toadoY + 3;
			}
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + str1.length(), pointer1 + 1);
			xuLyNhapFloat(str1, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + str2.length(), pointer1 + 1);
			xuLyNhapFloat(str2, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 12)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true){
				if (kbhit()){
					char c = getch();
					if (c == 13){
						mh.stclt = atof(str1.c_str());
						mh.stcth = atof(str2.c_str());

						if (pointer2 == toadoX + 15
							&& (!mh.maMH.empty() && !mh.tenMH.empty()
								&& mh.stclt > -1 && mh.stcth > -1
								&& mh.stclt + mh.stcth > 0)
							)
						{
							*temp = mh;
							saveMonHoc(dsMH);
							giaoDienThongBao("Sua Thanh Cong");
							return;
						}
						else if (pointer2 == toadoX + 30)
						{
							return;
						}
						else
						{
							gotoXY(75, 40);
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY + 3;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 15);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 15);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 15);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

void xuatDSMH(DsMonHoc dsMH, int toadoX, int toadoY){
	giaoDienInDSMH(toadoX, toadoY, dsMH.soLuong);
	for (int i = 0; i < dsMH.soLuong; i++)	{
		gotoXY(toadoX + 1, toadoY + 4 + i * 2);
		cout << dsMH.nodeMH[i]->maMH;
		gotoXY(toadoX + 31, toadoY + 4 + i * 2);
		cout << dsMH.nodeMH[i]->tenMH;
		gotoXY(toadoX + 81, toadoY + 4 + i * 2);
		cout << dsMH.nodeMH[i]->stclt;
		gotoXY(toadoX + 91, toadoY + 4 + i * 2);
		cout << dsMH.nodeMH[i]->stcth;
	}
	getch();
}

void inDSMH(DsMonHoc dsMH, int toadoX, int toadoY){
	sapXepMonHoc(dsMH);
	gotoXY(65,5);
	textcolor(242);
	cout<<"<<<<<<<<<< DANH SACH MON HOC >>>>>>>>>>";
	textcolor(240);
	xuatDSMH(dsMH, toadoX, toadoY);
}

//========= Dang Ky Lop Tin Chi ==============
void xuatDSLopTC(NodeLopTC* dsLopTC[], bool ktDKLopTinChi[], DsMonHoc dsMH, int n, int toadoX, int toadoY){
	giaoDienDKLopTinChi(toadoX, toadoY, n);
	for (int i = 0; i < n; i++){
		gotoXY(toadoX + 1, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.maLopTC;
		gotoXY(toadoX + 11, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.maMH;
		gotoXY(toadoX + 21, toadoY + 4 + i * 2);
		cout << getTenMonHoc(dsMH, dsLopTC[i]->data.maMH);
		gotoXY(toadoX + 61, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.nhom;
		gotoXY(toadoX + 71, toadoY + 4 + i * 2);
		cout << getSTCTheoMa(dsMH, dsLopTC[i]->data.maMH);
		gotoXY(toadoX + 81, toadoY + 4 + i * 2);
		cout << getSoLgConLaiLopTC(dsLopTC[i]);
		gotoXY(toadoX + 91, toadoY + 4 + i * 2);
		if (ktDKLopTinChi[i]){
			cout << "X";
		}
	}
}

void xuatDSLopTCDaDK(NodeLopTC* dsLopTC[], DsMonHoc dsMH, int n, int toadoX, int toadoY){
	giaoDienXuatDSLopTCDaDK(toadoX, toadoY, n);
	for (int i = 0; i < n; i++)	{
		gotoXY(toadoX + 1, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.maLopTC;
		gotoXY(toadoX + 11, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.maMH;
		gotoXY(toadoX + 21, toadoY + 4 + i * 2);
		cout << getTenMonHoc(dsMH, dsLopTC[i]->data.maMH);
		gotoXY(toadoX + 61, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.nhom;
		gotoXY(toadoX + 71, toadoY + 4 + i * 2);
		cout << getSTCTheoMa(dsMH, dsLopTC[i]->data.maMH);
		gotoXY(toadoX + 81, toadoY + 4 + i * 2);
		cout << dsLopTC[i]->data.sosvMax;
		gotoXY(toadoX + 91, toadoY + 4 + i * 2);
		cout << getSoLgConLaiLopTC(dsLopTC[i]);
	}
}

void xuatThongTinSV(SinhVien sv, int toadoX, int toadoY){
	gotoXY(toadoX + 5, toadoY);
	cout << "<<<<< Thong Tin Sinh Vien >>>>>";
	toadoY += 3;
	gotoXY(toadoX, toadoY++);
	cout << "Ma Sinh Vien :       " << sv.maSV;
	gotoXY(toadoX, toadoY++);
	cout << "Ho Va Ten Sinh Vien: " << sv.ho + " " + sv.ten;
	gotoXY(toadoX, toadoY++);
	cout << "Phai :               " << getTrangThaiGioiTinh(sv.phai);
	gotoXY(toadoX, toadoY++);
	cout << "SDT :                " << sv.sdt;
	gotoXY(toadoX, toadoY++);
	cout << "Nam Nhap Hoc :       " << sv.namNhapHoc;
	gotoXY(toadoX, toadoY + 3);
	cout << "Vui Long Kiem Tra Thong Tin Sinh Vien";
	gotoXY(toadoX+7, toadoY + 5);
	cout << "ECS: Thoat";
}

void nhapNienKhoaHocKi(int& nienKhoa, int& hocKy, int toadoX, int toadoY){
	int pointer1 = toadoY;
	giaoDienNhapNKHK(toadoX, toadoY);
	while (true)
	{
		if (pointer1 == toadoY)
		{
			if (countNumInt(nienKhoa) == 4)
			{
				gotoXY(toadoX + 2 + 9, pointer1 + 1);
			}
			else
				gotoXY(toadoX + 2 + countNumInt(nienKhoa), pointer1 + 1);
			xuLyNhapNienKhoa(nienKhoa, toadoX + 2, pointer1);
			if (pointer1 < toadoY)
			{
				pointer1 = toadoY;
			}
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + countNumInt(hocKy), pointer1 + 1);
			xuLyNhapSo(hocKy, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true)
			{
				if (kbhit())
				{
					char c = getch();
					if (c == 13)
					{
						if (pointer2 == toadoX + 15
							&& checkHocKi(hocKy)
							&& checkNienKhoa(nienKhoa))
						{
							return;
						}
						else if (pointer2 == toadoX + 30)
						{
							nienKhoa = -1;
							hocKy = -1;
							return;
						}
						else
						{
							gotoXY(75, 40);
							cout << "Vui Long Kiem Tra lai Thong Tin";
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 15);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 15);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 15);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

bool checkMHLopTC(NodeLopTC* dsLopTCDK[], bool ktDKLopTinChi[], int soLg, NodeLopTC* lopTCDK, int k){
	for (int i = 0; i < soLg; i++){ 
		if (i != k && ktDKLopTinChi[i] && dsLopTCDK[i]->data.maMH == lopTCDK->data.maMH){ 
			return false;
		}
	}
	return true;
}

void getDsLopTCTheoHKNK(NodeLopTC* root, NodeLopTC* dsLopTCDK[], int& soLg, int hocKy, int nienKhoa){
	if (root == NULL){
		return;
	}

	if (root->data.nienKhoa == nienKhoa && root->data.hocKy == hocKy){
		if (getSoLgConLaiLopTC(root) == 0){ 
		}
		else
			dsLopTCDK[soLg++] = root;
	}

	getDsLopTCTheoHKNK(root->pLeft, dsLopTCDK, soLg, hocKy, nienKhoa);
	getDsLopTCTheoHKNK(root->pRight, dsLopTCDK, soLg, hocKy, nienKhoa);
}

void getDsLopTCDaDK(NodeLopTC* dsLopTC[], NodeLopTC* dsLopTCDK[], bool ktDKLopTinChi[], int soLgLTC, int& soLgLTCDK){
	for (int i = 0; i < soLgLTC; i++){
		if (ktDKLopTinChi[i]){
			dsLopTCDK[soLgLTCDK++] = dsLopTC[i]; 
		}
	}
}

void checkDsLopTCTheoHKNK(NodeLopTC* dsLTCDK[], bool ktDKLopTinChi[], int& soLg, string maSV){
	for (int i = 0; i < soLg; i++){
		if (checkSVTrongDSDK(dsLTCDK[i], maSV)) //sv da dk lop thu i 
		{
			ktDKLopTinChi[i] = true;
		}
	}
}

bool confirmDKMonHoc(NodeLopTC* dsLopTCDaDK[], int soLg, LopTC dsLopTCTemp[], int& pointer1, int toadoX, int toadoY, int toadoY1) {
	showCur(0);
	int pointer2 = toadoX + 30;
	while (true)
	{
		if (kbhit())
		{
			char c = getch();
			if (c == 13)
			{
				if (pointer2 == toadoX + 30)
				{
					return true;
				}
				else if (pointer2 == toadoX + 60)
				{
					for (int i = 0; i < soLg; i++)
					{
						dsLopTCDaDK[i]->data = dsLopTCTemp[i];
					}
					return true;
				}
			}
			else if (c == -32)
			{
				c = getch();
				if (c == 72)
				{
					gotoXY(toadoX + 60, toadoY1);
					cout << "Thoat";
					gotoXY(toadoX + 30, toadoY1);
					cout << "Xac Nhan";
					showCur(1);
					pointer1 = pointer1 - 2;
					return false;
				}
				else if (c == 80)
				{
					gotoXY(toadoX + 60, toadoY1);
					cout << "Thoat";
					gotoXY(toadoX + 30, toadoY1);
					cout << "Xac Nhan";
					showCur(1);
					pointer1 = toadoY;
					return false;
				}
				else if (c == 75)
				{
					if (pointer2 == toadoX + 60)
					{
						pointer2 = toadoX + 30;
					}
					else
						pointer2 = toadoX + 60;
				}
				else if (c == 77)
				{
					if (pointer2 == toadoX + 30)
					{
						pointer2 = toadoX + 60;
					}
					else
						pointer2 = toadoX + 30;
				}
			}
		}
		setColor(10);
		gotoXY(pointer2, toadoY1);
		if (pointer2 == toadoX + 30)
		{
			cout << "Xac Nhan";
			textcolor(240);
			gotoXY(toadoX + 60, toadoY1);
			cout << "Thoat";
		}
		else if (pointer2 == toadoX + 60)
		{
			cout << "Thoat";
			textcolor(240);
			gotoXY(toadoX + 30, toadoY1);
			cout << "Xac Nhan";
		}
	}
}

void runDKMonHoc(NodeLopTC* dsLopTCDK[], DsMonHoc dsMH, NodeSinhVien* nodeSV, bool ktDKLopTinChi[], int soLg, int toadoX, int toadoY)
{
	LopTC* dsLopTCTemp = new LopTC[soLg]; //ds TDK
	for (int i = 0; i < soLg; i++)
	{
		dsLopTCTemp[i] = dsLopTCDK[i]->data;
	}

	int pointer1 = toadoY;
	showCur(1);
	while (true)
	{
		gotoXY(toadoX + 91, pointer1);
		if (kbhit())
		{
			char c = getch();
			if (c == 13)
			{
				int index = (pointer1 - toadoY) / 2;
				if (!ktDKLopTinChi[index]) 
				{
					int kt = checkMHLopTC(dsLopTCDK, ktDKLopTinChi, soLg, dsLopTCDK[index], index);
					if (kt) 
					{
						cout << "X";
						ktDKLopTinChi[index] = true;

						SinhVienDK sv;
						sv.diem = -1;
						sv.masv = nodeSV->data.maSV;
						nodeSV->data.ktXoa++;
						dsLopTCDK[index]->data.dsSVDK.soLg++;
						xuLyThemSVDK(dsLopTCDK[index]->data.dsSVDK.pHead, sv);
					}
					else
					{
						gotoXY(75, 25);
						cout << "Ban Da Dang Ky Mon Hoc Nay Trong Ki Nay Roi";
					}
				}
				else
				{
					cout << " ";
					ktDKLopTinChi[index] = false;
					dsLopTCDK[index]->data.dsSVDK.soLg--;
					xuLyHuySVDK(dsLopTCDK[index]->data.dsSVDK.pHead, nodeSV->data.maSV);
					nodeSV->data.ktXoa--;
				}
				xoaManHinhTuyChon(toadoX, toadoY + 25, 105, 5 + (2 * soLg));
				int soLgLopDaDK = 0;
				NodeLopTC* dsLopTCDaDK[100];
				getDsLopTCDaDK(dsLopTCDK, dsLopTCDaDK, ktDKLopTinChi, soLg, soLgLopDaDK);
				xuatDSLopTCDaDK(dsLopTCDaDK, dsMH, soLgLopDaDK, toadoX, toadoY + 25);
			}
			else if (c == -32)
			{
				gotoXY(75, 25);
				cout << "                                            ";
				c = getch();
				if (c == 72)
				{
					pointer1 -= 2;
					if (pointer1 < toadoY)
					{
						pointer1 = toadoY;
					}
				}
				else if (c == 80)
				{
					if (pointer1 == toadoY + (2 * soLg) - 2)
					{
						int toadoYTemp = toadoY + 6 + 2 * soLg - 4;
						bool kt = confirmDKMonHoc(dsLopTCDK, soLg, dsLopTCTemp, pointer1, toadoX+15, toadoY, toadoYTemp);
						if (kt){
							delete[] dsLopTCTemp;
							return;
						}
					}
					else{
						pointer1 += 2;
					}
				}
			}
		}
	}
}

void dangKiMonHoc(DsSinhVien dsSV, DsLopTC& dsLTC, DsMonHoc dsMH, int toadoX, int toadoY){
	int nienKhoa=0, hocKy=0;
	string maSV;
	NodeSinhVien* nodeSV = NULL;

	do {
		giaoDienDKLTC();
		gotoXY(toadoX+10, toadoY+5);
		cout << "ESC: Thoat";
		gotoXY(toadoX+5 , toadoY+2);
		cout << "Nhap Vao Ma SV De Dang Ky: ";
		maSV = xuLyNhapMa();
		if (maSV == ""){
			return;
		}

		nodeSV = getNodeSinhVien(dsSV, maSV);
		if (nodeSV == NULL){
			giaoDienThongBao("Sinh Vien Khong Ton Tai");
			system("cls");
			system("color F0");
		}
	} while (nodeSV == NULL);
	system("cls");
	system("color F0");
	giaoDienDKLTC();
	xuatThongTinSV(nodeSV->data, toadoX+10, toadoY);

	char c;
	while (true){
		if (kbhit())
		{
			c = getch();
			if (c == 27)
			{
				return;
			}
			else
				break;
		}
	}
	
	system("cls");
	system("color F0");

	int soLg = 0;
	NodeLopTC* dsLTCTDK[100];

	do{
		soLg = 0;
		nienKhoa = 0;
		hocKy = 0;
		giaoDienDKLTC();
		nhapNienKhoaHocKi(nienKhoa, hocKy, toadoX+10, toadoY); 
		if (nienKhoa == -1 && hocKy == -1){
			return;
		}
		
		getDsLopTCTheoHKNK(dsLTC.root, dsLTCTDK, soLg, hocKy, nienKhoa); 
		if (soLg == 0){
			giaoDienThongBao("Khong Co Lop Nao");
			system("cls");
			system("color F0");
		}
	} while (soLg==0);
	
	system("cls");
	system("color F0");

	bool* ktDKLopTinChi = new bool[soLg] {false};
	checkDsLopTCTheoHKNK(dsLTCTDK, ktDKLopTinChi, soLg, maSV);
	xuatDSLopTC(dsLTCTDK, ktDKLopTinChi, dsMH, soLg, 35, 5);

	int soLgLopDaDK = 0;
	NodeLopTC* dsLopTCDaDK[100];
	getDsLopTCDaDK(dsLTCTDK, dsLopTCDaDK, ktDKLopTinChi, soLg, soLgLopDaDK);
	xuatDSLopTCDaDK(dsLopTCDaDK, dsMH, soLgLopDaDK, 35, 5 + 4 + 25);	
	runDKMonHoc(dsLTCTDK, dsMH, nodeSV, ktDKLopTinChi, soLg, 35, 5 + 4);
	saveLopTC(dsLTC);
	saveSinhVien(dsSV);
}

//========= Xu Ly Diem Sinh Vien ===========
void xuatDSDiem(DsSinhVien dsSV, NodeSinhVienDK* a[], int soLg, int toadoX, int toadoY, int kt = 1){
	int count = 0;
	for (int i = 0; i < soLg; i++){
		NodeSinhVien* temp = getNodeSinhVien(dsSV, a[i]->data.masv); 
		gotoXY(toadoX + 1, toadoY + 4 + (count * 2));
		cout << i + 1;
		gotoXY(toadoX + 11, toadoY + 4 + (count * 2));
		cout << a[i]->data.masv;
		gotoXY(toadoX + 41, toadoY + 4 + (count * 2));
		cout << temp->data.ho;
		gotoXY(toadoX + 71, toadoY + 4 + (count * 2));
		cout << temp->data.ten;
		gotoXY(toadoX + 91, toadoY + 4 + (count * 2));
		if (kt == 1)
		{
			if(a[i]->data.diem==0)
				cout << "0.00";
			else if (a[i]->data.diem != -1)
				cout << showpoint << setprecision(3) << a[i]->data.diem;
		}
		else {
			if (a[i]->data.diem == -1)
			{
				cout << "Chua co";
			}
			else
				cout << showpoint << setprecision(3) << a[i]->data.diem;
		}
		count++;
	}
	giaoDienNhapDiem(toadoX, toadoY, soLg);
}
void runNhapDiem(NodeSinhVienDK* a[], int soLg, int toadoX, int toadoY)
{
	gotoXY(1, 6);
	cout << "Nhan ESC: Ket Thuc Qua Trinh Nhap";
	int length = 0;
	showCur(1);
	int pointer1 = toadoY;
	while (true)
	{
		if (a[(pointer1 - toadoY) / 2]->data.diem == -1)
		{
			gotoXY(toadoX, pointer1);
		}
		else
			gotoXY(toadoX + 4, pointer1);
		if (!xuLyNhapDiem(a[(pointer1 - toadoY) / 2]->data.diem, toadoX, pointer1)) {
			return; //false thoát
		}

		if (pointer1 < toadoY)
		{
			pointer1 = toadoY;
		}
		else if (pointer1 > toadoY + (2 * soLg) - 2)
		{
			pointer1 = toadoY + (2 * soLg) - 2;
		}
	}
	showCur(0);
}
void nhapDiem(DsSinhVien dsSV, DsLopTC& dsLTC, DsMonHoc dsMH, int toadoX, int toadoY){
	int pointer1 = toadoY;
	int nienKhoa = 0;
	int hocKi = 0;
	int nhom = 0;
	string maMH="";
	NodeLopTC* nodeLopTC = NULL;
	giaoDienChonLopTC(toadoX, toadoY);

	while (true)
	{
		if (pointer1 == toadoY)
		{
			if (countNumInt(nienKhoa) == 4)
			{
				gotoXY(toadoX + 2 + 9, pointer1 + 1);
			}
			else
				gotoXY(toadoX + 2 + countNumInt(nienKhoa), pointer1 + 1);
			xuLyNhapNienKhoa(nienKhoa, toadoX + 2, pointer1);
			if (pointer1 < toadoY)
			{
				pointer1 = toadoY + 9;
			}
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + countNumInt(hocKi), pointer1 + 1);
			xuLyNhapSo(hocKi, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + countNumInt(nhom), pointer1 + 1);
			xuLyNhapSo(nhom, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + maMH.length(), pointer1 + 1);
			xuLyNhapMa(maMH, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 12)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true)
			{
				if (kbhit())
				{
					char c = getch();
					if (c == 13)
					{
						getNodeLopTCTheoNKHK(dsLTC.root, nodeLopTC, hocKi, nhom, nienKhoa, maMH);
						if (pointer2 == toadoX + 15
							&& checkNienKhoa(nienKhoa)
							&& checkHocKi(hocKi)
							&& nhom > 0
							&& getNodeMonHoc(dsMH, maMH) != NULL
							&& nodeLopTC != NULL)
						{
							int soLg = 0;
							NodeSinhVienDK* dsSVDK[100];
							getDsSVLop(nodeLopTC, dsSVDK, soLg);
							if (soLg == 0)
							{
								giaoDienThongBao("Lop Tin Chi Chua Co Sinh Vien Dang Ky ");
								return;
							}

							system("cls");
							xuatDSDiem(dsSV, dsSVDK, soLg, 35, 17);
							runNhapDiem(dsSVDK, soLg, 35 + 91, 17 + 4);
							saveLopTC(dsLTC);
							return;
						}
						else if (pointer2 == toadoX + 30)
						{
							return;
						}
						else
						{
							gotoXY(75, 40);
							if (!checkNienKhoa(nienKhoa))
							{
								cout << "Nien Khoa Khong Hop Le        ";
							}
							else if (!checkHocKi(hocKi))
							{
								cout << "Hoc Ki Khong Hop Le           ";
							}
							else if (nhom < 0)
							{
								cout << "Nhom Khong Hop Le             ";
							}
							else if (getNodeMonHoc(dsMH, maMH) == NULL)
							{
								cout << "Ma Mon Hoc Khong Ton Tai      ";
							}
							else if (nodeLopTC == NULL)
							{
								cout << "Lop Khong Ton Tai             ";
							}
							else
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 15);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 15);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 15);
					cout << "Xac Nhan";
				}
			}
		}
	}
}

//cau I
void inBangDiemCuaLopTC(DsSinhVien dsSV, DsLopTC& dsLTC, DsMonHoc dsMH, int toadoX, int toadoY){
	int pointer1 = toadoY;
	int nienKhoa = 0;
	int hocKi = 0;
	int nhom = 0;
	string maMH="";
	NodeLopTC* nodeLopTC = NULL;
	giaoDienChonLopTC(toadoX, toadoY);

	while (true)
	{
		if (pointer1 == toadoY)
		{
			if (countNumInt(nienKhoa) == 4)
			{
				gotoXY(toadoX + 2 + 9, pointer1 + 1);
			}
			else
				gotoXY(toadoX + 2 + countNumInt(nienKhoa), pointer1 + 1);
			xuLyNhapNienKhoa(nienKhoa, toadoX + 2, pointer1);
			if (pointer1 < toadoY)
			{
				pointer1 = toadoY + 9;
			}
		}
		else if (pointer1 == toadoY + 3)
		{
			gotoXY(toadoX + 2 + countNumInt(hocKi), pointer1 + 1);
			xuLyNhapSo(hocKi, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 6)
		{
			gotoXY(toadoX + 2 + countNumInt(nhom), pointer1 + 1);
			xuLyNhapSo(nhom, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 9)
		{
			gotoXY(toadoX + 2 + maMH.length(), pointer1 + 1);
			xuLyNhapMa(maMH, toadoX + 2, pointer1);
		}
		else if (pointer1 == toadoY + 12)
		{
			showCur(0);
			int pointer2 = toadoX + 15;
			while (true)
			{
				if (kbhit())
				{
					char c = getch();
					if (c == 13)
					{
						getNodeLopTCTheoNKHK(dsLTC.root, nodeLopTC, hocKi, nhom, nienKhoa, maMH);
						if (pointer2 == toadoX + 15
							&& checkNienKhoa(nienKhoa)
							&& checkHocKi(hocKi)
							&& nhom > 0
							&& getNodeMonHoc(dsMH, maMH) != NULL
							&& nodeLopTC != NULL
							)
						{

							int soLg = 0;
							NodeSinhVienDK* dsSVDK[100];
							getDsSVLop(nodeLopTC, dsSVDK, soLg);
							if (soLg == 0)
							{
								giaoDienThongBao("Lop Chua Co Sinh Vien Nao");
								return;
							}

							system("cls");
							gotoXY(toadoX, 5);
							cout << "BANG DIEM MON HOC " << getTenMonHoc(dsMH, maMH);
							gotoXY(toadoX, 5 + 1);
							cout << "Nien Khoa :" << nienKhoa << " Hoc Ki :" << hocKi << " Nhom :" << nhom;
							xuatDSDiem(dsSV, dsSVDK, soLg, 35, 5 + 3,0);
							getch();

							system("cls");
							system("color F0");
							pointer1 = toadoY;
							nienKhoa = 0;
							hocKi = 0;
							nhom = 0;
							maMH = "";
							giaoDienChonLopTC(toadoX, toadoY);
							return;
						}
						else if (pointer2 == toadoX + 30)
						{
							return;
						}
						else
						{
							gotoXY(75, 40);
							if (!checkNienKhoa(nienKhoa))
							{
								cout << "Nien Khoa Khong Hop Le        ";
							}
							else if (!checkHocKi(hocKi))
							{
								cout << "Hoc Ki Khong Hop Le           ";
							}
							else if (nhom < 0)
							{
								cout << "Nhom Khong Hop Le             ";
							}
							else if (getNodeMonHoc(dsMH, maMH) == NULL)
							{
								cout << "Ma Mon Hoc Khong Ton Tai      ";
							}
							else if (nodeLopTC == NULL)
							{
								cout << "Lop Khong Ton Tai             ";
							}
							else
							{
								cout << "Vui Long Dien Day Du Thong Tin";
							}
						}
					}
					else if (c == -32)
					{
						c = getch();
						if (c == 72)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = pointer1 - 3;
							break;
						}
						else if (c == 80)
						{
							gotoXY(toadoX + 30, toadoY + 15);
							cout << "Thoat";
							gotoXY(toadoX + 15, toadoY + 15);
							cout << "Xac Nhan";
							showCur(1);
							pointer1 = toadoY;
							break;
						}
						else if (c == 75)
						{
							if (pointer2 == toadoX + 30)
							{
								pointer2 = toadoX + 15;
							}
							else
								pointer2 = toadoX + 30;
						}
						else if (c == 77)
						{
							if (pointer2 == toadoX + 15)
							{
								pointer2 = toadoX + 30;
							}
							else
								pointer2 = toadoX + 15;
						}
					}
				}

				setColor(10);
				gotoXY(pointer2, toadoY + 15);
				if (pointer2 == toadoX + 15)
				{
					cout << "Xac Nhan";
					textcolor(240);
					gotoXY(toadoX + 30, toadoY + 15);
					cout << "Thoat";
				}
				else if (pointer2 == toadoX + 30)
				{
					cout << "Thoat";
					textcolor(240);
					gotoXY(toadoX + 15, toadoY + 15);
					cout << "Xac Nhan";
				}
			}
		}
	}
}
