tokens = (
    'NAME', 'NUMBER', 'SYMBOL',
    'PLUS', 'MINUS', 'TIMES', 'AMP', 'DEREF', 'DIVIDE', 'EQUALS', 'NOTEQ', 'ASSIGN', 'MOD',
    'LPAREN', 'RPAREN', 'DO', 'END', 'VAR', 'COMMA', 'LBRACKET', 'RBRACKET', 'FN', 'ATSYM',
    'IF', 'ELSE', 'WHILE', 'SEMICOLON',
    'INT', 'CHAR', 'TYPE'
    )
reserved = {'do': 'DO', 'end': 'END', 'var': 'VAR', 'fn': 'FN', 'if': 'IF', 'else': 'ELSE', 'while': 'WHILE',}
types = {'int': 'INT', 'char': 'CHAR'}
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_AMP = r'&'
t_DEREF = r'\$'
t_MOD = r'%'
t_DIVIDE = r'/'
t_EQUALS = r'=='
t_NOTEQ = r'!='
t_ASSIGN = r'='
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_SEMICOLON = r';'
t_ATSYM = r'@'
t_COMMA = ','
def t_NAME(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    t.type = reserved.get(t.value, 'NAME')
    return t

def t_TYPE(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    t.type = types.gen(t.value, 'INT')
    return t
    

def t_NUMBER(t):
    r'\d+'
    try:
        t.value = int(t.value)
    except ValueError:
        print('int too big')
        t.value = 0
    return t
        
t_ignore = ' \t'
def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")
    
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)
    
# Build the lexer
import ply.lex as lex
lexer = lex.lex()

# Parsing rules

precedence = (
    ('left', 'COMMA'),
    ('left', 'EQUALS', 'NOTEQ'),
    ('left','PLUS','MINUS'),
    ('left','TIMES','DIVIDE', 'MOD'),
    #('right','UMINUS'),
    ('right', 'DEREF'),
    ('right', 'AMP'),
    ('right', 'ATSYM')
    )

# dictionary of names
namepos = 1
names = { }

def p_program(t):
    'program : statements'
    t[0] = ('program', t[1])

def p_statements_single(t):
    'statements : statement'
    t[0] = ('statements', [t[1]])

def p_statements_mult(t):
    'statements : statements statement'
    t[0] = ('statements', t[1][1] + [t[2]])

def p_statement_assign(t):
    'statement : NAME ASSIGN expression SEMICOLON'
    t[0] = ('assign-statement', t[1], t[3])

def p_statement_declare(t):
    'statement : VAR NAME SEMICOLON'
    t[0] = ('declare-statement', t[2])

def p_statement_declaren(t):
    'statement : VAR LBRACKET NUMBER RBRACKET NAME SEMICOLON'
    t[0] = ('declare-statement', t[5], t[3])

def p_statement_expr(t):
    'statement : expression SEMICOLON'
    t[0] = ('expr-statement', t[1])
#CARRY IBT NERD
def p_statement_if(t):
    'statement : IF expression statement'
    t[0] = ('if-statement', t[2], t[3])

def p_statement_while(t):
    'statement : WHILE expression statement'
    t[0] = ('while-statement', t[2], t[3])

#def p_statement_else(t):
#    'statement : ELSE statement'
#    t[0] = ('else-statement', t[2]) 

def p_statement_block(t):
    'statement : DO statements END'
    t[0] = ('block-statement', t[2])

def p_statement_defun(t):
    'statement : FN NAME LPAREN list RPAREN statement'
    t[0] = ('fundef-statement', t[2], t[4], t[6])

def p_list_atom(t):
    'list : expression'
    t[0] = ('list', [t[1]])

def p_list_mult(t):
    'list : list COMMA expression'
    t[0] = ('list', t[1][1] + [t[3]])

def p_expression_binop(t):
    '''expression : expression PLUS expression
                  | expression MINUS expression
                  | expression EQUALS expression
                  | expression NOTEQ expression
                  | expression TIMES expression
                  | expression MOD expression
                  | expression DIVIDE expression'''
    t[0] = ('binary-expr', t[2], t[1], t[3])

def p_expression_uderef(t):
    'expression : DEREF expression'
    t[0] = ('deref-expr', t[2])

def p_expression_uaddrof(t):
    'expression : AMP NAME'
    t[0] = ('addrof-expr', t[2])

def p_expression_ureg(t):
    'expression : ATSYM NAME'
    t[0] = ('regat-expr', t[2])
#def p_expression_uminus(t):
#    'expression : MINUS expression %prec UMINUS'
#    t[0] = ('negate-expr', t[2])

def p_expression_group(t):
    'expression : LPAREN expression RPAREN'
    t[0] = t[2]

def p_expression_number(t):
    'expression : NUMBER'
    t[0] = ('number-expr', t[1])

def p_expression_funcal(t):
    'expression : NAME LPAREN list RPAREN'
    t[0] = ('funcall-expr', t[1], t[3])

def p_expression_list(t):
    'expression : LBRACKET list RBRACKET'
    t[0] = ('list-expr', t[2])

def p_expression_name(t):
    'expression : NAME'
    t[0] = ('name-expr', t[1])

def p_expression_nameoffset(t):
    'expression : NAME LBRACKET NUMBER RBRACKET'
    t[0] = ('offset-expr', t[1], t[3])

def p_error(t):
    print("Syntax error at '%s'" % t.value)


import ply.yacc as yacc
import sys
import gen
parser = yacc.yacc()

with open(sys.argv[1], 'r') as program:
    code = program.read()
    ast = parser.parse(code)
    gen = gen.CodeGen(ast)
    print(gen.gen_program())
