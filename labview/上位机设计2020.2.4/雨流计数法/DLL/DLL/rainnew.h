//#pragma once

struct Valid//������Ч�Խṹ�� ��ȥ�ظ�Ԫ�غ󱣴�
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

struct Count
{
	int Num;
	int* Amp;//��ֵ
	int* Ave;//��ֵ
};

int MyMax(int a, int b);//�����ֵ

int MyMin(int a, int b);//����Сֵ

void PV_Print(int* p, int len);//��Ƚṹ���������

void PV_Test(Rain Inp);//���������������

Valid PV_NoSame(int* Inp, int len);

int PV_4Points(int a, int b, int c, int d);
//�޳��ظ�Ԫ�� ����һ��

Rain PV_Extra(Valid Inp);//��ȡ��� д���ʶ 1����  -1����

Rain PV_Adjust(Rain Inp);//�غ����̵���

Rain PV_Sweep(Rain Inp);//�Ӿ���ֵ��С��Ԫ�ش�����

TR PV_Count(Rain Inp);//�ĵ������

extern "C" __declspec(dllexport) void for_labview
(
	int LenRawData, int* RawData,//ԭʼ���ݼ�����
	int* time,//ʱ���
	int* Extra, int* LenExtra,//��ȡ������ݺͳ���
	int* Adjust, int* LenAdjust,//�غ����̵������ݺͳ���
	int* Amp, int* Avg, int* LenCount//��ֵ ��ֵ �ͳ���
);