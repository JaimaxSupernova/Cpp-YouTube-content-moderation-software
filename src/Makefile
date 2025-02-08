main: Creator.o main.o Person.o User.o vidManage.o
	g++ -o main Creator.o main.o Person.o User.o vidManage.o 
	make clean

main.o: main.cpp
	g++ -c main.cpp 

Creator.o: Creator.cpp
	g++ -c Creator.cpp

Person.o: Person.cpp
	g++ -c Person.cpp

User.o: User.cpp
	g++ -c User.cpp

vidManage.o: vidManage.cpp
	g++ -c vidManage.cpp


ifeq ($(OS), Windows_NT)
clean:
	del *.o
else
clean:
	rm *.o
endif

run:
	./main