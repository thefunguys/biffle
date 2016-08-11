(require 'generic-x)

(define-generic-mode
	'bif-mode
  '(";") ; comment list
  '("add" "sub" "addi" "subi" "print" "debug" "load" "store" "set" "mult" "div" "mod" "getc" "mov" "comp" "bif" "cne" "jump" "put" "inc" "dec" "hlt" "call" "noop" "push" "pop" "ret" "printn") ; keyword list
  '(("\\[0-9\\]+" . font-lock-contant-face)
	("\\\\..+" . font-lock-variable-name-face)
	("%{\\([A-Z_]+\\)}" 1 font-lock-variable-name-face)
	("\\(ein\\|zwei\\)" . font-lock-variable-name-face)
	) ; font-lock list
  '("\\.bif$" "\\.bifh")
  nil
  "mode for bif files"
  )
