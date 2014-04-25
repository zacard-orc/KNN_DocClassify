A Document Classify Tool
====================================
This is based on a document classification tool KNN.  
I put it in the complaint classification navigation WMS system CMCC Shanghai on the current.
For the sake of convenience,I compile it to static libfile.
You are welcome to use it.  


Use Method
====================================
0,You should install scws first.  http://www.xunsearch.com/scws/  
1,Use make command to complie. It will generate some executable file in the home directory. 
[make] 
2,First, you maybe split the raw document from one whole file to Separate document.The file you see,just like:
c1raw.txt.a  
c2raw.txt.a  
c3raw.txt.a  
[splitword 3 50]  
3 means class number,50 means docs number per class.
3,wordcount 3 50  
4,wordmatrix 3 50  
5,dvm 3 50 10  
6,run 3 50 10 ./unknown 

Directory description  
====================================  


Environment  
====================================   
Linux/Centos Kernel2.6 Gcc4.4.7