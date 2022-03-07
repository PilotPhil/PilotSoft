#include"pch.h"
#include"DataJoin.h"


extern "C" __declspec(dllexport) void DataGroup(int Num, int* data,int *label)
{
	for (int i = 0; i < Num; i++)
	{
		*(label + i) = i;
	}
}