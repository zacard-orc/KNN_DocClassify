#include "dvm.h"

using namespace std;

map<string,double> map_feat;  //特征项IG
map<int,vector<int> > map_cd; //类与文档索引的关系
map<string,int> map_wr;       //word与IGM记录数的映射关系
map<string,int> map_test;   //测试文档的快速建树


//int IGM_CC=0;                 //计算特种项的记录数
//double DCNUM=6;               //定义文档总数
//double CLASSNUM=2;			  //定义类的总数
//double CATNUM=DCNUM/CLASSNUM; //定义每个类有多少文档
//double ENY=log(2);            //初始嫡
//int WCM_NUM=100;			  //词频矩阵总行数
//int DIV=6;                    //设定有价值的信息增益维度

igmatrix_t igm[9999];          //信息增益类型和初始变量数
feature_t feat[9999];            //IG特征项
dvm_t dvm[9999];           	  //文档向量定义
dvm_t dvm_test;		   //测试的向量结构体


int ReadMatrix(string ifn,int clsize,int dsize)
{
   //ifn 输入的文件名
   //ofn 输出的文件名
   ifstream ifs;
   string line;
   ifs.open(ifn.c_str());
   int j=0;

   while(getline(ifs,line))
   {
	  // cout<<line<<endl;
	   istringstream strstm(line);
	   string str[dsize+1];
	   int i=0;
	   //打散split数据
	   while(strstm>>str[i])
	   { 
		   i++;
	   }
	   //cout<<str[1]<<endl;
	   //初始化vector空间
	   igm[j].wc.resize(dsize);
	   igm[j].wc_class.resize(clsize);
	   igm[j].pcw.resize(clsize);
	   igm[j].pcwb.resize(clsize);


	   igm[j].word=str[0];
	   //igm赋值
	   map_wr[igm[j].word]=j;
	   for(i=1;i<dsize+1;i++)
	   {
		  igm[j].wc[i-1]=atoi(str[i].c_str());
		 // cout<<igm[j].wc[i-1]<<endl;
	   }

	   j++;
   }

   ifs.close();
   return j;
};


void CreateDCIndex(string ifn)
{
	 ifstream ifs;
     string line;
     ifs.open(ifn.c_str());
	 while(getline(ifs,line))
	 {
	   istringstream strstm(line);
	   string str[3];
	   strstm>>str[0]>>str[1]>>str[2];
	   map_cd[atoi(str[0].c_str())].push_back(atoi(str[1].c_str()));
       map_cd[atoi(str[0].c_str())].push_back(atoi(str[2].c_str()));

	 }
	//第一个值是起点，第二个值是终点
	/*
	map_cd[0].push_back(0);
	map_cd[0].push_back(2);
	map_cd[1].push_back(3);
	map_cd[1].push_back(5);
	*/

};



