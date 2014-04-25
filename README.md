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
//3 means class number,50 means docs number per class.  

3,Second,you maybe form the wordcount file by use this command:  
[wordcount 3 50]  
//3 means class number,50 means docs number per class.  

4,And then,you maybe form the wordcount matrix by use this command:  
[wordmatrix 3 50]    

5,And then,you maybe form the document vector / ig vector / feature vector.it will output into the home dircectory.  
[dvm 3 50 10]  
//3 means class number,50 means docs number per class.  

6,Finally,you can test the file you want to classify.  
[run 3 50 10 ./unknown]    
//3 means class number,50 means docs number per class.10 means the dimension of the feature vector.  

Directory description  
====================================  


Environment  
====================================   
Linux/Centos Kernel2.6 Gcc4.4.7