DEBUG := 1

CXX := clang
CXX_FLAGS := -pedantic-errors -v -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -std=c++17

LIBRARIES := glfw3dll.lib glad.c stb_image.cpp freetype.lib irrKlang.lib
EXECUTABLE := ponggl

ifeq ($(DEBUG),1)
run: $(EXECUTABLE)
	# clear
	@echo "🚀  Executing..."
	./$(EXECUTABLE).exe
else
run: $(EXECUTABLE)
	# clear
	@echo "🚀  Executing..."
	rm -rf ../build
	mkdir ../build
	cp $(EXECUTABLE).exe ../build
	cp *.dll ../build
	cp -r audio ../build
	cp -r shaders ../build
	cp -r fonts ../build
	cp -r textures ../build
	../build/$(EXECUTABLE).exe
endif

$(EXECUTABLE): start
	@echo "🏗️  Building $(EXECUTABLE)..."
	$(CXX) -l$(LIBRARIES) --output=$(EXECUTABLE).exe main.cpp

start:
	@echo "🚧  Starting..."