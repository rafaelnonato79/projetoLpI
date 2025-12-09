# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    # Windows
    RM = del /Q
    EXE = main.exe
    MKDIR = if not exist bin mkdir bin
    RMDIR = if exist bin rmdir /S /Q bin
else
    # Linux/Unix
    RM = rm -f
    EXE = main
    MKDIR = mkdir -p bin
    RMDIR = rm -rf bin
endif

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheader
SRCDIR = src
HEADERDIR = header
OBJDIR = obj

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Alvo padrão
all: $(EXE)

# Compila o executável
$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compila arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria diretório de objetos
$(OBJDIR):
ifeq ($(OS),Windows_NT)
	if not exist $(OBJDIR) mkdir $(OBJDIR)
else
	mkdir -p $(OBJDIR)
endif

# Executa o programa
run: $(EXE)
	./$(EXE)

# Limpa arquivos compilados
clean:
ifeq ($(OS),Windows_NT)
	if exist $(OBJDIR) rmdir /S /Q $(OBJDIR)
	if exist $(EXE) del /Q $(EXE)
else
	rm -rf $(OBJDIR)
	rm -f $(EXE)
endif

# Limpa tudo incluindo arquivos de dados
cleanall: clean
ifeq ($(OS),Windows_NT)
	if exist bin rmdir /S /Q bin
else
	rm -rf bin
endif

# Recompila tudo
rebuild: clean all

.PHONY: all run clean cleanall rebuild
