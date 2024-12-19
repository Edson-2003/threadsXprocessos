all:
	g++ t1_SO_main.cpp -o t1_SO_main -Wall

clean:
	rm t1_SO_main threads.out process.out
