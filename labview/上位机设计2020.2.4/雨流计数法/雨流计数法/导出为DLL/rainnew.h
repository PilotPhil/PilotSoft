//#pragma once
#include"pch.h"

struct DataOk//������Ч�Խṹ�� ��ȥ�ظ�Ԫ�غ󱣴�
{
	int Size;
	int* Value;
};

struct Rain//��Ƚṹ��
{
	int PVn;//�����
	int* Value;//ֵ
	int* ID;//��ȱ�ʶ 1����  -1����  0��������
};

struct TR
{
	int *Amp;
	int *Ave;
	int size;
};


int MyMax(int a, int b);//�����ֵ

int MyMin(int a, int b);//����Сֵ

void PV_Print(int* p, int len);//��Ƚṹ���������

void PV_Test(Rain Inp);//���������������

DataOk PV_NoSame(int* Inp, int len);

int PV_4Points(int a, int b, int c, int d);
//�޳��ظ�Ԫ�� ����һ��



Rain PV_Extra(DataOk Inp);//��ȡ��� д���ʶ 1����  -1����

Rain PV_Adjust(Rain Inp);//�غ����̵���

Rain PV_Sweep(Rain Inp);//�Ӿ���ֵ��С��Ԫ�ش�����

TR PV_Count(Rain Inp);//�ĵ������