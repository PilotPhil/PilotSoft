#pragma once
#include"rainnew.h"


extern "C" __declspec(dllexport) void for_labview
(
	int LenRawData, int* RawData,//原始数据及长度
	int* time,//时间戳
	int* Extra, int* LenExtra,//提取峰谷数据和长度
	int* Adjust, int* LenAdjust,//载荷历程调整数据和长度
	int* Amp, int* Avg, int* LenCount//幅值 均值 和长度
);