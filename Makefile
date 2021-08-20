a.out: main.cpp
	g++ main.cpp

clean:
	rm a.out

zip:
	zip pipe.zip main.cpp Makefile