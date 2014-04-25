#include "dochandle.h"


using namespace std;


const int FLDNUM=200;   			//һ������N������
map<string,vector<int> > map_wc;    //ÿ�����ʵĺ����ͳ��


void Wc(string ifn,string ofn)        //�ӷֺôʵ�ԭʼ�ļ���ͳ�ƴ�Ƶ
{
   //ifn ������ļ���
   //ofn ������ļ���
   ifstream ifs;
   ofstream ofs(ofn.c_str());  //���Ϊchar*


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

void ReadWordCountFile(string ifn,int fid,int dsize)  //���д�Ƶ���ļ��л��ܳɴ�Ƶ����
{
   //ifn ������ļ���
   //ofn ������ļ���
   ifstream ifs;
   string line;
   ifs.open(ifn.c_str());

   while(getline(ifs,line))
   {
		
	   istringstream strstm(line);
       string str[2];
       strstm>>str[0]>>str[1];
       //��word֮ǰ���������û�г�ʼ�������ȳ�ʼ��һ��
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



