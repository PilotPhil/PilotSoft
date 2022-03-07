#include"RAIN.h"

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

int* Diff(int* Inp, int len)
{
	int* DiffRes = new int[len];
	for (int i = 0; i < len - 1; i++)
	{
		DiffRes[i] = Inp[i + 1] - Inp[i];
	}
	return DiffRes;
	delete[]DiffRes;
}

void Judge(int* Inp, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (Inp[i] > 0)
		{
			Inp[i] = 1;
		}
		else if (Inp[i] < 0)
		{
			Inp[i] = -1;
		}
	}
}

void RevJudge(int* Inp, int len)
{
	for (int i = len - 2; i >= 0; i--)
	{
		if (*(Inp + i) == 0)
		{
			if (*(Inp + i + 1) >= 0)
				Inp[i] = 1;
			else if (*(Inp + i + 1) < 0)
				Inp[i] = -1;
		}
	}
}

void MoveBack(int* Inp, int len)
{
	for (int i = len - 2; i > 0; i--)
	{
		*(Inp + i) = *(Inp + i - 1);
	}

	//��β�޸�
	*(Inp) = 2;
	*(Inp + len - 1) = 2;
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

PeakVallyDef PVFetch(int* RawData, int len)
{
	PeakVallyDef RES;//ʵ�������������

	int* temp1 = Diff(RawData, len);//��һ�β��

	Judge(temp1, len);//ȡ��������

	RevJudge(temp1, len);//�������

	int* Temp2 = Diff(temp1, len);//�ڶ��β��

	MoveBack(Temp2, len);//�����λ



	/*-----ȷ��temp2���ж��ٷ���ֵ------*/
	int PVNum = 0;//�����������ȵ����
	int PNum = 0;
	int VNum = 0;
	int temp;
	for (int i = 0; i < len; i++)
	{
		if (*(Temp2 + i))
		{
			PVNum++;//����
		}
	}
	int* Tim = new int[PVNum];//++++++++++3
	int* Value = new int[PVNum];//+++++++++++++4
	int* PVID = new int[PVNum];//++++++++++++5

	/*-------����������-------*/
	for (int j = 0, i = 0; i < len; i++)//ʱ���Ǵ�1��ʼ��
	{
		if (*(Temp2 + i) != 0)
		{
			*(Tim + j) = i;//����ʱ���
			*(Value + j) = *(RawData + i);//�����غ�����
			*(PVID + j) = *(Temp2 + i);//�������ַ�ȣ�1��-1��
			j++;
		}
	}


	//����
	RES.PVNum = PVNum;//�������
	RES.PNum = PNum;//����
	RES.VNum = VNum;//����
	RES.PVTime = Tim;//ʱ���
	RES.Value = Value;//�غ�ֵ
	RES.PVID = PVID;//��ȱ�ʶ

	cout << "��һ�η�ȴ�����ȡ�����з壺" << RES.PNum << "�����ȣ�" << RES.VNum << "�����ܣ�" << RES.PVNum << "��" << endl;

	//�ȷ��غ��ͷţ�����
	return RES;

	delete[]Tim;//-------------3
	delete[]Value;//-----------4
	delete[]PVID;//------------5
}

void PVFind(int* Inp, int len)
{
	int* PVID = new int[len]();
	for (int i = 1; i < len-1; i++)
	{
		if (*(Inp + i) > * (Inp + i - 1) && *(Inp + i) > * (Inp + i + 1))
			*(PVID + i) = 1;
		else if (*(Inp + i) < *(Inp + i - 1) && *(Inp + i) < *(Inp + i + 1))
			*(PVID + i) = -1;
		else
			*(PVID + i) = 0;
	}

	*(PVID) = -*(PVID + 1);
	*(PVID + len - 1) = -*(PVID + len - 2);

	for (int i = 0; i < len; i++)
	{
		cout << *(PVID + i) << "   ";
	}
	
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

//Full PVCount(PeakVallyDef INP)
//{
//
//}

void PV_For_Labview_DLL(int* RawData, int length, int* Data, int* time, int* Num, int* RealData, int* RealTime, int* RealNum)
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


}