all:mypipeline 
mypipeline.o:task2.c
	gcc -g -m32 -c -o mypipeline.o task2.c
mypipeline: mypipeline.o 
	gcc -m32 -o mypipeline mypipeline.o 

.PHONY: clean
clean:
	 rm -rf ./*.o mypipeline
