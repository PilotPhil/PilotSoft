#pragma once
#include<iostream>
#include<math.h>
using namespace std;


//������Խṹ��
struct PeakVallyDef
{
	int PVNum;//��͹�����
	int PNum;//������
	int VNum;//������
	int* PVTime;//��ȶ�Ӧ��ʱ����
	int* Value;//���ֵ��С
	int* PVID;//���ID 1���� -1����
};

struct Cou
{
	int* X_Index;
	int* Y_Index;
	int len;
};

void PV_Print(int* p, int len);//����Ԫ�ش�ӡ��

int MyMax(int a, int b);//�����ֵ

int MyMin(int a, int b);//����Сֵ

void PVCopy(PeakVallyDef* A, PeakVallyDef B);//����PV�ṹ�帴���ã�Bֵ���ݲ���������Ӱ��

void PVTest(PeakVallyDef PV);//����ṹ������Ԫ�ز�����

int PVFindMin(PeakVallyDef adj);//�ҵ������о���ֵ��СԪ�ص��±�

void PVSweep(PeakVallyDef* adj);///����СԪ�ش��׶����ҽ���ƴ��-

PeakVallyDef PVFetch(int* RawData, int Length);//�����ȡ

PeakVallyDef PVAdjust(PeakVallyDef fg);//�غ����̵���

int FourPoint(int a, int b, int c, int d);//�ĵ������

Cou PVCount(PeakVallyDef Inp);

/*---��labview����DLLʹ��---*/
extern "C" __declspec(dllexport) void PV_For_Labview_DLL
(int length, int* RawData, int* Data, int* time, int* Num, int* RealData, int* RealTime, int* RealNum, int* X, int* Y);