#include "dochandle.h"


using namespace std;


const int FLDNUM=200;   			//一行内有N个单词
map<string,vector<int> > map_wc;    //每个单词的红黑树统计


void Wc(string ifn,string ofn)        //从分好词的原始文件中统计词频
{
   //ifn 输入的文件名
   //ofn 输出的文件名
   ifstream ifs;
   ofstream ofs(ofn.c_str());  //入参为char*


   string line;
   ifs.open(ifn.c_str());
   
   cout<<"Handleing Doc: "<<ifn<<endl;

   map<string,int> map_wc;
   while(getline(ifs,line))
   {
	 //cout<<line<<endl;
     istringstream strstm(line);
	 string str[FLDNUM];
	 for(int i=0;i<FLDNUM;i++)
	 {
        strstm>>str[i];
		if(str[i].length())
		{
			 map_wc[str[i]]++;
    	}
	 }
   }
   
   map<string,int>::iterator it_wc;
   for(it_wc=map_wc.begin();it_wc!=map_wc.end();it_wc++)
   {
	  //cout<<it_wc->first<<" "<<it_wc->second<<endl;
	  ofs<<it_wc->first<<" "<<it_wc->second<<endl;
   }
   map_wc.clear();
   ifs.close();
   ofs.close();
};

void ReadWordCountFile(string ifn,int fid,int dsize)  //从有词频的文件中汇总成词频矩阵
{
   //ifn 输入的文件名
   //ofn 输出的文件名
   ifstream ifs;
   string line;
   ifs.open(ifn.c_str());

   while(getline(ifs,line))
   {
		
	   istringstream strstm(line);
       string str[2];
       strstm>>str[0]>>str[1];
       //该word之前的向量如果没有初始化过，先初始化一下
       if(map_wc[str[0]].size()==0)
       {
			map_wc[str[0]].resize(dsize);
       }
       map_wc[str[0]][fid]+=atoi(str[1].c_str());
   }

   ifs.close();
};


void WcmPrint(string ofn)
{
	ofstream ofs(ofn.c_str());
    map<string,vector<int> >::iterator wc_it;
	vector<int>::iterator wcv_it;
    for(wc_it=map_wc.begin();wc_it!=map_wc.end();wc_it++)
    {
	    //cout<<wc_it->first<<" "<<wc_it->second[0]<<endl;
		cout<<wc_it->first<<" ";
		ofs<<wc_it->first<<" ";
		for(wcv_it=wc_it->second.begin();wcv_it!=wc_it->second.end();wcv_it++)
		{
		   cout<<*wcv_it<<" ";
		   ofs<<*wcv_it<<" ";
		}
		cout<<endl;
		ofs<<endl;
    }

};



