run: Akinator.exe
	Akinator.exe

Akinator.exe: List_main.o Akinator_main.o Logs.o TreeFileProcessing.o Akinator.h List\\List.h
	g++ -w List_main.o Akinator_main.o Logs.o TreeFileProcessing.o -o Akinator.exe

List_main.o: List\\List_main.cpp
	g++ -c -w List\\List_main.cpp

Akinator_main.o: Akinator_main.cpp
	g++ -c -w Akinator_main.cpp

Logs.o: Logs.cpp
	g++ -c -w Logs.cpp

TreeFileProcessing.o: TreeFileProcessing.cpp
	g++ -c -w TreeFileProcessing.cpp



clear:
	del List_main.o Akinator_main.o Logs.o TreeFileProcessing.o
