#include "dvm.h"
#include "dochandle.h"
#include <string.h>
#include <scws/scws.h>

#define SCWS_PREFIX  "/usr/local/scws"

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



using namespace std;

int main(int argc,char *argv[])
{

	if(argc!=5)
    { 
        printf("\nNot Enough Parameters!,GoodBye Exit(0)!\n");
        printf("Or you can try example below:\n");
		printf("----------------------------------------------------\n");
        printf("run 3 50 10 ./unknown\n");   
        printf("3 mens class number\n");  //argv[1]:class number
        printf("50 means doc per class number\n"); //argv[2]:doc per class number
		printf("10 means features div\n");   //argv[3]:features div
		printf("./unknown means the file you want to classify\n");   //argv[4]:testfile
        exit(0);
    }
	
	int n_class=atoi(argv[1]);	//类的数量
	int n_doc=atoi(argv[2]);	//每个类的文档数
	int n_div=atoi(argv[3]); 	//特征项维度
	int n_total_doc=n_class*n_doc;  //文档总数
	
	CreateDCIndex("./class-doc.txt");
	ReadFeatures("./features.txt",n_div);
	ReadTDVM("./tdvm.txt",n_div);
	
	ifstream ifs;
	string line;
	ifs.open(argv[4]);  
	while(getline(ifs,line))
	{
		cout<<line<<endl;
		SplitWord(line,"./testfile");
	}
	
	ConvertTest("./testfile",n_total_doc,n_div);
}
