#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <numeric>
#include <tuple>
#include <iomanip>
#include <algorithm>

#ifndef _DVM_H_
#define _DVM_H_

#define DBM numeric_limits<double>::min()

using namespace std;


typedef struct
{
	string word;
	vector<float> wc;            //wordcount matrix ����*�ĵ� Ƶ�ξ���
	float wcount;           //����word���ĵ���
	vector<float> wc_class;      //ĳ��[C[X]]����word���ĵ���
	float pw;		        //����word���ĵ�ռȫ���ĵ��ı���
	vector<float> pcw;		    //ĳ��[C[X]]����word���ĵ���ռ�ܳ���word���ĵ����ı���
	vector<float> pcwb;   		//ĳ��[C[X]]û�г���word���ĵ���ռ��û�г���word���ĵ����ı���
	double ig;
} igmatrix_t;

typedef struct            //IG������ṹ��
{
	string word;
	double ig;
	double ni;
} feature_t;

typedef struct		       //�ĵ�����������ṹ��
{
	vector<double> tf;    //div
	vector<double> v;
	vector<double> ev;
	vector<int> ssss;
	double vmodle;
} dvm_t;

typedef pair<string,double> PAIR;


int  ReadMatrix(string ifn,int clsize,int dsize);          //��ȡ��Ƶ����WordCountMatrix
void CreateDCIndex(string ifn);       //���� �����ĵ���ӳ���ϵ
/*�������������
* ����1:������ļ���
* ����2:��Ϣ�������IG�ļ�¼��
* ����3:����
* ����4:ÿ������ĵ���
* ����5:������ά��
*/
void ComputerIgm(string ofn,int IGM_CC,int clsize,int dcnum,int div);    

void ReadFeatures(string ifn,int div);  //��ȡIG���������
void ComputeDVM(int DCNUM,int div);  //�����ĵ���λ����
void PrintAll(string ofn,int DCNUM,int div);  //��ӡ�ĵ�����
void ReadTDVM(string ifn,int div);            //��ȡ�ĵ�����
void ConvertTest(string ifn,int DCNUM,int div);		  //�������ĵ�ת���ɲ�������

double ComputeE(double x[],int div);          //��λ���������������
double Cos(double a[],double b[],int div);     //����COS

int cmp(const PAIR& x,const PAIR&y);  //����sort��>����
int Test(vector<double> &x,int KNN,int div);          //�Ѳ����ĵ�������������KNN������ھӽ��в���



#endif