every cell holds both its address and value
curaddress <
goto 0: <[<<]
goto n: <[!=n>>]
00102030
every block is an instruction
jcmp register for comparisons
pc register - index

mov hlt 1
hlt
[
cmp .here pc
[
op
inc pc
jzero
]
]

memory layout:
0 = hlt.  Setting to zero and setting pc to zero will end program.
1 = pc.   Refers to the index of the next instruction to be executed.  
		  Change to jump.
2 = jcmp. Stores the value of whether the current instruction 
		  is the one pointed to by pc.
3 = cmp.  Stores the result of the last comparison.
4 = ein.  First "general purpose" register.
5 = zwei. Second "general purpose" register.
6 = zero. Register with sole value of 0. 
		  Useful for ending loops without changing state.
7 = sc	  Stack counter - points to top of stack.
8-512	  Stack.  Values are push'd and pop'd at the location of the sc.
513+	  Heap.
