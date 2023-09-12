all: qmake
	make -C ./src

qmake:
	qmake ./src -o ./src/Makefile

run:
	./src/chess

doxygen:
	mkdir -p ./doc
	doxygen ./config

clean:
	make -C ./src clean
	rm ./src/Makefile
