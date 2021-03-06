#pragma once
#include<iostream>
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

struct Full
{
	int len;
	float *XLabel;
	float* YLabel;
};

void PVFind(int* Inp, int len);

void PV_Print(int* p, int len);//数组元素打印用

int MyMax(int a, int b);//求最大值

int MyMin(int a, int b);//求最小值

int* Diff(int* Inp, int length);//差分 返回len-1的数组首地址

void Judge(int* Inp, int length);//正向遍历判断

void RevJudge(int* Inp, int len);//反向遍历判断

void MoveBack(int* Inp, int len);

void PVCopy(PeakVallyDef* A, PeakVallyDef B);//两个PV结构体复制用，B值传递不会对其造成影响

void PVTest(PeakVallyDef PV);//输出结构体所有元素测试用

int PVFindMin(PeakVallyDef adj);//找到数组中绝对值最小元素的下标

void PVSweep(PeakVallyDef* adj);///从最小元素处阶段左右交换拼接-

PeakVallyDef PVFetch(int* RawData, int Length);//峰谷提取

PeakVallyDef PVAdjust(PeakVallyDef fg);//载荷历程调整

int FourPoint(int a, int b, int c, int d);//四点计数法

/*---供labview调用DLL使用---*/
void PV_For_Labview_DLL(int* RawData, int length, int* Data, int* time, int* Num, int* RealData, int* RealTime, int* RealNum);
