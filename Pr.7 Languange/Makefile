Folder=Progs
Name=SquareEquation.txt

Program=$(Folder)/$(Name)

DebugOption="-D SUPERDEBUG=1"



run: language
	bin/Compiler.out $(Program)


language: general Compiler.cpp Parser.cpp NameTable.cpp
	g++ -c NameTable.cpp	-o bin/NameTable.o
	g++ -c Parser.cpp		-o bin/Parser.o
	g++ -c Compiler.cpp		-o bin/Compiler.o

	g++ bin/Compiler.o bin/Parser.o bin/FileProcessing.o bin/Initialisation.o bin/Logs.o bin/NameTable.o -o bin/Compiler.out


general: FileProcessing.cpp Initialisation.cpp Logs.cpp
	g++ -c FileProcessing.cpp -o bin/FileProcessing.o
	g++ -c Initialisation.cpp -o bin/Initialisation.o
	g++ -c Logs.cpp           -o bin/Logs.o $(DebugOption)