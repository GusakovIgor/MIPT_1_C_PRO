RunCPU: Assembler Executor
	bin/Assembler.out $(CODE)
	bin/Executor.out  $(CODE)

Executor: Executor.cpp TextProcessing.cpp MyStack/Stack.cpp MyStack/Protection.cpp CPU_header.h Commands.h
	@g++ -w Executor.cpp TextProcessing.cpp MyStack/Stack.cpp MyStack/Protection.cpp -o bin/Executor.out

Assembler: Assembler.cpp TextProcessing.cpp CPU_header.h Commands.h
	@g++ -w Assembler.cpp TextProcessing.cpp -o bin/Assembler.out