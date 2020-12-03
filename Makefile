#stack

test:Stack.c TestStack.c
	gcc -g Stack.c TestStack.c -o stack
	./stack
