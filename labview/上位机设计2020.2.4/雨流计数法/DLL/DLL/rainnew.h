//#pragma once

struct Valid//数据有效性结构体 除去重复元素后保存
{
	int Size;
	int* Value;
};

struct Rain//峰谷结构体
{
	int PVn;//峰谷数
	int* Value;//值
	int* ID;//峰谷标识 1：峰  -1：谷  0：都不是
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
	int* Amp;//幅值
	int* Ave;//均值
};

int MyMax(int a, int b);//求最大值

int MyMin(int a, int b);//求最小值

void PV_Print(int* p, int len);//峰谷结构体输出测试

void PV_Test(Rain Inp);//单独数组输出测试

Valid PV_NoSame(int* Inp, int len);

int PV_4Points(int a, int b, int c, int d);
//剔除重复元素 保留一个

Rain PV_Extra(Valid Inp);//提取峰谷 写入标识 1：峰  -1：谷

Rain PV_Adjust(Rain Inp);//载荷历程调整

Rain PV_Sweep(Rain Inp);//从绝对值最小的元素处交换

TR PV_Count(Rain Inp);//四点计数法

extern "C" __declspec(dllexport) void for_labview
(
	int LenRawData, int* RawData,//原始数据及长度
	int* time,//时间戳
	int* Extra, int* LenExtra,//提取峰谷数据和长度
	int* Adjust, int* LenAdjust,//载荷历程调整数据和长度
	int* Amp, int* Avg, int* LenCount//幅值 均值 和长度
);