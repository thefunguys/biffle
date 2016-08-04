where target is a location being modified, source is a constant location, value is a value, address is a memory address (starts at 1), and dest is a label or location in code
INSTRUCTION SET:

    add target source
	sub target source
	addi target value
	subi target value
	print rest_of_line
	debug source
	load target address
	store value address
	set target value
	mult target source
	div target source
	mod target source
	getc target
	mov target source
	comp target source
	bif source dest
	cne target source
	jump dest
	put source
	inc target
	dec target
	hlt
	ret
	noop
	call dest
	push source
	pop source