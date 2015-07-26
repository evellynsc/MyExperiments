CC		= g++ -Wall -O -fPIC -fexceptions -DNDEBUG -DIL_STD
CFLAGS1_LACCAN	= -I/home/evellyn/ibm/cplex/include/ -I/home/evellyn/ibm/concert/include/
CFLAGS2_LACCAN	= -L/home/evellyn/ibm/cplex/lib/x86-64_sles10_4.1/static_pic/ -lilocplex -lcplex -L/home/evellyn/ibm/concert/lib/x86-64_sles10_4.1/static_pic/ -lconcert -lm -lpthread
CFLAGS1_LAPO	= -I/home/lapo/cplex/cplex125/cplex/include -I/home/lapo/cplex/cplex125/concert/include
CFLAGS2_LAPO	= -L/home/lapo/cplex/cplex125/cplex/lib/x86-64_sles10_4.1/static_pic -lilocplex -lcplex -L/home/lapo/cplex/cplex125/concert/lib/x86-64_sles10_4.1/static_pic -lconcert -lm -lpthread


FILES_CC	= io.cpp model.cpp main.cpp

BINARY		= evlex2

all:	clean compile

clean:
	find . -name '*.o' -exec rm -f '{}' ';'
	rm -f $(BINARY);

compile:
	$(CC) $(CFLAGS1_LAPO)  $(FILES_CC) -o $(BINARY)  $(CFLAGS2_LAPO)

