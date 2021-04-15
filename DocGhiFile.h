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

void loadDSSoRanDom()
{
	ifstream fileIn("RanDom.txt", ios::in);
	fileIn >> soLgSoConLai;
	fileIn.ignore();
	mangRanDom = new int[soLgSoConLai];

	for (int i = 0; i < soLgSoConLai; i++)
	{
		fileIn >> mangRanDom[i];
	}

	fileIn.close();
}
void loadDSSV(DsSinhVien &dsSV)
{
	ifstream fileIn("inputSV.txt", ios::in);
	string str;
	int n;
	fileIn >> n;
	fileIn.ignore();

	for(int i=0;i<n;i++)
	{
		SinhVien sv;
		getline(fileIn, sv.maLop, ',');
		getline(fileIn, sv.maSV, ',');
		getline(fileIn, str, ',');
		tachLayTenVaHo(str, sv.ten, sv.ho);
		fileIn >> sv.phai ;
		fileIn.ignore();
		getline(fileIn, sv.sdt,',');
		fileIn >> sv.namNhapHoc;
		fileIn.ignore();
		fileIn >> sv.ktXoa;
		fileIn.ignore();
		
		xuLyThemSVTheoThuTu(dsSV, sv);
	}

	fileIn.close();
}
void loadDSMH(DsMonHoc& dsMH)
{
	int n;
	ifstream fileIn("inputMH.txt", ios::in);
	fileIn >> n;
	fileIn.ignore();

	for (int i = 0; i < n; i++)
	{
		MonHoc mh;
		getline(fileIn, mh.maMH, ',');
		getline(fileIn, mh.tenMH, ',');
		fileIn >> mh.stclt;
		fileIn.ignore();
		fileIn >> mh.stcth;
		fileIn.ignore();

		fileIn >> mh.check;
		fileIn.ignore();
		
		xuLyThemMonHoc(dsMH, mh);
	}
	fileIn.close();
}
void loadDSLTC(DsLopTC& dsLTC)
{
	ifstream fileIn("inputLTC.txt", ios::in);
	fileIn >> dsLTC.soLg;
	fileIn.ignore();

	for (int i = 0; i < dsLTC.soLg; i++)
	{
		LopTC lopTC;
		fileIn >> lopTC.maLopTC;
		fileIn.ignore();
		fileIn >> lopTC.nienKhoa;
		fileIn.ignore();
		getline(fileIn, lopTC.maMH, ',');
		fileIn >> lopTC.hocKy;
		fileIn.ignore();
		fileIn >> lopTC.nhom;
		fileIn.ignore();
		fileIn >> lopTC.sosvMin;
		fileIn.ignore();
		fileIn >> lopTC.sosvMax;
		fileIn.ignore();
		fileIn >> lopTC.dsSVDK.soLg;
		fileIn.ignore();

		for (int j = 0; j < lopTC.dsSVDK.soLg; j++)
		{
			SinhVienDK svDK;
			getline(fileIn, svDK.masv, ',');
			fileIn >> svDK.diem;
			fileIn.ignore();
			xuLyThemSVDK(lopTC.dsSVDK.pHead, svDK);
		}

		xuLyThemLopTC(dsLTC.root, lopTC);
	}

	fileIn.close();
}

void saveDSSoRanDom()
{
	ofstream fileOut("RanDom.txt", ios::out);
	fileOut << soLgSoConLai << endl;

	for (int i = 0; i < soLgSoConLai; i++)
	{
		fileOut << mangRanDom[i] << " ";
	}

	fileOut.close();
}
void saveSinhVien(DsSinhVien dsSV)
{
	ofstream fileOut("inputSV.txt", ios::out);
	fileOut << dsSV.solg << endl;

	for (NodeSinhVien* k = dsSV.pHead; k != NULL; k = k->pNext)
	{
		fileOut << k->data.maLop << "," << k->data.maSV << "," 
			<< k->data.ho + " " + k->data.ten << "," << k->data.phai << "," 
			<< k->data.sdt<<","<<k->data.namNhapHoc << ","
			<< k->data.ktXoa << endl;
	}


	fileOut.close();
}
void saveMonHoc(DsMonHoc dsMH)
{
	ofstream fileOut("inputMH.txt", ios::out);
	fileOut << dsMH.soLuong << endl;
	
	for (int i = 0; i < dsMH.soLuong; i++)
	{
		fileOut << dsMH.nodeMH[i]->maMH << "," << dsMH.nodeMH[i]->tenMH << ","
			<< dsMH.nodeMH[i]->stclt << "," << dsMH.nodeMH[i]->stclt <<","
			<< dsMH.nodeMH[i]->check<< endl;
	}

	fileOut.close();
}
void xuLySaveLopTC(NodeLopTC *root,ofstream &fileOut)
{
	if (root == NULL)
	{
		return;
	}

	fileOut << root->data.maLopTC<< "," << root->data.nienKhoa << "," << root->data.maMH << ","
		<< root->data.hocKy << "," << root->data.nhom << "," << root->data.sosvMin << "," << root->data.sosvMax << ","
		<< root->data.dsSVDK.soLg << endl;
	for (NodeSinhVienDK* k = root->data.dsSVDK.pHead; k != NULL; k = k->pNext)
	{
		fileOut << k->data.masv << "," << k->data.diem << endl;
	}

	xuLySaveLopTC(root->pLeft, fileOut);
	xuLySaveLopTC(root->pRight, fileOut);
}
void saveLopTC(DsLopTC dsLTC)
{
	ofstream fileOut("inputLTC.txt", ios::out);
	fileOut << dsLTC.soLg << endl;
	xuLySaveLopTC(dsLTC.root, fileOut);
	fileOut.close();
}

void deleteMemorySV(DsSinhVien &dsSV)
{
	while (dsSV.pHead != NULL)
	{
		NodeSinhVien* p = dsSV.pHead;
		dsSV.pHead = dsSV.pHead->pNext;
		delete p;
	}
}
void deleteMemoryMonHoc(DsMonHoc &dsMH)
{
	for (int i = 0; i < dsMH.soLuong; i++)
	{
		delete dsMH.nodeMH[i];
	}
}
void xuLydeleteMemoryLopTC(NodeLopTC*& root)
{
	if(root==NULL)
	{
		return;
	}

	xuLydeleteMemoryLopTC(root->pLeft);
	xuLydeleteMemoryLopTC(root->pRight);
	while (root->data.dsSVDK.pHead != NULL)
	{
		NodeSinhVienDK* p = root->data.dsSVDK.pHead;
		root->data.dsSVDK.pHead = root->data.dsSVDK.pHead->pNext;
	}
	delete root;
}
void deleteMemoryLopTC(DsLopTC& dsLTC)
{
	xuLydeleteMemoryLopTC(dsLTC.root);
}
