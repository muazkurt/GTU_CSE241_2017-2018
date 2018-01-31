exe: GTUSet.o GTUSetAbstract.o GTUMap.o GTUGlobal.o main.o
	g++ -o exe Binaries/*.o

GTUSet.o: Sources/GTUSet.cpp
	g++ -std=c++11 -c Sources/GTUSet.cpp -o Binaries/GTUSet.o

GTUSetAbstract.o: Sources/GTUSetAbstract.cpp
	g++ -std=c++11 -c Sources/GTUSetAbstract.cpp -o Binaries/GTUSetAbstract.o

GTUMap.o: Sources/GTUMap.cpp
	g++ -std=c++11 -c Sources/GTUMap.cpp -o Binaries/GTUMap.o

GTUGlobal.o: Sources/GTUGlobal.cpp
	g++ -std=c++11 -c Sources/GTUGlobal.cpp -o Binaries/GTUGlobal.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -o Binaries/main.o

clear:
	rm Binaries/*.o exe