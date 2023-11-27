CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
OBJ		:= obj

LIBRARIES   := -ldl -lSDL2
EXECUTABLE  := prog

vpath %.cpp $(SRC)
vpath %.o $(OBJ)
vpath %.hpp $(INCLUDE)

OBJFILES	= $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(wildcard $(SRC)/*.cpp))

.PHONY: run clean

$(OBJ)/%.o : %.cpp Makefile
		@$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -MMD -c $< -o $@
		@echo "$*.o rebuilt"

	
$(BIN)/$(EXECUTABLE): $(OBJFILES)
	@$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

all: $(BIN)/$(EXECUTABLE)

run: $(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

clean:
	rm $(BIN)/*
	rm $(OBJ)/*

-include $(OBJ)/*.d