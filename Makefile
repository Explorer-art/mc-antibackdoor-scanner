SRC_DIR = "src"

all: clean mc-scanner

mc-scanner:
	gcc -lssl -lcrypto $(SRC_DIR)/mc-scanner.c $(SRC_DIR)/utils.c -o $@

clean:
	rm -f mc-scanner