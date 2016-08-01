testfiles=$(wildcard tests/*.bif)
tests=$(testfiles:.bif=.b)

all:
	gcc biffle.c functions.c hashmap.c -o biffle

test: 
	./bif tests/*.bif
	./cbf tests/*.b

clean:
	rm tests/*.b
	rm *.b

