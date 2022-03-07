#include<iostream>
#include"rainnew.h"
#include"pch.h"

using namespace std;

int MyMax(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

int MyMin(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

void PV_Print(int* p, int len)
{
	for (int i = 0; i < len; i++)
		cout << *(p + i) << " ";
	cout << endl;
}

void PV_Test(Rain Inp)
{
	cout << endl;
	PV_Print(Inp.Value, Inp.PVn);
	PV_Print(Inp.ID, Inp.PVn);
}

Valid PV_NoSame(int* Inp, int len)
{
	int NewLen = len;
	int* ID = new int[len];
	Valid tr;

	for (int i = 0; i < len - 1; i++)
	{
		if (*(Inp + i) == *(Inp + i + 1))
		{
			*(ID + i) = 0;
			NewLen--;
		}
		else
			*(ID + i) = 1;

	}
	*(ID + len - 1) = 1;

	//cout << "newlen:" << NewLen;

	int* Save = new int[NewLen];
	for (int i = 0, j = 0; i < len; i++)
	{
		if (*(ID + i))
		{
			*(Save + j) = *(Inp + i);
			j++;
		}
	}
	delete[]ID;

	tr.Size = NewLen;
	tr.Value = Save;

	return tr;
	delete[]Save;
}

int PV_4Points(int a, int b, int c, int d)
{

	int temp1 = abs(a - b);
	int temp2 = abs(b - c);
	int temp3 = abs(c - d);

	if (temp1 >= temp2 && temp3 >= temp2)
		return 1;
	else
		return 0;
}

Rain PV_Extra(Valid Inp)
{
	int* PVID = new int[Inp.Size];

	int PVNUM = 2;
	for (int i = 1; i < Inp.Size - 1; i++)//峰谷标识写入
	{
		if (*(Inp.Value + i) > * (Inp.Value + i - 1) && *(Inp.Value + i) > * (Inp.Value + i + 1))
		{
			*(PVID + i) = 1;
			PVNUM++;
		}
		else if (*(Inp.Value + i) < *(Inp.Value + i - 1) && *(Inp.Value + i) < *(Inp.Value + i + 1))
		{
			*(PVID + i) = -1;
			PVNUM++;
		}
		else
			*(PVID + i) = 0;
	}
	*(PVID) = 2;//首位需保存 先写2
	*(PVID + Inp.Size - 1) = 2;

	int* value = new int[PVNUM];//存储值
	int* newID = new int[PVNUM];//存储峰谷判断标志

	for (int i = 0, j = 0; i < Inp.Size; i++)//根据峰谷标识写入峰谷值
	{
		if (*(PVID + i) != 0)
		{
			*(value + j) = *(Inp.Value + i);
			*(newID + j) = *(PVID + i);
			j++;
			//cout << "test:" <<* (Inp.pin + i);
		}
	}
	*(newID) = -*(newID + 1);
	*(newID + PVNUM - 1) = -*(newID + PVNUM - 2);



	Rain sth;//
	sth.PVn = PVNUM;
	sth.Value = value;
	sth.ID = newID;
	return sth;
	delete[]value;
	delete[]PVID;
}

Rain PV_Adjust(Rain Inp)
{
	int newlen = 0;
	if (Inp.PVn % 2 == 0)//峰谷总数为偶数 则去掉最后一个
		newlen = Inp.PVn - 1;
	else
		newlen = Inp.PVn;

	int* newvalue = new int[newlen];
	int* newID = new int[newlen];

	for (int i = 0; i < newlen; i++)//拷贝
	{
		*(newvalue + i) = *(Inp.Value + i);
		*(newID + i) = *(Inp.ID + i);
	}

	if (*(newID) == 1)//首位值取较大的或者较小的
	{
		*(newvalue) = *(newvalue + newlen - 1) = MyMax(*(newvalue), *(newvalue + newlen - 1));
	}
	if (*(newID) == -1)
	{
		*(newvalue) = *(newvalue + newlen - 1) = MyMin(*(newvalue), *(newvalue + newlen - 1));
	}

	Rain sth;
	sth.ID = newID;
	sth.PVn = newlen;
	sth.Value = newvalue;

	return sth;

	delete[]newvalue;
	delete[]newID;

}

Rain PV_Sweep(Rain Inp)
{

	int Value = abs(*(Inp.Value));
	int position = 0;

	for (int i = 0; i < Inp.PVn; i++)
	{
		if (abs(*(Inp.Value + i)) <= Value)
		{
			Value = abs(*(Inp.Value + i));//找到一个更小的，赋值给临时变量
			position = i;//并且保存下标
		}
	}

	position++;

	int j = 0;//索引
	int* TempValue = new int[Inp.PVn]();
	int* TempID = new int[Inp.PVn]();

	for (int i = position - 1; i < Inp.PVn; i++, j++)//将后部分赋值给Temp
	{
		//注：j从0开始 下标没有错误
		*(TempValue + j) = *(Inp.Value + i);
		*(TempID + j) = *(Inp.ID + i);
	}

	for (int i = 1; i < position; i++, j++)//将前部分赋值给Temp
	{
		*(TempValue + j) = *(Inp.Value + i);
		*(TempID + j) = *(Inp.ID + i);
	}

	Rain sth;
	sth.PVn = Inp.PVn;
	sth.ID = TempID;
	sth.Value = TempValue;

	return sth;

	delete[]TempValue;
	delete[]TempID;
}

TR PV_Count(Rain Inp)
{
	int* ave = new int[Inp.PVn+4];
	int* amp = new int[Inp.PVn+4];

	int i = 0;
	int num = 1;
	while (i < Inp.PVn - 3)
	{
		if (PV_4Points(*(Inp.Value + i), *(Inp.Value + i + 1), *(Inp.Value + i + 2), *(Inp.Value + i + 3)))
		{
			//均值
			*(ave + i) = 0;
			*(ave + i + 1)= *(ave + i + 2) = *(Inp.Value + i + 1) + *(Inp.Value + i + 2);

			//幅值
			*(amp + i) = 0;
			*(amp + i + 1) = *(amp + i + 2) = abs(*(Inp.Value + i + 1) - *(Inp.Value + i + 2));

			i+=3;
			num += 3;
		}
		else
		{
			*(ave + i) = 0;
			*(amp + i) = 0;

			i++;
			num++;
		}
	}

	//cout << "end:" << *(Inp.Value + i) << endl;
	//cout << "Label:" << i << "   " << "num:" << num << endl;

	if (i==Inp.PVn-1)
	{
		//cout << "完整计数，不需要补数" << endl;
	}
	else
	{
		//cout << "非完整计数，需要补数" << endl;
		if (i == Inp.PVn - 3)
		{
			if (PV_4Points(*(Inp.Value + i), *(Inp.Value + i + 1), *(Inp.Value + i + 2), *(Inp.Value)))
			{
				//均值
				*(ave + i) = 0;
				*(ave + i + 1) = *(ave + i + 2) = *(Inp.Value + i + 1) + *(Inp.Value + i + 2);
				
				//幅值
				*(amp + i) = 0;
				*(amp + i + 1) = *(amp + i + 2) = abs(*(Inp.Value + i + 1) - *(Inp.Value + i + 2));

				num += 3;
			}
			else
			{
				*(ave + i) = *(ave + i + 1) = *(ave + i + 2) = *(ave + i + 3) = 0;

				*(amp + i) = *(amp + i + 1) = *(amp + i + 2) = *(amp + i + 3) = 0;
				num += 3;
			}
		}
		if (i == Inp.PVn - 2)
		{
			if (PV_4Points(*(Inp.Value + i), *(Inp.Value + i + 1), *(Inp.Value), *(Inp.Value + 1)))
			{
				*(ave + i) = 0;
				*(ave + i + 1) = *(ave + i + 2) = *(Inp.Value + i + 1) + *(Inp.Value);
				
				*(amp + i) = 0;
				*(amp + i + 1) = *(amp + i + 2) = abs(*(Inp.Value + i + 1) - *(Inp.Value));


				num += 3;
			}
			else
			{
				*(ave + i) = *(ave + i + 1) = *(ave + i + 2) = *(ave + i + 3) = 0;
				
				*(amp + i) = *(amp + i + 1) = *(amp + i + 2) = *(amp + i + 3) = 0;

				
				num += 3;
			}
		}
	}

	//cout << "new:::" << num << endl;

	TR sth;
	sth.size = num;
	sth.Ave = ave;
	sth.Amp = amp;
	return sth;
	delete[]ave;
	delete[]amp;
}

extern "C" __declspec(dllexport) void for_labview
(
	int LenRawData, int* RawData,//原始数据及长度
	int* time,//时间戳
	int* Extra, int* LenExtra,//提取峰谷数据和长度
	int* Adjust, int* LenAdjust,//载荷历程调整数据和长度
	int* Amp, int* Avg, int* LenCount//幅值 均值 和长度
)
{
	for (int i = 0; i < LenRawData; i++)
		*(time + i) = i;

	Valid a = PV_NoSame(RawData, LenRawData);//剔除重复数据

	//提取峰谷
	Rain b = PV_Extra(a);

	for (int i = 0; i < b.PVn; i++)//幅值峰谷数据
		*(Extra + i) = *(b.Value + i);

	*LenExtra = b.PVn;//保存峰谷个数

	//载荷历程调整
	Rain c = PV_Adjust(b);
	Rain d = PV_Sweep(c);

	*LenAdjust = d.PVn;//保存调整后个数

	for (int i = 0; i < d.PVn; i++)//保存调整后的值
		*(Adjust + i) = *(d.Value + i);

	//四点计数
	TR e = PV_Count(d);
	*LenCount = e.size;
	for (int i = 0; i < e.size; i++)
	{
		*(Amp + i) = *(e.Amp + i);
		*(Avg + i) = *(e.Ave + i);
	}
}