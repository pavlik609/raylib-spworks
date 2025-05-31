CC=g++
CFLAGS=-L/libs -lraylib -lm

SRC_ENGINE=src/engine
SRCS_ENGINE=$(wildcard $(SRC_ENGINE)/*.cpp)
OBJ_ENGINE=$(SRCS_ENGINE:$(SRC_ENGINE)/%.cpp=bin/%.o)


#Example folder
SRC_EXAMPLES=src/examples
#Gets all of the cpp files in SRC_EXAMPLES
SRCS_EXAMPLES=$(wildcard $(SRC_EXAMPLES)/*.cpp)
#Replaces all SRC_EXAMPLES/%.cpp with bin/%.o (defined by the rule)
OBJ_EXAMPLES=$(SRCS_EXAMPLES:$(SRC_EXAMPLES)/%.cpp=bin/%.o)
TARGETS_EXAMPLES=$(OBJ_EXAMPLES:bin/%.o=%)

#Compiles all of the OBJ_EXAMPLES into separate executables
$(TARGETS_EXAMPLES): $(OBJ_EXAMPLES)
	for obj in $(OBJ_EXAMPLES) ; do \
		$(CC) $(CFLAGS) $< -o $(basename $<) $(OBJ_ENGINE); \
	done


.PHONY: engine examples clean all

engine: $(OBJ_ENGINE)

examples: engine $(TARGETS_EXAMPLES)

clean:
	rm -rf bin

bin/%.o: $(SRC_ENGINE)/%.cpp
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $<  -o $@

bin/%.o: $(SRC_EXAMPLES)/%.cpp
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $<  -o $@
