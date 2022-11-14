run: List.exe
	List.exe

debug: DebugList.exe
	DebugList.exe

List.exe: List_main.o Logs.o Unit_Tests.o List.h
	g++ -w List_main.o Logs.o Unit_Tests.o -o List.exe

DebugList.exe: List_main.o Debug_Logs.o Unit_Tests.o List.h
	g++ -w List_main.o Logs.o Unit_Tests.o -o DebugList.exe

List_main.o: List_main.cpp
	g++ -c -w List_main.cpp

Unit_Tests.o: Unit_Tests.cpp
	g++ -c Unit_tests.cpp

Logs.o: Logs.cpp
	g++ -c Logs.cpp

Debug_Logs.o:
	g++ -c Logs.cpp -DSUPERDEBUG

clear:
	del List_main.o Logs.o Unit_Tests.o