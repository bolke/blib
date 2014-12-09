all: clean main

clean:
	rm -f main
main:
	g++ -std=c++0x -D LINUX -c main.cpp -I../../blibLinux/build/blib/inc/
	g++ -std=c++0x -o main main.o ../../blibLinux/build/blib/Blib.a -Wl,--no-as-needed -lrt -lpthread
	chmod +x main
	mkdir -p ./obj
	mv *.o ./obj
