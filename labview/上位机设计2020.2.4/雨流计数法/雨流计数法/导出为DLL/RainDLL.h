#pragma once
#include<iostream>
#include<math.h>
using namespace std;


//峰谷特性结构体
struct PeakVallyDef
{
	int PVNum;//峰和谷总数
	int PNum;//峰数量
	int VNum;//谷数量
	int* PVTime;//峰谷对应的时间标记
	int* Value;//峰谷值大小
	int* PVID;//峰谷ID 1：峰 -1：谷
};

struct Cou
{
	int* X_Index;
	int* Y_Index;
	int len;
};

void PV_Print(int* p, int len);//数组元素打印用

int MyMax(int a, int b);//求最大值

int MyMin(int a, int b);//求最小值

void PVCopy(PeakVallyDef* A, PeakVallyDef B);//两个PV结构体复制用，B值传递不会对其造成影响

void PVTest(PeakVallyDef PV);//输出结构体所有元素测试用

int PVFindMin(PeakVallyDef adj);//找到数组中绝对值最小元素的下标

void PVSweep(PeakVallyDef* adj);///从最小元素处阶段左右交换拼接-

PeakVallyDef PVFetch(int* RawData, int Length);//峰谷提取

PeakVallyDef PVAdjust(PeakVallyDef fg);//载荷历程调整

int FourPoint(int a, int b, int c, int d);//四点计数法

Cou PVCount(PeakVallyDef Inp);

/*---供labview调用DLL使用---*/
extern "C" __declspec(dllexport) void PV_For_Labview_DLL
(int length, int* RawData, int* Data, int* time, int* Num, int* RealData, int* RealTime, int* RealNum, int* X, int* Y);