void ComputerIgm(string ofn,int IGM_CC,int clsize,int dcnum,int div)
{
	double CATNUM=dcnum/clsize;
	double ENY=log(clsize);

	map<int,vector<int> >::iterator it_cd;
	//vector<float>::iterator it_float;
	ofstream ofs(ofn.c_str());
	//cout<<"word\twc  wc_class\t  pw\t\t\tpcw\t\t     pcwb\t\td\t\t   ig"<<endl;
	for(int i=0;i<IGM_CC;i++)
	{
	    
		//cout<<setw(3)<<left<<igm[i].word<<" ";
		//计算WC 
		igm[i].wcount=accumulate(igm[i].wc.begin(),igm[i].wc.begin()+dcnum,0);
		//cout<<setw(3)<<right<<igm[i].wcount<<" ";

		//计算WC_CLASS
	    for(it_cd=map_cd.begin();it_cd!=map_cd.end();it_cd++)
	    {
	       igm[i].wc_class[it_cd->first]=accumulate(igm[i].wc.begin()+it_cd->second[0],igm[i].wc.begin()+it_cd->second[1]+1,0);
		   //cout<<setw(6)<<igm[i].wc_class[it_cd->first]<<" ";
	    }
		//计算PW
		igm[i].pw=igm[i].wcount/(float)dcnum;
		//cout<<setw(10)<<igm[i].pw<<" ";
		//计算PCW
		for(it_cd=map_cd.begin();it_cd!=map_cd.end();it_cd++)
		{
				igm[i].pcw[it_cd->first]=igm[i].wc_class[it_cd->first]/igm[i].wcount;
				igm[i].pcwb[it_cd->first]=(CATNUM-igm[i].wc_class[it_cd->first])/(dcnum-igm[i].wcount);
				//cout<<setw(10)<<igm[i].pcw[it_cd->first]<<" ";
		}
		for(it_cd=map_cd.begin();it_cd!=map_cd.end();it_cd++)
		{
			//cout<<setw(10)<<igm[i].pcwb[it_cd->first]<<" ";	
		}
		//计算D/嫡
		double d1=0,d2=0;
		for(it_cd=map_cd.begin();it_cd!=map_cd.end();it_cd++)
		{
			d1+=log(igm[i].pcw[it_cd->first]+DBM)*igm[i].pcw[it_cd->first];
			d2+=log(igm[i].pcwb[it_cd->first]+DBM)*igm[i].pcwb[it_cd->first];
		}
		//cout<<setw(10)<<d1<<setw(13)<<d2;
		double ig=0;
		//计算IG
		ig=ENY+igm[i].pw*d1+(1-igm[i].pw)*d2;
		//cout<<setw(13)<<ig<<endl;
		//存入IG特征MAP
		map_feat[igm[i].word]=ig;
		//ofs<<igm[i].word<<" "<<map_feat[igm[i].word]<<endl;
		//MAP按VALUE排序
		vector<PAIR> vec; 
		map<int,double>::iterator it_mapfeat;
	}  
	vector<PAIR> vec;
	map<string,double>::iterator it_mapfeat;
	for(it_mapfeat=map_feat.begin();it_mapfeat!=map_feat.end();it_mapfeat++)
	{
		vec.push_back(make_pair(it_mapfeat->first,it_mapfeat->second));  	
	}
	sort(vec.begin(),vec.end(),cmp); 
	vector<PAIR>::iterator it_vv;
	cout<<endl;
	//打印IG向量
	for(it_vv=vec.begin();it_vv!=vec.end();it_vv++)
	{
		//cout<<it_vv->first<<":"<<it_vv->second<<":"<<igm[map_wr[it_vv->first]].wcount<<endl;	
		ofs<<it_vv->first<<" "<<it_vv->second<<" "<<igm[map_wr[it_vv->first]].wcount<<endl;
	}

};


int cmp(const PAIR& x,const PAIR&y)  
{
	return x.second > y.second;
};


void ReadFeatures(string ifn,int div)
{
	ifstream ifs;
	string line;
	ifs.open(ifn.c_str());
	int i=0;
	while(getline(ifs,line)&&i<div)
	{
		istringstream strstm(line);
		string str_f[2];
		strstm>>feat[i].word>>str_f[0]>>str_f[1];
		feat[i].ig=atof(str_f[0].c_str());
		feat[i].ni=atof(str_f[1].c_str());
		i++;
	}
	ifs.close();
};

double ComputeE(vector<double> &x,int div)
{
	double esum=0;
	for(int i=0;i<div;i++)
	{
		esum+=x[i]*x[i];
	}
	return sqrt(esum);
};


void ComputeDVM(int DCNUM,int div)
{
	for(int i=0;i<DCNUM;i++)
	{
		dvm[i].tf.resize(div);
		dvm[i].v.resize(div);
		dvm[i].ev.resize(div);
	
		for(int j=0;j<div;j++)
		{
			dvm[i].tf[j]=igm[map_wr[feat[j].word]].wc[i];
			dvm[i].v[j]=-1*dvm[i].tf[j]*log(feat[j].ni/DCNUM+DBM);
		}
		cout<<endl;
	}
	
	for(int i=0;i<DCNUM;i++)
	{
		//cout<<"DOC "<<i<<"---";
		double tempem=ComputeE(dvm[i].v,div);
		//cout<<tempem<<" ";
		for(int j=0;j<div;j++)
		{
			dvm[i].ev[j]=dvm[i].v[j]/tempem;		
			//cout<<dvm[i].ev[j]<<" ";
		}
		//cout<<endl;
	}
};


