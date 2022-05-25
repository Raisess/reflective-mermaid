CC=g++

SRC_DIR=./src
INPUT=$(SRC_DIR)/main.cpp \
			$(SRC_DIR)/Lexer.cpp \
			$(SRC_DIR)/Parser.cpp \
			$(SRC_DIR)/ParserListener.cpp \
			$(SRC_DIR)/Utils/File.cpp

BUILD_DIR=./build
OUTPUT=$(BUILD_DIR)/refmermaid

build:
	mkdir -p $(BUILD_DIR)
	$(CC) $(INPUT) -o $(OUTPUT)

clean:
	rm -r $(BUILD_DIR)
