#include"pch.h"
#include"RainDLL.h"

void PVPrint(int* p, int len)
{
	for (int i = 0; i < len; i++)
		cout << *(p + i) << " ";
	cout << endl;
}

int MyMax(int a, int b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int MyMin(int a, int b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

void PVCopy(PeakVallyDef* A, PeakVallyDef B)
{
	A->PVNum = B.PVNum;
	A->PNum = B.PNum;
	A->VNum = B.VNum;

	A->PVTime = B.PVTime;
	A->Value = B.Value;
	A->PVID = B.PVID;
}

void PVTest(PeakVallyDef PV)
{
	cout << endl;
	PVPrint(PV.PVTime, PV.PVNum);
	PVPrint(PV.Value, PV.PVNum);
	PVPrint(PV.PVID, PV.PVNum);
	cout << "Peak:" << PV.PNum << "Vally:" << PV.VNum << "ALL:" << PV.PVNum << endl;
}

int PVFindMin(PeakVallyDef adj)
{

	int* Value = new int(abs(*(adj.Value)));//++++++1
	int* Index = new int(0);//++++++2

	for (int i = 0; i < adj.PVNum; i++)
	{
		if (abs(*(adj.Value + i)) <= *Value)
		{
			*Value = abs(*(adj.Value + i));//找到一个更大的，赋值给临时变量
			*Index = i;//并且保存下标
		}
	}

	return (*Index) + 1;//返回最大值所在的下标+1

	delete Value;//-------1
	delete Index;//-------2
}

void PVSweep(PeakVallyDef* adj)
{
	int IndexMin = PVFindMin(*adj);

	//将前半和后半交换位置并存放
	//前后都包含最大值
	//但是首位值相等，交换拼接时省略一个点（省略 头值）
	//头尾拼接于Temp

	int j = 0;//索引
	int* TempValue = new int[adj->PVNum]();//动态内存分配并初始化用小括号
	int* TempIndex = new int[adj->PVNum]();//动态内存分配并初始化用小括号
	int* TempID = new int[adj->PVNum]();//动态内存分配并初始化用小括号

	for (int i = IndexMin - 1; i < adj->PVNum; i++, j++)//将后部分赋值给Temp
	{
		//注：j从0开始 下标没有错误
		*(TempIndex + j) = *(adj->PVTime + i);
		*(TempValue + j) = *(adj->Value + i);
		*(TempID + j) = *(adj->PVID + i);
	}

	for (int i = 1; i < IndexMin; i++, j++)//将前部分赋值给Temp
	{
		*(TempIndex + j) = *(adj->PVTime + i);
		*(TempValue + j) = *(adj->Value + i);
		*(TempID + j) = *(adj->PVID + i);
	}

	for (int i = 0; i < adj->PVNum; i++)
	{
		*(adj->PVTime + i) = *(TempIndex + i);
		*(adj->Value + i) = *(TempValue + i);
		*(adj->PVID + i) = *(TempID + i);
	}

	delete[]TempIndex;
	delete[]TempValue;
	delete[]TempID;
}

int FourPoint(int a, int b, int c, int d)
{
	int* t1 = new int(abs(b - a));
	int* t2 = new int(abs(c - b));
	int* t3 = new int(abs(d - c));

	if (*t1 >= *t2 && *t3 >= *t2)
	{
		return 1;

	}
	else
	{
		return 0;
	}
	delete t3;
	delete t2;
	delete t1;
}

PeakVallyDef PVFetch(int* RawData, int Length)
{
	PeakVallyDef RES;//实例化构造体对象

	int i = 0;

	/*----------第一次差分----------*/
	int* FirstTemp = new int[Length - 1];//暂存+++++++++++1
	for (i = 0; i < Length - 1; i++)
	{
		*(FirstTemp + i) = *(RawData + i + 1) - *(RawData + i);
		//取符号运算
		if (*(FirstTemp + i) > 0)
			*(FirstTemp + i) = 1;
		else if (*(FirstTemp + i) < 0)
			*(FirstTemp + i) = -1;
	}

	/*------------反向遍历-----------*/
	for (i = Length - 2; i >= 0; i--)
	{
		if (*(FirstTemp + i) == 0)
		{
			if (*(FirstTemp + i + 1) >= 0)
				*(FirstTemp + i) = 1;
			else if (*(FirstTemp + i + 1) < 0)
				*(FirstTemp + i) = -1;
		}
	}

	/*------------再次差分------------*/
	int* SecondTemp = new int[Length];//暂存2+++++++++++++2
	for (i = 0; i < Length - 2; i++)
		*(SecondTemp + i) = -(*(FirstTemp + i + 1) - *(FirstTemp + i)) / 2;

	delete[]FirstTemp;//--------1

	/*-------------向后移位------------*/
	for (i = Length - 2; i >= 0; i--)
	{
		*(SecondTemp + i) = *(SecondTemp + i - 1);
	}
	*(SecondTemp) = 1;//首尾先写2
	*(SecondTemp + Length - 1) = 1;



	/*-----先确定temp2中有多少非零值------*/
	int FengGuNum = 0;//非零点数即峰谷点个数
	int FengNum = 0;
	int GuNum = 0;
	int temp;
	for (i = 0; i < Length; i++)
	{
		if (*(SecondTemp + i) < 0)
		{
			GuNum++;//谷数
		}
		if (*(SecondTemp + i) > 0)
		{
			FengNum++;
		}
	}
	FengGuNum = GuNum + FengNum;

	int* TimeLabel = new int[FengGuNum];//++++++++++3
	int* Value = new int[FengGuNum];//+++++++++++++4
	int* FgLabel = new int[FengGuNum];//++++++++++++5

	/*-------保存峰谷数据-------*/
	for (int j = 0, i = 0; i < Length; i++)//时间标记从1开始计
	{
		if (*(SecondTemp + i) != 0)
		{
			*(TimeLabel + j) = i;//保存时间戳
			*(Value + j) = *(RawData + i);//保存载荷数据
			*(FgLabel + j) = *(SecondTemp + i);//保存区分峰谷（1和-1）
			j++;
		}
	}


	delete[]SecondTemp;//-----------2

	//保存
	RES.PVNum = FengGuNum;//峰谷总数
	RES.PNum = FengNum;//峰数
	RES.VNum = GuNum;//谷数
	RES.PVTime = TimeLabel;//时间戳
	RES.Value = Value;//载荷值
	RES.PVID = FgLabel;//峰谷标识

	cout << "第一次峰谷粗略提取，其中峰：" << RES.PNum << "个，谷：" << RES.VNum << "个，总：" << RES.PVNum << "个" << endl;

	//先返回后释放？？？
	return RES;

	delete[]TimeLabel;//-------------3
	delete[]Value;//-----------4
	delete[]FgLabel;//------------5
}

PeakVallyDef PVAdjust(PeakVallyDef FindRes)
{
	PeakVallyDef AdjustSave;

	PVCopy(&AdjustSave, FindRes);

	//判断峰谷总数奇偶性
	if (AdjustSave.PVNum % 2 == 0)//偶数，则去掉最后一个点
	{
		*(AdjustSave.PVTime + AdjustSave.PVNum) = 0;
		*(AdjustSave.Value + AdjustSave.PVNum) = 0;
		*(AdjustSave.PVID + AdjustSave.PVNum) = 0;
		AdjustSave.PVNum--;
	}


	//更新过后，修改首位峰谷标识符
	//前面首位已经写1了
	//但是现在考虑到首位和第二以及倒数第二的关系，如果第二及倒数第二是峰，那首位必是谷
	if (*(AdjustSave.PVID + 1) == 1)
	{
		*(AdjustSave.PVID) = -1;
	}
	if (*(AdjustSave.PVID + AdjustSave.PVNum - 2) == 1)
	{
		*(AdjustSave.PVID + AdjustSave.PVNum - 1) = -1;//注意下标问题
	}

	/*---下标 下标	*(p+0):首   *(p+i-1)：尾---*/


	//令首位值相同
	if (*(AdjustSave.PVID) == 1 && *(AdjustSave.PVID + AdjustSave.PVNum - 1) == 1)//都为峰,取首位最大值
	{
		*(AdjustSave.Value) = MyMax(*(AdjustSave.Value), *(AdjustSave.Value + AdjustSave.PVNum - 1));//首取最大的
	}

	if (*(AdjustSave.PVID) == -1 && *(AdjustSave.PVID + AdjustSave.PVNum - 1) == -1)//都为谷，取首位最小值
	{
		*(AdjustSave.Value) = MyMin(*(AdjustSave.Value), *(AdjustSave.Value + AdjustSave.PVNum - 1));//尾取最大的
	}
	*(AdjustSave.Value + AdjustSave.PVNum - 1) = *(AdjustSave.Value);//首值给尾


	//重新对峰、谷数计数
	AdjustSave.PNum = 0;
	AdjustSave.VNum = 0;

	for (int i = 0; i < AdjustSave.PVNum; i++)
	{
		if (*(AdjustSave.PVID + i) == 1)//谷
		{
			AdjustSave.PNum++;
		}
		else if (*(AdjustSave.PVID + i) == -1)//谷
		{
			AdjustSave.VNum++;
		}
	}
	AdjustSave.PVNum = AdjustSave.PNum + AdjustSave.VNum;


	//交换
	PVSweep(&AdjustSave);

	return AdjustSave;
}

Cou PVCount(PeakVallyDef Inp)
{
	PeakVallyDef Count;

	PVCopy(&Count, Inp);

	Cou Save;
	int* X = new int[Count.PVNum];
	int* Y = new int[Count.PVNum];
	//int* len = new int(0);

	int j = 0;
	int k = 0;
	for (int i = 0; i < Count.PVNum - 3; i++)
	{
		if (FourPoint(*(Count.Value + j), *(Count.Value + j + 1), *(Count.Value + j + 2), *(Count.Value + j + 3)))//满足判定条件
		{
			*(X + k) = k;
			*(Y + k) = 100*(i + (*(Count.Value + j + 2) - *(Count.Value + j)) / (*(Count.Value + j + 1) - *(Count.Value + j)));

			*(X + k + 1) = k + 1;
			*(Y + k + 1) = 100*(*(Count.Value + j + 2));
			j += 3;
			k += 2;
		}
		else
			j++;
	}
	Save.len = k;
	Save.X_Index = X;
	Save.Y_Index = Y;
	return Save;
	delete[]X;
	delete[]Y;
}

extern "C" __declspec(dllexport) void PV_For_Labview_DLL(int length, int* RawData, int* Data, int* time, int* Num, int* RealData, int* RealTime, int* RealNum, int* X, int* Y)
{
	PeakVallyDef ResF = PVFetch(RawData, length);

	for (int i = 0; i < ResF.PVNum; i++)//保存第一次粗略提取峰谷的数据
	{
		*(Data + i) = *(ResF.Value + i);//保存峰谷值
		*(time + i) = *(ResF.PVTime + i);//保存对应的时间戳
	}
	*Num = ResF.PVNum;

	PeakVallyDef ResA = PVAdjust(ResF);

	for (int i = 0; i < ResA.PVNum; i++)
	{
		*(RealData + i) = *(ResA.Value + i);
		*(RealTime + i) = i;
	}
	*RealNum = ResA.PVNum;

	Cou CN = PVCount(ResA);

	for (int i = 0; i < CN.len; i++)
	{
		*(X + i) = *(CN.X_Index + i);
		*(Y + i) = *(CN.Y_Index + i);
	}
}