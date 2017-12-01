CFLAGS += -std=c++11 -Wall -I include/

bin/example: example.cpp src/* | include/* bin/
	g++ $^ -o $@ $(CFLAGS)

bin/:
	mkdir -p $@

clean:
	rm -rf bin/
