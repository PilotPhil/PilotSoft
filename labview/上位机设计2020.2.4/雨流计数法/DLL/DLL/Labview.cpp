#include"labview.h"
#include"pch.h"
#include"rainnew.h"

extern "C" __declspec(dllexport) void for_labview
(	
	int LenRawData, int* RawData,//ԭʼ���ݼ�����
	int* time,//ʱ���
	int* Extra, int* LenExtra,//��ȡ������ݺͳ���
	int* Adjust, int* LenAdjust,//�غ����̵������ݺͳ���
	int* Amp,int* Avg,int* LenCount//��ֵ ��ֵ �ͳ���
)
{
	for (int i = 0; i < LenRawData; i++)
		*(time + i) = i;

	Valid a = PV_NoSame(RawData, LenRawData);//�޳��ظ�����

	//��ȡ���
	Rain b = PV_Extra(a);

	for (int i = 0; i < b.PVn; i++)//��ֵ�������
		*(Extra + i) = *(b.Value + i);

	*LenExtra = b.PVn;//�����ȸ���

	//�غ����̵���
	Rain c = PV_Adjust(b);
	Rain d = PV_Sweep(c);

	*LenAdjust = d.PVn;//������������

	for (int i = 0; i < d.PVn; i++)//����������ֵ
		*(Adjust + i) = *(d.Value + i);

	//�ĵ����
	TR e = PV_Count(d);
	*LenCount = e.size;
	for (int i = 0; i < e.size; i++)
	{
		*(Amp + i) = *(e.Amp + i);
		*(Avg + i) = *(e.Ave + i);
	}
}