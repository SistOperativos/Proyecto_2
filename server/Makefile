all: server

server:  server.c
		gcc -o server server.c 

clean:
		rm -f  $(OUT)/$(APP)*
		rm -f *.o 
		rm -f *.so
		rm -f *.a

.PHONY:clean all