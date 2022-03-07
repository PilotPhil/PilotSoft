#include"labview.h"
#include"pch.h"
#include"rainnew.h"

extern "C" __declspec(dllexport) void for_labview
(	
	int LenRawData, int* RawData,//原始数据及长度
	int* time,//时间戳
	int* Extra, int* LenExtra,//提取峰谷数据和长度
	int* Adjust, int* LenAdjust,//载荷历程调整数据和长度
	int* Amp,int* Avg,int* LenCount//幅值 均值 和长度
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