CXXFLAGS = -Wall -g -pedantic -std=c++17




HEADERS = $(wildcard src/*.h) $(wildcard src/Filters/*.h) $(wildcard src/Export/*.h) $(wildcard src/Notes/*.h) $(wildcard src/Sorting/*.h)
SOURCES = $(wildcard src/*.cpp) $(wildcard src/Filters/*.cpp) $(wildcard src/Export/*.cpp) $(wildcard src/Notes/*.cpp) $(wildcard src/Sorting/*.cpp)
OBJECTS = $(patsubst src/%.cpp,build/%.o,$(SOURCES))

.PHONY: all clean doc compile run

all: compile doc

compile : durkojak

durkojak: $(OBJECTS)
	g++ $(CXXFLAGS) $^ -o $@

run: compile
	./durkojak /home/jakub/durkojak/config.properties


build/%.o: src/%.cpp $(HEADERS)
	mkdir -p $(@D)
	g++ $(CXXFLAGS) -c $< -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile


clean:
	rm -rf durkojak build/ doc/ 2>/dev/null

