#pragma once
#include"rainnew.h"


extern "C" __declspec(dllexport) void for_labview
(
	int LenRawData, int* RawData,//ԭʼ���ݼ�����
	int* time,//ʱ���
	int* Extra, int* LenExtra,//��ȡ������ݺͳ���
	int* Adjust, int* LenAdjust,//�غ����̵������ݺͳ���
	int* Amp, int* Avg, int* LenCount//��ֵ ��ֵ �ͳ���
);