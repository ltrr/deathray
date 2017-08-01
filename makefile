srcs = image.cpp color.cpp
examples = example1

all: $(examples)

clean:
	rm -f $(examples)

.PHONY: all clean

example1: example1.cpp $(srcs)
	g++ -std=c++11 -o example1 example1.cpp $(srcs)
