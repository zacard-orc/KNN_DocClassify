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

5,And then,you maybe form the document vector / ig vector / feature vector.it will output into the home directory.  
[dvm 3 50 10]  
//3 means class number,50 means docs number per class.  

6,Finally,you can test the file you want to classify.  
[run 3 50 10 ./unknown]    
//3 means class number,50 means docs number per class.10 means the dimension of the feature vector.  

Directory description  
====================================  
fragment:A directory for raw document after split word.  
frequency:A directory for every document after wordcount.  
rawdoc:A directory for every document after cut by line.  
include:A directory for .h file  
lib:A directory for .a file  
src:A directory for .cpp source file  

Testing Sample  
====================================  
[root@cent5 knn]# run 3 50 10 ./unknown  
用户反映A月A日AA点到AA点之间本机发送短信给AAAAAAA，但对方称收到的短信内容不是用户发送的，之前网管回复需提供具体的地址，用户提供在浦东南桥营业厅附近的小区，请网管核实处理。)【发送号码：AAAAA,接收号码：AAAAAAAAA】  
Write Complete!: ./testfile  
>>  
0:18.3146  
Asserting Class  0:   18.3146  
1:1.95339  
Asserting Class  1:   1.95339  
2:1.16635  
Asserting Class  2:   1.16635  
>>  
Test Sample Belong:         0  

[root@cent5 knn]# run 3 50 10 ./unknown  
KF2013-10-17-2580 用户来电反映相同问题，酷派 8020+，称手机问题，我出当时给出的建议是该手机型号已经没有给用户做退订，用户不认可用户称要么换一个同等价位的手机换一部，要么给予一定费用的补偿，解释无效请处理但之前的投诉记录内并未提及到任何用户说的情况，请处理。    
Write Complete!: ./testfile  
>>  
0:8.94447  
Asserting Class  0:   8.94447  
1:12.502  
Asserting Class  1:    12.502  
2:5.5903  
Asserting Class  2:    5.5903  
>>  
Test Sample Belong:         1  

Environment    
====================================    
Linux/Centos Kernel2.6 Gcc4.4.7

Announcement  
====================================  
Just as a test user data related to this project, please do not reprint or forward.  
