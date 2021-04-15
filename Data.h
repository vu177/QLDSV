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
#include "KhaiBao.h"

NodeLopTC* getNodeLopTC(NodeLopTC* root, int maLopTC)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->data.maLopTC == maLopTC)
	{
		return root;
	}
	else if (root->data.maLopTC > maLopTC)
	{
		return getNodeLopTC(root->pLeft, maLopTC);
	}
	else
	{
		return getNodeLopTC(root->pRight, maLopTC);
	}
}
void getNodeLopTCTheoNKHK(NodeLopTC* root, NodeLopTC* &temp, int hocKi, int nhom, int nienKhoa, string maMonHoc)
{
	if (root == NULL)
	{
		return;
	}

	if (root->data.hocKy == hocKi && root->data.nhom == nhom && root->data.nienKhoa == nienKhoa
		&& root->data.maMH == maMonHoc)
	{
		temp = root;
	}

	getNodeLopTCTheoNKHK(root->pRight, temp, hocKi, nhom, nienKhoa, maMonHoc);
	getNodeLopTCTheoNKHK(root->pLeft, temp, hocKi, nhom, nienKhoa, maMonHoc);

}

void chuyenCaySangMang(NodeLopTC* root, LopTC a[], int& n)
{
	if (root == NULL){
		return;
	}
	a[n++] = root->data;
	chuyenCaySangMang(root->pLeft, a, n);
	chuyenCaySangMang(root->pRight, a, n);
}
void sapXepLTCTheoMHvaHK(LopTC a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].maMH  + convertIntToString(a[i].nhom) > a[j].maMH + convertIntToString(a[i].nhom) )
			{
				LopTC temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}
void xuatDSLTCTheoMHvaHK(DsLopTC dsLTC, int toadoX, int toadoY)
{
	LopTC a[100];
	int soLg = 0;
	chuyenCaySangMang(dsLTC.root, a, soLg);
	sapXepLTCTheoMHvaHK(a, soLg);

	for (int i = 0; i < soLg; i++)
	{
		gotoXY(toadoX, toadoY);
		cout << a[i].maLopTC;
		gotoXY(toadoX + 10, toadoY);
		cout << a[i].maMH;
		gotoXY(toadoX + 25, toadoY);
		cout << getNienKhoa(a[i].nienKhoa);
		gotoXY(toadoX + 35, toadoY);
		cout << a[i].hocKy;
		gotoXY(toadoX + 40, toadoY);
		cout << a[i].nhom;
		toadoY++;
	}
}

void xuLyThemLopTC(NodeLopTC *&root,LopTC lopTC)
{
	if (root == NULL)
	{
		NodeLopTC* nodeLopTC = new NodeLopTC;
		nodeLopTC->data = lopTC;
		nodeLopTC->pLeft = NULL;
		nodeLopTC->pRight = NULL;
		root = nodeLopTC;
	}
	else if (root->data.maLopTC > lopTC.maLopTC)
	{
		return xuLyThemLopTC(root->pLeft, lopTC);
	}
	else
	{
		return xuLyThemLopTC(root->pRight, lopTC);
	}
}
void xoaNode2Con(NodeLopTC* tam, NodeLopTC*& t)
{
	if (t->pLeft != NULL)
	{
		xoaNode2Con(tam, t->pLeft);
	}
	else
	{
		tam->data = t->data;
		tam = t;
		t = t->pRight;
	}
}
void xuLyXoaLopTC(NodeLopTC*& root, int ma)
{
	if (root == NULL)
	{
		return;
	}

	if (ma > root->data.maLopTC)
	{
		xuLyXoaLopTC(root->pRight, ma);
	}
	else if (ma < root->data.maLopTC)
	{
		xuLyXoaLopTC(root->pLeft, ma);
	}
	else
	{
		NodeLopTC* tam = root;
		if (root->pLeft == NULL)
		{
			root = root->pRight;
		}
		else if (root->pRight == NULL)
		{
			root = root->pLeft;
		}
		else if (root->pLeft != NULL && root->pRight != NULL)
		{
			xoaNode2Con(tam, root->pRight);
		}
		delete tam;
	}
}
void getDsSVLop(NodeLopTC *lopTC, NodeSinhVienDK *dsSV[],int &soLg)
{
	for (NodeSinhVienDK* k = lopTC->data.dsSVDK.pHead; k != NULL; k = k->pNext)
	{
		dsSV[soLg++] = k;
	}
}

