APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

GLUT_FLAGS = -lGL -lGLU -lglut
MULTIPLE_FLAGS = "-Wl,--allow-multiple-definition"

APP = main

all: _src clean_apps _apps

_src: \
		$(OBJ)/opengl_manager.o\
		$(OBJ)/point.o

clean_apps:
	rm -rf $(BIN)/*

_apps: $(BIN)/$(APP)
	$(BIN)/$(APP)

clean:
	rm $(OBJ)/*

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	g++ -c $< -I $(INCLUDE) -o $@ $(GLUT_FLAGS) $(MULTIPLE_FLAGS)

$(BIN)/%: $(APPS)/%.cpp
	g++ $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(GLUT_FLAGS) $(MULTIPLE_FLAGS)

$(OBJ)/%.o: 
	g++ -c $< -I $(INCLUDE) -o $@ $(GLUT_FLAGS) $(MULTIPLE_FLAGS)
