PROGRAM = buresp10
C_FILES := $(wildcard ./src/*.h ./src/*.cpp)
OBJS := $(patsubst %.c, %.o, $(C_FILES))
CC = g++
CFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11

all: $(PROGRAM)
	doxygen dgex.cfg

$(PROGRAM): .depend $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

depend: .depend

 .depend: cmd = g++ -MM -MF depend $(var);
 .depend:
	@echo "Generating dependencies..."
	@$(foreach var, $(C_FILES), $(cmd))
	@rm -f depend

# These are the pattern matching rules. In addition to the automatic
# variables used here, the variable $* that matches whatever % stands for
# can be useful in special cases.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f .depend buresp10 
	rm -rf doc

compile: $(PROGRAM)
	
doc:
	doxygen dgex.cfg 
run:
	./buresp10

.PHONY: clean depend all doc run compile
