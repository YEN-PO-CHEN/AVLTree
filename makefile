all:AVLTree.c
	gcc -std=c11 *.c -o AVL
	./AVL <input0_windows.txt >ans_output0_windows.txt
	diff ./output0_windows.txt ./ans_output0_windows.txt
clean:
	rm *.exe