CXX = g++
CXXFLAGS = -std=c++17 -I../header
SOURCES = main.cpp Pessoa.cpp Professor.cpp Aluno.cpp Equipamento.cpp Aula.cpp Plano.cpp PlanoPersonalizado.cpp Gerenciador.cpp Treino.cpp Modalidade.cpp
OUTPUT = academia.exe

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	del $(OUTPUT)

.PHONY: all run clean
