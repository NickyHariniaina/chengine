FILE_TO_COMPILE=$(wildcard src/*.c)
OUTPUT_FOLDER=bin/

all: run

initiate:
	mkdir -p $(OUTPUT_FOLDER)

compile:
	gcc -o $(OUTPUT_FOLDER)main $(FILE_TO_COMPILE)

clean:
	rm -rf $(OUTPUT_FOLDER)

run: clean initiate compile
	./$(OUTPUT_FOLDER)main
