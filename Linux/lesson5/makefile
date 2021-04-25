CFLAGS = -g
BIN1 = main
BIN2 = test

all:$(BIN1) $(BIN2)

$(BIN1):main.c a.c b.c d.c
	gcc $^ -o $@ $(CFLAGS)

$(BIN2):test.c
	gcc $^ -o $@

clean:
	rm main test
