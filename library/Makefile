all: main

dependencies = hash.c list.c persistent.c headers.c file.c
headers = hash.h headers.h list.h persistent.h file.h
main: main.c ${dependencies} ${headers}
	gcc -g -o main main.c ${dependencies} -I. -lcrypto

clean:
	@rm main