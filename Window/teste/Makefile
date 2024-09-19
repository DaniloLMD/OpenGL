
all:
	g++ teste.cpp -o teste $(OPENGL_FLAGS) -I obj/*.o
	./teste

comp:
	g++ -c src/glad.c -o obj/glad $(OPENGL_FLAGS)


APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

OPENGL_FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl



all: _src clean_apps _apps

_src: \
		$(OBJ)/glad.o
		
clean_apps:
	rm -rf $(BIN)/*

_apps: $(BIN)/teste
	$(BIN)/teste

clean:
	rm $(OBJ)/*


$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	g++ -c $< -I $(INCLUDE) -o $@ $(SDL_FLAGS) $(MULTIPLE_FLAGS)

$(BIN)/%: $(APPS)/%.cpp
	g++ $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(SDL_FLAGS) $(MULTIPLE_FLAGS)


$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc -c $< -I $(INCLUDE) -o $@ $(SDL_FLAGS) $(MULTIPLE_FLAGS)

$(BIN)/%: $(APPS)/%.c
	gcc $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(SDL_FLAGS) $(MULTIPLE_FLAGS)
