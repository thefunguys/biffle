CC = gcc
CFLAGS = -Wall -O1
SOURCES = biffle.c functions.c hashmap.c


EXE = biffle
SRCDIR = .
OBJDIR = build
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

$(EXE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@ 

test: $(EXE) 
	./bif tests/*.bif
	./cbf tests/*.b

clean:
	rm build/*.o
