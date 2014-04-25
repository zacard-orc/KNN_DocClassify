#include "dochandle.h"

using namespace std;


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
	
   stringstream iss,oss;
   string ifn,ofn;
   ofstream cdfs("./class-doc.txt");
   int step=atoi(argv[2]);
   for(int cls=0;cls<atoi(argv[1]);cls++)
   {
      for(int i=0;i<step;i++)
      {
		if(i==0) cdfs<<cls<<" "<<cls*step+i<<" ";
		if(i==step-1) cdfs<<cls*step+i<<endl;
		iss<<"./fragment/c"<<cls+1<<"/"<<i;
		oss<<"./frequency/"<<cls*step+i;
		iss>>ifn;
		oss>>ofn;
		iss.clear();
		oss.clear();
		Wc(ifn,ofn);
	  }
   }
}



