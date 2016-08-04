when registers and a stack are not enough...

Memory offset of 100 or something like that
Each memory cell has index, tmp1, tmp2, data
finding a cell:
compare index to prev tmp1
if not set tmp1 to prev tmp2  and move to next cell
if so then copy data to prev tmp1 until index is 0
>>>>[
>[-]<<<[-]<[>+>>>+<<<<-]>>>>[<<<<+>>>>-] ptmp2 = ptmp1
[-]>[-] <<<<<[>>>>+<<<<-]+
>>>[>->+<<-] >>[<<+>>-] <[<<<<->>>>[-]] ptmp1 = idx == ptmp1
>[-]>[-]<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-] ptmp2 = ptmp1

store:
check if cell
if not copy last tmp1 to this cell and move to next
when so copy last tmp1 to data and leave heap