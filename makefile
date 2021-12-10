all: user.o worker.o
	gcc -o user user.o
	gcc -o worker worker.o

user.o: user.c
	gcc -x c -c user.c

worker.o: worker.c
	gcc -x c -c worker.c

clean:
	rm *.o
	rm user
	rm worker
	rm user_to_worker
	rm worker_to_user
