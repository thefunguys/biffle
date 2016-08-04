(require 'generic-x)

(define-generic-mode
	'bif-mode
  '(";")
  '("add" "sub" "addi" "subi" "print" "debug" "load" "store" "set" "mult" "div" "mod" "getc" "mov" "comp" "bif" "cne" "jump" "put" "inc" "dec" "hlt" "call" "noop" "push" "pop" "ret")
  '(("[0-9]+" . font-lock-contant-face)
	("\\..\\+" . font-lock-variable-name-face)
	("\\ein\\" . font-lock-variable-name-face)
	)
  '("\\.bif$")
  nil
  "mode for bif files"
  )