MonHoc* getNodeMonHoc(DsMonHoc dsMH, string maMH)
{
	for (int i = 0; i < dsMH.soLuong; i++)
	{
		if (dsMH.nodeMH[i]->maMH == maMH)
		{
			return dsMH.nodeMH[i];
		}
	}
	return NULL;
}
void xuLyThemMonHoc(DsMonHoc &dsMH, MonHoc mh)
{
	dsMH.nodeMH[dsMH.soLuong] = new MonHoc;
	*dsMH.nodeMH[dsMH.soLuong] = mh;
	dsMH.soLuong++;
}
void xuLyXoaMonHoc(DsMonHoc& dsMH,string maMH)
{
	for (int i = 0; i < dsMH.soLuong; i++)
	{
		if (dsMH.nodeMH[i]->maMH == maMH)
		{
			for (int j = i; j < dsMH.soLuong-1; j++)
			{
				*dsMH.nodeMH[j] = *dsMH.nodeMH[j+1];
			}

			delete dsMH.nodeMH[dsMH.soLuong - 1];
			dsMH.soLuong--;
		}
	}
}
void sapXepMonHoc(DsMonHoc &dsMH)
{
	for (int i = 0; i < dsMH.soLuong - 1; i++)
	{
		for (int j = i + 1; j < dsMH.soLuong; j++)
		{
			if (dsMH.nodeMH[i]->tenMH > dsMH.nodeMH[j]->tenMH)
			{
				MonHoc temp = *dsMH.nodeMH[i];
				*dsMH.nodeMH[i] = *dsMH.nodeMH[j];
				*dsMH.nodeMH[j] = temp;
			}
		}
	}
}
string getTenMonHoc(DsMonHoc dsMH, string maMH)
{
	for (int i = 0; i < dsMH.soLuong; i++)
	{
		if (dsMH.nodeMH[i]->maMH == maMH)
		{
			return dsMH.nodeMH[i]->tenMH;
		}
	}
	return "";
}

NodeSinhVien* getNodeSinhVien(DsSinhVien dsSV,string maSV)
{
	for (NodeSinhVien* k = dsSV.pHead; k != NULL; k = k ->pNext)
	{
		if (k->data.maSV == maSV)
		{
			return k;
		}
	}
	return NULL;
}

void xuLyThemSVTheoThuTu(DsSinhVien &dsSV,SinhVien sv)
{
	NodeSinhVien* nodeSV = new NodeSinhVien;
	nodeSV->pNext = NULL;
	nodeSV->data = sv;
	dsSV.solg++;

	if (dsSV.pHead == NULL)
	{
		dsSV.pHead = nodeSV;
		return;
	}

	if (nodeSV->data.maLop + nodeSV->data.maSV 
			< dsSV.pHead->data.maLop + dsSV.pHead->data.maSV)
	{
		nodeSV->pNext = dsSV.pHead;
		dsSV.pHead = nodeSV;
		return;
	}

	NodeSinhVien* pPrev = dsSV.pHead;
	for (NodeSinhVien* k = dsSV.pHead->pNext; k != NULL; k = k->pNext,pPrev = k)
	{
		if (nodeSV->data.maLop + nodeSV->data.maSV  < k->data.maLop + k->data.maSV)
		{
			pPrev->pNext = nodeSV;
			nodeSV->pNext = k;
			return;
		}
	//	pPrev = k;
	}

	pPrev->pNext = nodeSV;
}
void xuLyXoaSV(DsSinhVien &dsSV, string maSV)
{
	NodeSinhVien* pPrev = dsSV.pHead;
	if (pPrev->data.maSV == maSV)
	{
		dsSV.solg--;
		dsSV.pHead = dsSV.pHead->pNext;
		delete pPrev;
		return;
	}

	for (NodeSinhVien* k = dsSV.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.maSV == maSV)
		{
			dsSV.solg--;
			pPrev->pNext = k->pNext; //k sau prev
			delete k;
			return;
		}
		pPrev = k;
	}
}

NodeSinhVien* getSVDauLop(DsSinhVien dsSV, string maLop)
{
	for (NodeSinhVien* k = dsSV.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.maLop == maLop)
		{
			return k;
		}
	}
	return NULL;
}

void xuLyThemSVDK(NodeSinhVienDK* &pHead, SinhVienDK sv)
{
	NodeSinhVienDK* p = new NodeSinhVienDK;
	p->pNext = NULL;
	p->data = sv;

	if (pHead == NULL)
	{
		pHead = p;
		return;
	}

	NodeSinhVienDK* temp = pHead;
	while (true)
	{
		if (temp->pNext == NULL)
		{
			temp->pNext = p;
			return;
		}
		temp = temp->pNext;
	}
}
void xuLyHuySVDK(NodeSinhVienDK*& pHead, string maSV)
{
	NodeSinhVienDK* pPre = pHead;
	if (pHead->data.masv == maSV)
	{
		pHead = pHead->pNext;
		delete pPre;
		return;
	}

	for (NodeSinhVienDK* k = pHead->pNext; k != NULL; k = k->pNext)
	{
		if (k->data.masv == maSV)
		{
			pPre->pNext = k->pNext;
			delete k;
			return;
		}
		pPre = pPre->pNext;
	}
}

int getSTCTheoMa(DsMonHoc dsMH, string maMH)
{
	for (int i = 0; i < dsMH.soLuong; i++)
	{
		if (dsMH.nodeMH[i]->maMH == maMH)
		{
			return dsMH.nodeMH[i]->stclt + dsMH.nodeMH[i]->stcth;
		}
	}
	return -1;
}

bool checkSVTrongDSDK(NodeLopTC* lopTC, string maSV)
{
	for (NodeSinhVienDK* k = lopTC->data.dsSVDK.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.masv == maSV)
		{
			return true;
		}
	}
	return false;
}
int getSoLgConLaiLopTC(NodeLopTC* lopTC)
{
	return lopTC->data.sosvMax - lopTC->data.dsSVDK.soLg;
}
