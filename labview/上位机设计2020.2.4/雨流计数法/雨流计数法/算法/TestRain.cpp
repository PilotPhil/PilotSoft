#include<iostream>
#include<time.h>
#include<math.h>
#include"rainnew.h"
#define rand(x) rand()%x//随机种子
using namespace std;
int main()
{
	//FILE* fp = NULL;
	//fp = fopen("C:\\Users\\63291\\Desktop\\test.xls","w");
	//int RawData[] = 
	//{ 69,5,-28,-77,-77,96,-63,33,10,-25,-29,
	//	-45,46,-44,-12,-32,-11,-97,-91,22,
	//	-87,86,-27,-57,-79,-26,-22,24 };
	//int len = sizeof(RawData) / sizeof(RawData[0]);
	//DataOk a = PV_NoSame(RawData, len);
	//Rain b = PV_Extra(a);
	////PV_Test(b);
	//Rain c = PV_Adjust(b);
	////PV_Test(c);
	//Rain d = PV_Sweep(c);
	////PV_Test(d);
	//cout << "有效个数：：：" << d.PVn << endl;
	//TR e = PV_Count(d);
	////PV_Print(e.Ave, e.size);
	////PV_Print(e.Amp, e.size);

	//fprintf(fp, "时间\t原始数据\t提取峰谷值\t载荷历程调整\t幅值\t均值\n");

	//for (int i = 0; i < len; i++)
	//	fprintf(fp, "%d\t%d\t%d\t%d\t%d\t%d\n", i, RawData[i], *(b.Value + i), *(d.Value + i), *(e.Amp + i), *(e.Ave + i));

	//fclose(fp);

	//return 1;
}
