#Diretórios
SRC_DIR = src
INC_DIR = classes
BUILD_DIR = build
BIN_DIR = bin

#Nome do executável
TARGET = $(BIN_DIR)/hospital

#Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INC_DIR)

#Localiza todos os arquivos .cpp dentro de src/
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

#Regra principal
all: $(TARGET)

#Linkagem final
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $(TARGET)
	@echo "✅ Compilação concluída: $(TARGET)"

#Compilação de cada .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Limpeza dos arquivos compilados
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "🧹 Limpeza concluída."

#Regra para recompilar do zero
rebuild: clean all

#Evita conflitos com arquivos reais chamados "clean", "all" etc.
.PHONY: all clean rebuild
