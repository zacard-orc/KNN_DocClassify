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
	vector<float> wc;            //wordcount matrix 单词*文档 频次矩阵
	float wcount;           //出现word的文档数
	vector<float> wc_class;      //某类[C[X]]出现word的文档数
	float pw;		        //出现word的文档占全部文档的比重
	vector<float> pcw;		    //某类[C[X]]出现word的文档数占总出现word的文档数的比重
	vector<float> pcwb;   		//某类[C[X]]没有出现word的文档数占总没有出现word的文档数的比重
	double ig;
} igmatrix_t;

typedef struct            //IG特征项结构体
{
	string word;
	double ig;
	double ni;
} feature_t;

typedef struct		       //文档向量特征项结构体
{
	vector<double> tf;    //div
	vector<double> v;
	vector<double> ev;
	vector<int> ssss;
	double vmodle;
} dvm_t;

typedef pair<string,double> PAIR;


int  ReadMatrix(string ifn,int clsize,int dsize);          //读取词频矩阵WordCountMatrix
void CreateDCIndex(string ifn);       //创建 类与文档的映射关系
/*创建特征项矩阵
* 参数1:输出的文件名
* 参数2:信息增益矩阵IG的记录数
* 参数3:类数
* 参数4:每个类的文档数
* 参数5:特征项维度
*/
void ComputerIgm(string ofn,int IGM_CC,int clsize,int dcnum,int div);    

void ReadFeatures(string ifn,int div);  //读取IG特征项矩阵
void ComputeDVM(int DCNUM,int div);  //计算文档单位矩阵
void PrintAll(string ofn,int DCNUM,int div);  //打印文档向量
void ReadTDVM(string ifn,int div);            //读取文档向量
void ConvertTest(string ifn,int DCNUM,int div);		  //将测试文档转换成测试向量

double ComputeE(double x[],int div);          //求单位向量，入参是数组
double Cos(double a[],double b[],int div);     //计算COS

int cmp(const PAIR& x,const PAIR&y);  //重载sort的>函数
int Test(vector<double> &x,int KNN,int div);          //把测试文档的向量传入与KNN最近的邻居进行测试



#endif