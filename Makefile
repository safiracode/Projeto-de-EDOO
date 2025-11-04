# No terminal, use:
# PowerShell (Windows): mingw32-make
# Bash (Linux/Mac): make

# Diretórios
SRC_DIR = src
INC_DIR = classes
BUILD_DIR = build
BIN_DIR = bin

# Nome do executável
TARGET = $(BIN_DIR)/hospital

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INC_DIR) -Iinclude

# Detecta sistema operacional
ifeq ($(OS),Windows_NT)
	MKDIR_P = if not exist $(1) mkdir $(1)
	RM_DIR = if exist $(1) rmdir /s /q $(1)
else
	MKDIR_P = mkdir -p $(1)
	RM_DIR = rm -rf $(1)
endif

# Localiza todos os arquivos .cpp dentro de src/
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# Regra principal
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJ)
	@$(call MKDIR_P,$(BIN_DIR))
	$(CXX) $(OBJ) -o $(TARGET)
	@echo "COMPILACAO CONCLUIDA: $(TARGET)"

# Compilação de cada .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call MKDIR_P,$(BUILD_DIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	@$(call RM_DIR,$(BUILD_DIR))
	@$(call RM_DIR,$(BIN_DIR))
	@echo "LIMPEZA CONCLUIDA"

# Recompilar do zero
rebuild: clean all

# Evita conflitos com arquivos reais chamados "clean", "all" etc.
.PHONY: all clean rebuild