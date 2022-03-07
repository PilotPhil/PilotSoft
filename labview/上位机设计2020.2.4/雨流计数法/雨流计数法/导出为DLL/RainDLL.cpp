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
			*Value = abs(*(adj.Value + i));//�ҵ�һ������ģ���ֵ����ʱ����
			*Index = i;//���ұ����±�
		}
	}

	return (*Index) + 1;//�������ֵ���ڵ��±�+1

	delete Value;//-------1
	delete Index;//-------2
}

void PVSweep(PeakVallyDef* adj)
{
	int IndexMin = PVFindMin(*adj);

	//��ǰ��ͺ�뽻��λ�ò����
	//ǰ�󶼰������ֵ
	//������λֵ��ȣ�����ƴ��ʱʡ��һ���㣨ʡ�� ͷֵ��
	//ͷβƴ����Temp

	int j = 0;//����
	int* TempValue = new int[adj->PVNum]();//��̬�ڴ���䲢��ʼ����С����
	int* TempIndex = new int[adj->PVNum]();//��̬�ڴ���䲢��ʼ����С����
	int* TempID = new int[adj->PVNum]();//��̬�ڴ���䲢��ʼ����С����

	for (int i = IndexMin - 1; i < adj->PVNum; i++, j++)//���󲿷ָ�ֵ��Temp
	{
		//ע��j��0��ʼ �±�û�д���
		*(TempIndex + j) = *(adj->PVTime + i);
		*(TempValue + j) = *(adj->Value + i);
		*(TempID + j) = *(adj->PVID + i);
	}

	for (int i = 1; i < IndexMin; i++, j++)//��ǰ���ָ�ֵ��Temp
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
	PeakVallyDef RES;//ʵ�������������

	int i = 0;

	/*----------��һ�β��----------*/
	int* FirstTemp = new int[Length - 1];//�ݴ�+++++++++++1
	for (i = 0; i < Length - 1; i++)
	{
		*(FirstTemp + i) = *(RawData + i + 1) - *(RawData + i);
		//ȡ��������
		if (*(FirstTemp + i) > 0)
			*(FirstTemp + i) = 1;
		else if (*(FirstTemp + i) < 0)
			*(FirstTemp + i) = -1;
	}

	/*------------�������-----------*/
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

	/*------------�ٴβ��------------*/
	int* SecondTemp = new int[Length];//�ݴ�2+++++++++++++2
	for (i = 0; i < Length - 2; i++)
		*(SecondTemp + i) = -(*(FirstTemp + i + 1) - *(FirstTemp + i)) / 2;

	delete[]FirstTemp;//--------1

	/*-------------�����λ------------*/
	for (i = Length - 2; i >= 0; i--)
	{
		*(SecondTemp + i) = *(SecondTemp + i - 1);
	}
	*(SecondTemp) = 1;//��β��д2
	*(SecondTemp + Length - 1) = 1;



	/*-----��ȷ��temp2���ж��ٷ���ֵ------*/
	int FengGuNum = 0;//�����������ȵ����
	int FengNum = 0;
	int GuNum = 0;
	int temp;
	for (i = 0; i < Length; i++)
	{
		if (*(SecondTemp + i) < 0)
		{
			GuNum++;//����
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

	/*-------����������-------*/
	for (int j = 0, i = 0; i < Length; i++)//ʱ���Ǵ�1��ʼ��
	{
		if (*(SecondTemp + i) != 0)
		{
			*(TimeLabel + j) = i;//����ʱ���
			*(Value + j) = *(RawData + i);//�����غ�����
			*(FgLabel + j) = *(SecondTemp + i);//�������ַ�ȣ�1��-1��
			j++;
		}
	}


	delete[]SecondTemp;//-----------2

	//����
	RES.PVNum = FengGuNum;//�������
	RES.PNum = FengNum;//����
	RES.VNum = GuNum;//����
	RES.PVTime = TimeLabel;//ʱ���
	RES.Value = Value;//�غ�ֵ
	RES.PVID = FgLabel;//��ȱ�ʶ

	cout << "��һ�η�ȴ�����ȡ�����з壺" << RES.PNum << "�����ȣ�" << RES.VNum << "�����ܣ�" << RES.PVNum << "��" << endl;

	//�ȷ��غ��ͷţ�����
	return RES;

	delete[]TimeLabel;//-------------3
	delete[]Value;//-----------4
	delete[]FgLabel;//------------5
}

PeakVallyDef PVAdjust(PeakVallyDef FindRes)
{
	PeakVallyDef AdjustSave;

	PVCopy(&AdjustSave, FindRes);

	//�жϷ��������ż��
	if (AdjustSave.PVNum % 2 == 0)//ż������ȥ�����һ����
	{
		*(AdjustSave.PVTime + AdjustSave.PVNum) = 0;
		*(AdjustSave.Value + AdjustSave.PVNum) = 0;
		*(AdjustSave.PVID + AdjustSave.PVNum) = 0;
		AdjustSave.PVNum--;
	}


	//���¹����޸���λ��ȱ�ʶ��
	//ǰ����λ�Ѿ�д1��
	//�������ڿ��ǵ���λ�͵ڶ��Լ������ڶ��Ĺ�ϵ������ڶ��������ڶ��Ƿ壬����λ���ǹ�
	if (*(AdjustSave.PVID + 1) == 1)
	{
		*(AdjustSave.PVID) = -1;
	}
	if (*(AdjustSave.PVID + AdjustSave.PVNum - 2) == 1)
	{
		*(AdjustSave.PVID + AdjustSave.PVNum - 1) = -1;//ע���±�����
	}

	/*---�±� �±�	*(p+0):��   *(p+i-1)��β---*/


	//����λֵ��ͬ
	if (*(AdjustSave.PVID) == 1 && *(AdjustSave.PVID + AdjustSave.PVNum - 1) == 1)//��Ϊ��,ȡ��λ���ֵ
	{
		*(AdjustSave.Value) = MyMax(*(AdjustSave.Value), *(AdjustSave.Value + AdjustSave.PVNum - 1));//��ȡ����
	}

	if (*(AdjustSave.PVID) == -1 && *(AdjustSave.PVID + AdjustSave.PVNum - 1) == -1)//��Ϊ�ȣ�ȡ��λ��Сֵ
	{
		*(AdjustSave.Value) = MyMin(*(AdjustSave.Value), *(AdjustSave.Value + AdjustSave.PVNum - 1));//βȡ����
	}
	*(AdjustSave.Value + AdjustSave.PVNum - 1) = *(AdjustSave.Value);//��ֵ��β


	//���¶Է塢��������
	AdjustSave.PNum = 0;
	AdjustSave.VNum = 0;

	for (int i = 0; i < AdjustSave.PVNum; i++)
	{
		if (*(AdjustSave.PVID + i) == 1)//��
		{
			AdjustSave.PNum++;
		}
		else if (*(AdjustSave.PVID + i) == -1)//��
		{
			AdjustSave.VNum++;
		}
	}
	AdjustSave.PVNum = AdjustSave.PNum + AdjustSave.VNum;


	//����
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
		if (FourPoint(*(Count.Value + j), *(Count.Value + j + 1), *(Count.Value + j + 2), *(Count.Value + j + 3)))//�����ж�����
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

	for (int i = 0; i < ResF.PVNum; i++)//�����һ�δ�����ȡ��ȵ�����
	{
		*(Data + i) = *(ResF.Value + i);//������ֵ
		*(time + i) = *(ResF.PVTime + i);//�����Ӧ��ʱ���
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