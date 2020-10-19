EXEFILE = vote_sys_gen
CXXFLAGS = -c -Wall
SOURCES = $(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

$(EXEFILE): $(OBJECTS)
	gcc $^ -pthread -o $@

%.o: %.c
	gcc $(CXXFLAGS) $^ -pthread -o $@

clean:
	rm *.o $(EXEFILE)
	rm data/output_file.txt
.PHONY: clean
