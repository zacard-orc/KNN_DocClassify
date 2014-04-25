#include "dvm.h"


using namespace std;



int main(int argc,char *argv[])
{

	if(argc!=4)
    { 
        printf("Not Enough Parameters!,GoodBye Exit(0)!\n");
        printf("Or you can try example below:\n");
        printf("dvm 3 50 10\n");   
        printf("3 mens class number\n");  //argv[1]:class number
        printf("50 means doc per class number\n"); //argv[2]:doc per class number
		printf("10 means features div\n");   //argv[3]:features div
        exit(0);
    }
	
	int n_class=atoi(argv[1]);	//类的数量
	int n_doc=atoi(argv[2]);	//每个类的文档数
	int n_div=atoi(argv[3]); 	//特征项维度
	int n_total_doc=n_class*n_doc;  //文档总数


	CreateDCIndex("./class-doc.txt");
    int igm_num=ReadMatrix("./matrix.txt",n_class,n_total_doc);  //生成词频矩阵，返回记录数
	cout<<igm_num<<endl;
	ComputerIgm("./features.txt",igm_num,n_class,n_total_doc,n_div);
	ReadFeatures("./features.txt",n_div);
	ComputeDVM(n_total_doc,n_div);
	PrintAll("./tdvm.txt",n_total_doc,n_div);
}



