CXX := clang
CXX_FLAGS := -pedantic-errors -v -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -std=c++17

LIBRARIES := glfw3dll.lib glad.c stb_image.cpp freetype.lib irrKlang.lib
EXECUTABLE := ponggl

run: $(EXECUTABLE)
	# clear
	@echo "🚀  Executing..."
	./$(EXECUTABLE).exe

$(EXECUTABLE): start
	@echo "🏗️  Building $(EXECUTABLE)..."
	$(CXX) -l$(LIBRARIES) --output=$(EXECUTABLE).exe main.cpp

start:
	@echo "🚧  Starting..."