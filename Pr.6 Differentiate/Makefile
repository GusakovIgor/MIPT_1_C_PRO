run_diff: diff.exe
	Differentiate.exe

diff.exe: Parser.o Diff_Logs.o Output_Processing.o Differentiate.o Simplifying.o Main_Creation.o Diff.h
	g++ -w Parser.o Diff_Logs.o Output_Processing.o Differentiate.o Simplifying.o Main_Creation.o -o Differentiate.exe

Parser.o: Parser.cpp
	g++ -c -w Parser.cpp

Differentiate.o: Differentiate.cpp
	g++ -c -w Differentiate.cpp

Simplifying.o: Simplifying.cpp
	g++ -c -w Simplifying.cpp

Diff_Logs.o: Diff_Logs.cpp
	g++ -c -w Diff_Logs.cpp -DSUPERDEBUG

Output_Processing.o: Output_Processing.cpp
	g++ -c -w Output_Processing.cpp

Main_Creation.o: Main_Creation.cpp
	g++ -c -w Main_Creation.cpp

clear:
	cls
	del Main_Creation.o Parser.o Differentiate.o Simplifying.o Diff_Logs.o Output_Processing.o
	delete.exe LaTeX\\LaTeX_expression_.pdf
	delete.exe LaTeX\\LaTeX_expression_.log
	delete.exe LaTeX\\LaTeX_expression_.aux
	delete.exe  Logs\\DiffGraphicLogs_.png