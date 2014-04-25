#include "dochandle.h"

using namespace std;


extern map<string,vector<int> > map_wc;

int main(int argc,char *argv[])
{

	if(argc!=3)
    {
        printf("Not Enough Parameters!,GoodBye Exit(0)!\n");
        printf("Or you can try example below:\n");
        printf("wordcount 3 50 \n");
        printf("3 mens class number\n");
        printf("50 means doc per class number\n");
        exit(0);
    }
	
	int dnum=atoi(argv[1])*atoi(argv[2]);
	
	for(int i=0;i<dnum;i++)
	//for(int i=0;i<150;i++)
	{
		stringstream iss;
		iss<<"./frequency/"<<i;
		cout<<iss.str()<<endl;
		ReadWordCountFile(iss.str(),i,dnum);
	}

 
   
   //打印词频矩阵
   WcmPrint("./matrix.txt");
}



