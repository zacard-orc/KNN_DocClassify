CXX:=g++
LIB_FLAGS=-ldvm -ldochandle
STD:=-std=c++0x
LIB_DIR:=./lib
SRC_DIR:=./src
INCLUDES_DIR:=./include
AR:=ar
ARFLAG:=cqs
BAN1:=@echo "Author Zacard: ";
BAN2:=@echo "--------------------------";


all:ann genlib arlib genobj genprog clean 
ann:
	$(BAN1)
	$(BAN2)
genlib:
	$(CXX) $(STD) -c -g -Wall -I$(INCLUDES_DIR) $(SRC_DIR)/l_dochandle.cpp  -o $(LIB_DIR)/l_dochandle.o
	$(CXX) $(STD) -c -g -Wall -I$(INCLUDES_DIR) $(SRC_DIR)/l_dvm.cpp -Wall -g -o $(LIB_DIR)/l_dvm.o
	$(CXX) $(STD) -c -g -Wall -I/usr/local/scws/include $(SRC_DIR)/p_splitword.cpp  -L/usr/local/scws/lib  -lscws -lm -o splitword.o
arlib:
	$(AR) $(ARFLAG) $(LIB_DIR)/libdochandle.a $(LIB_DIR)/l_dochandle.o
	$(AR) $(ARFLAG) $(LIB_DIR)/libdvm.a $(LIB_DIR)/l_dvm.o
genobj:
	$(CXX) $(SRC_DIR)/p_dvm.cpp $(STD)  -c -g -Wall -I$(INCLUDES_DIR) -L$(LIB_DIR) $(LIB_FLAGS) -o dvm.o;
	$(CXX) $(SRC_DIR)/p_wordcount.cpp $(STD)  -c -g -Wall -I$(INCLUDES_DIR) -L$(LIB_DIR) $(LIB_FLAGS) -o wordcount.o;
	$(CXX) $(SRC_DIR)/p_wordmatrix.cpp $(STD)  -c -g -Wall -I$(INCLUDES_DIR) -L$(LIB_DIR) $(LIB_FLAGS) -o wordmatrix.o;
	$(CXX) $(SRC_DIR)/p_run.cpp $(STD)  -c -g -Wall -I$(INCLUDES_DIR) -L$(LIB_DIR) -L/usr/local/scws/lib $(LIB_FLAGS)  -lscws -lm -o run.o;
genprog:
	$(CXX) dvm.o -L $(LIB_DIR) $(LIB_FLAGS)  -o dvm
	$(CXX) wordcount.o -L $(LIB_DIR) $(LIB_FLAGS)  -o wordcount
	$(CXX) wordmatrix.o -L $(LIB_DIR) $(LIB_FLAGS)  -o wordmatrix
	$(CXX) run.o -L $(LIB_DIR) $(LIB_FLAGS)  -L/usr/local/scws/lib  -lscws -lm  -o run
	$(CXX) splitword.o -L $(LIB_DIR) $(LIB_FLAGS) -L/usr/local/scws/lib  -lscws -lm   -o splitword



clean:cleanobj
cleanobj:
	rm -f $(LIB_DIR)/*.o
	rm -f *.o