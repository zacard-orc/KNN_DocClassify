#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <scws/scws.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#define SCWS_PREFIX  "/usr/local/scws"

using namespace std;

void SplitWord(string text,string ofn);

void ConvertDocByLine(string ifn,string ofd)
//参数1：原文件、参数2：输出路径
{
	ifstream ifs;	
	string line;
	string ofn;
	ifs.open(ifn.c_str());
	int i=0;
	stringstream ss;
	
	while(getline(ifs,line))
	{
		ss<<ofd<<"/"<<i;
		ss>>ofn;
		ss.clear();
		ofstream ofs(ofn.c_str());
		ofs<<line<<endl;
		i++;
		ofs.close();
	}
	ifs.close();
	
}

void ReadDoc(string ifd,string ofd,int RDNUM)
{
	ifstream ifs;
	string ifn,ofn;
	string line;
	int i=0;
	stringstream iss,oss;
	while(i<RDNUM)
	{
		iss<<ifd<<"/"<<i;
		oss<<ofd<<"/"<<i;
		iss>>ifn;
		oss>>ofn;
		iss.clear();
		oss.clear();
		//cout<<ifn<<endl;
		ifs.open(ifn.c_str());
		while(getline(ifs,line))
		{
			//cout<<line<<endl;
			SplitWord(line,ofn);
		}
		ifs.close();
		i++;	
	}
};

void SplitWord(string text,string ofn)
{
	scws_t s;
	scws_res_t res,cur;
	const char *tt=text.c_str();
	ofstream ofs(ofn.c_str());

	s=scws_new();
	scws_set_charset(s,"utf8");
	scws_set_dict(s,"/usr/local/scws/etc/dict.utf8.xdb",SCWS_XDICT_XDB);
	scws_set_rule(s,"/usr/local/scws/etc/rules.utf8.ini");	


	scws_send_text(s,tt,strlen(tt));
	while((res=(cur=scws_get_result(s))))
	{
		while (cur!=NULL)
		{
			char buff[50];
			sprintf(buff,"%.*s",cur->len, tt+cur->off);
			ofs<<buff<<" ";
			//cout<<buff<<endl;
			cur=cur->next;		
		}
		scws_free_result(res);
	}
	cout<<"Write Complete!: "<<ofn<<endl;

	ofs.close();
	scws_free(s);
};

void SysShell(string ccmd,int flag)
{
		stringstream iss;
		iss<<ccmd<<flag;
		cout<<iss.str()<<endl;
		system((iss.str()).c_str());
		iss.clear();
}


int main(int argc,char *argv[])
{
	stringstream iss;
	string NLL; //NULL;
 
	if(argc!=3)
    {
        printf("Not Enough Parameters!,GoodBye Exit(0)!\n");
        printf("Or you can try example below:\n");
        printf("splitword 3 50 \n");
        printf("3 mens class number\n");
        printf("50 means doc per class number\n");
        exit(0);
    }
		
    cout<<argv[0]<<":"<<argv[1]<<endl;
		
	for(int i=0;i<atoi(argv[1]);i++)
	{
		SysShell("rm -Rf ./rawdoc/c",i+1);
		SysShell("rm -Rf ./fragment/c",i+1);
		SysShell("mkdir ./rawdoc/c",i+1);
		SysShell("mkdir ./fragment/c",i+1);
	}
	
	ConvertDocByLine("/root/tt/knn/c1raw.txt.a","/root/tt/knn/rawdoc/c1");
	ConvertDocByLine("/root/tt/knn/c2raw.txt.a","/root/tt/knn/rawdoc/c2");
	ConvertDocByLine("/root/tt/knn/c3raw.txt.a","/root/tt/knn/rawdoc/c3");

	ReadDoc("/root/tt/knn/rawdoc/c1","/root/tt/knn/fragment/c1",atoi(argv[2]));
	ReadDoc("/root/tt/knn/rawdoc/c2","/root/tt/knn/fragment/c2",atoi(argv[2]));
	ReadDoc("/root/tt/knn/rawdoc/c3","/root/tt/knn/fragment/c3",atoi(argv[2]));
}
