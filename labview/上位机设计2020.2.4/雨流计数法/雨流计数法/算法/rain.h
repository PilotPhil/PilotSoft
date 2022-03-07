#pragma once
#include<iostream>
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

struct Full
{
	int len;
	float *XLabel;
	float* YLabel;
};

void PVFind(int* Inp, int len);

void PV_Print(int* p, int len);//����Ԫ�ش�ӡ��

int MyMax(int a, int b);//�����ֵ

int MyMin(int a, int b);//����Сֵ

int* Diff(int* Inp, int length);//��� ����len-1�������׵�ַ

void Judge(int* Inp, int length);//��������ж�

void RevJudge(int* Inp, int len);//��������ж�

void MoveBack(int* Inp, int len);

void PVCopy(PeakVallyDef* A, PeakVallyDef B);//����PV�ṹ�帴���ã�Bֵ���ݲ���������Ӱ��

void PVTest(PeakVallyDef PV);//����ṹ������Ԫ�ز�����

int PVFindMin(PeakVallyDef adj);//�ҵ������о���ֵ��СԪ�ص��±�

void PVSweep(PeakVallyDef* adj);///����СԪ�ش��׶����ҽ���ƴ��-

PeakVallyDef PVFetch(int* RawData, int Length);//�����ȡ

PeakVallyDef PVAdjust(PeakVallyDef fg);//�غ����̵���

int FourPoint(int a, int b, int c, int d);//�ĵ������

/*---��labview����DLLʹ��---*/
void PV_For_Labview_DLL(int* RawData, int length, int* Data, int* time, int* Num, int* RealData, int* RealTime, int* RealNum);
