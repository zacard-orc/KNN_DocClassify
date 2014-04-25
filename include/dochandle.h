#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <limits>
#include <math.h>
#include <numeric>
#include <iomanip>
#include <algorithm>


#ifndef _DOCHANDLE_H_
#define _DOCHANDLE_H_



using namespace std;

void Wc(string ifn,string ofn);  //从分好词的原始文件中统计词频
void ReadWordCountFile(string ifn,int fid,int dsize);  //从有词频的文件中汇总成词频矩阵
void WcmPrint(string ofn);        //打印词频矩阵


#endif