void PrintAll(string ofn,int DCNUM,int div)
{
	 ofstream ofs(ofn.c_str());
	//打印IG特征向量
	for(int i=0;i<div;i++)
	{
		cout<<feat[i].word<<":"<<feat[i].ig<<":"<<feat[i].ni<<endl;	
	}
	//打印IGMATRIX
	//for(int i=0;i<IGM_CC;i++)
	for(int i=0;i<div;i++)
	{
		//cout<<igm[i].word<<" ";
	}
	cout<<"--------------------";
	for(int i=0;i<div;i++)
	{
		cout<<feat[i].word<<" ";	
	}
	cout<<endl;
	//打印文档向量
	for(int i=0;i<DCNUM;i++)
	{
		cout<<"DOCV "<<i<<" ";
		ofs<<i<<" ";
		for(int j=0;j<div;j++)
		{
			cout<<setw(6)<<dvm[i].v[j]<<" ";
			ofs<<dvm[i].v[j]<<" ";
		}
		ofs<<endl;
		cout<<endl;
	}
};

void ReadTDVM(string ifn,int div)
{
	ifstream ifs;
	string line;
	ifs.open(ifn.c_str());
	int j=0;
	while(getline(ifs,line))
	{
		if(dvm[j].tf.size()==0)
		{
			dvm[j].tf.resize(div);
			dvm[j].v.resize(div);
			dvm[j].ev.resize(div);
		}
	
		istringstream strstm(line);
		string str_f[div+1];
		int i=0;
		while(strstm>>str_f[i]&&(i<div))
		{
			//cout<<i<<endl;
			if(i>0)
			{
				dvm[j].v[i-1]=atof(str_f[i].c_str());
			}
			i++;
		}
		j++;
	}
};


double Cos(vector<double> &a,vector<double> &b,int div)
{
    double sum_up=0;
    double ji_a=0;
    double ji_b=0;
    for(int i=0;i<div;i++)
    {
        sum_up+=a[i]*b[i];
        ji_a+=a[i]*a[i];
        ji_b+=b[i]*b[i];
    }
    double mod_a=sqrt(ji_a);
    double mod_b=sqrt(ji_b);
    return sum_up/(mod_a*mod_b);
};

void ConvertTest(string ifn,int DCNUM,int div)
{
	ifstream ifs;
	string line;
	ifs.open(ifn.c_str());  
	while(getline(ifs,line))
	{
		istringstream strstm(line);
		string str_f;
		while(strstm>>str_f)
		{
			map_test[str_f]++;
		}
	}
	
	dvm_test.tf.resize(div);
	dvm_test.v.resize(div);
	dvm_test.ev.resize(div);
	
	for(int i=0;i<div;i++)
	{
		dvm_test.tf[i]=map_test[feat[i].word];
		dvm_test.v[i]=-1*dvm_test.tf[i]*log(feat[i].ni/DCNUM+DBM);
		//cout<<dvm_test.v[i]<<endl;
	}
	cout<<"Test Sample Belong:"<<setw(10)<<Test(dvm_test.v,DCNUM,div)<<endl; //******
};


int Test(vector<double> &x,int KNN,int div)
{
    double D_res[KNN];
    map<int,vector<int> >::iterator it_cd;
    map<double,int> map_cmp;
    for(int i=0;i<KNN;i++)
    {
        D_res[i]=Cos(dvm[i].v,x,div); //
        //cout<<"Asserting Result "<<i<<":"<<setw(10)<<D_res[i]<<endl;
    }
    cout<<"-------------------"<<endl;
    for(it_cd=map_cd.begin();it_cd!=map_cd.end();it_cd++)
    {
         double sum=0;
         for(int j=it_cd->second[0];j<=it_cd->second[1];j++)
         {
			 if(!isnan(D_res[j]))
             {sum+=D_res[j];}
         }
		 cout<<it_cd->first<<":"<<sum<<endl;
         map_cmp[sum]=it_cd->first;
         cout<<"Asserting Class  "<<it_cd->first<<":"<<setw(10)<<sum<<endl;
     }
     map<double,int>::iterator it_cmp;
     it_cmp=map_cmp.end();
     it_cmp--;
	 cout<<"-------------------"<<endl;
     //cout<<it_cmp->first<<":"<<it_cmp->second<<endl;
     return it_cmp->second;
};