main: main.o classes.o ode.o classes.h ode.h
	c++ -o main main.o classes.o ode.o -ltrapfpe -lpgplot -lcpgplot -lX11

main.o: main.cpp classes.h ode.h
	c++ -c main.cpp

classes.o: classes.cpp classes.h
	c++ -c classes.cpp

ode.o: ode.cpp ode.h
	c++ -c ode.cpp

