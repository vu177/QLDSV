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
using namespace std;

#define MAXMH 300
int pointer = 17; 
int soLgSoConLai = 0;
int* mangRanDom;

//============= Mon hoc =============
struct MonHoc {
	string maMH;
	string tenMH;
	float stclt;
	float stcth;
	int check = 0;
};

struct DsMonHoc {
	MonHoc *nodeMH[MAXMH];
	int soLuong = 0;
};

//============= Dang ky =============
struct SinhVienDK {
	string masv;
	float diem;
};

struct NodeSinhVienDK{
	SinhVienDK data;
	NodeSinhVienDK* pNext;
};

struct DsSinhVienDK {
	NodeSinhVienDK* pHead = NULL;
	int soLg = 0;
};

//============= Lop tin chi =============
struct LopTC {
	int maLopTC;
	string maMH;
	int nienKhoa;
	int hocKy;
	int nhom;
	int sosvMax;
	int sosvMin;
	DsSinhVienDK dsSVDK; //tro den phan tu dau cua danh sach dang ky
};

struct NodeLopTC{
	LopTC data;
	NodeLopTC* pLeft;
	NodeLopTC* pRight;
};

struct DsLopTC {
	NodeLopTC* root=NULL;
	int soLg = 0;
};

//============= Sinh vien =============
struct SinhVien{
	string maLop;
	string maSV;
	string ho;
	string ten;
	int phai;
	string sdt;
	int namNhapHoc;
	int ktXoa = 0;
};

struct NodeSinhVien {
	SinhVien data;
	NodeSinhVien* pNext;
};

struct DsSinhVien {
	NodeSinhVien* pHead = NULL;
	int solg = 0;
};


