all: main

dependencies = hash.c list.c headers.c persistent.c file.c
headers = hash.h headers.h list.h persistent.h file.h
main: main.c ${dependencies} ${headers}
	gcc -o main main.c ${dependencies} -I. -lcrypto

clean:
	@rm main