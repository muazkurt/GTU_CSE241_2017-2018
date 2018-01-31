exe: main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o
	g++ -std=c++11 main.o  Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Cell.o: ./source/Cell.cpp
	g++ -std=c++11 -c ./source/Cell.cpp

ConnectFourAbstract.o: ./source/ConnectFourAbstract.cpp
	g++ -std=c++11 -c ./source/ConnectFourAbstract.cpp

ConnectFourPlus.o: ./source/ConnectFourPlus.cpp
	g++ -std=c++11 -c ./source/ConnectFourPlus.cpp

ConnectFourDiag.o: ./source/ConnectFourDiag.cpp
	g++ -std=c++11 -c ./source/ConnectFourDiag.cpp

ConnectFourPlusUndo.o: ./source/ConnectFourPlusUndo.cpp
	g++ -std=c++11 -c ./source/ConnectFourPlusUndo.cpp
clean:
	rm *.o exe