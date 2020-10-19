clp: main.o command_line_processor.o
	g++ -g -o clp main.o command_line_processor.o

main.o: main.cc
	g++ -g -c main.cc

command_line_processor.o: command_line_processor.h command_line_processor.cc
	g++ -g -c command_line_processor.h command_line_processor.cc
