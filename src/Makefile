main: main.o classes.o ode.o aggregates.o configurations.o classes.h ode.h aggregates.h configurations.h
	c++ --std=c++11 -O0 -g -o main main.o classes.o ode.o aggregates.o configurations.o -ltrapfpe -lpgplot -lcpgplot -lX11

main.o: main.cpp classes.h ode.h
	c++ --std=c++11 -c main.cpp -g

classes.o: classes.cpp classes.h
	c++ --std=c++11 -c classes.cpp -g

ode.o: ode.cpp ode.h
	c++ --std=c++11 -c ode.cpp -g

aggregates.o: aggregates.cpp aggregates.h
	c++ --std=c++11 -c aggregates.cpp -g

configurations.o: configurations.cpp configurations.h
	c++ --std=c++11 -c configurations.cpp -g

