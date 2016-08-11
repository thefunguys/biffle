class CodeGen(object):
    def __init__(self, ast):
        self.ast = ast
        self.names = {}
        self.functions = {}
        self.code = '.start\n'
        self.header = 'jump .start\n'
        self.labelctr = 1
        self.memptr = 1

    def gen_instr(self, instr):
        self.code += instr + '\n'

    def gen_funinstr(self, instr):
        self.header += instr + '\n'

    def gen_program(self):
        self.code_gen(self.ast)
        return self.header + self.code

    def get_next_mem(self, size=1):
        addr = self.memptr
        self.memptr += size
        return addr

    def get_next_label(self, base):
        label = '.' + base + str(self.labelctr)
        self.labelctr += 1
        return label

    def code_gen(self, ast):
        if len(ast) == 0:
            return
        if ast[0] == 'program':
            self.code_gen(ast[1])
            self.gen_instr('hlt')
            
        if ast[0] == 'statements':
            for statement in ast[1]:
                self.code_gen(statement)
        if ast[0] == 'declare-statement':
            if ast[1] not in self.names:
                size = 1
                if len(ast) > 2:
                    size = ast[2]
                self.names[ast[1]] = (self.get_next_mem(), size)
        if ast[0] == 'assign-statement':
            self.code_gen(ast[2])
            self.gen_instr('set zwei %d' % self.names[ast[1]][0])
            self.gen_instr('store ein zwei')
        if ast[0] == 'expr-statement':
            print(';expr-st')
            self.code_gen(ast[1])
            print(';end-expr-st')
        if ast[0] == 'if-statement':
            iflabel = self.get_next_label('if')
            endlabel = self.get_next_label('end')
            self.code_gen(ast[1])
            self.gen_instr('bif ein %s' % iflabel)
            self.gen_instr('jump %s' % endlabel)
            self.gen_instr(iflabel)
            self.code_gen(ast[2])
            self.gen_instr(endlabel)
        if ast[0] == 'while-statement':
            looplabel = self.get_next_label('loop')
            endlabel = self.get_next_label('end')
            contlabel = self.get_next_label('cont')
            self.gen_instr(looplabel)
            self.code_gen(ast[1])
            self.gen_instr('bif ein %s' % contlabel)
            self.gen_instr('jump %s' % endlabel)
            self.gen_instr(contlabel)
            self.code_gen(ast[2])
            self.gen_instr('jump %s' % looplabel)
            self.gen_instr(endlabel)
        if ast[0] == 'block-statement':
            self.code_gen(ast[1])
        if ast[0] == 'regat-expr':
            if ast[1] != 'ein':
                self.gen_instr('mov ein %s' % ast[1])
        if ast[0] == 'fundef-statement':
            oldcode = self.code
            self.code = ''
            self.gen_instr('.' + ast[1])
            for arg in ast[2][1][::-1]:
                self.gen_instr('pop ein')
                self.code_gen(('declare-statement', arg[1]))
                self.code_gen(('assign-statement', arg[1], ('regat-expr', 'ein')))
                
            self.gen_instr('push sc')
            self.code_gen(ast[3])
            self.gen_instr('pop sc')
            self.gen_instr('ret')
            self.header += self.code
            self.code = oldcode
            
            #TODO: complete this
        if ast[0] == 'funcall-expr':
            if ast[1] == 'put':
                print(';put')
                self.code_gen(ast[2][1][0])
                self.gen_instr('put ein')
            elif ast[1] == 'printn':
                self.code_gen(ast[2][1][0])
                self.gen_instr('printn ein')
                self.gen_instr('set zwei 10')
                self.gen_instr('put zwei')
            else:
                for arg in ast[2][1]:
                    self.code_gen(arg)
                    self.gen_instr('push ein')
                self.gen_instr('call .%s' % ast[1])
                self.gen_instr('noop')
            
        if ast[0] == 'binary-expr':
            self.code_gen(ast[3])
            self.gen_instr('push ein')
            self.code_gen(ast[2])
            self.gen_instr('pop zwei')
            if ast[1] == '+':
                self.gen_instr('add ein zwei')
            if ast[1] == '-':
                self.gen_instr('sub ein zwei')
            if ast[1] == '==':
                self.gen_instr('comp ein zwei')
            if ast[1] == '!=':
                self.gen_instr('cne ein zwei')
            if ast[1] == '*':
                self.gen_instr('mult ein zwei')
            if ast[1] == '/':
                self.gen_instr('div ein zwei')
            if ast[1] == '%':
                self.gen_instr('mod ein zwei')

        if ast[0] == 'number-expr':
            self.gen_instr('set ein %d' % ast[1])
        if ast[0] == 'name-expr':
            self.gen_instr('set zwei %d' % self.names[ast[1]][0])
            self.gen_instr('load ein zwei')
        if ast[0] == 'offset-expr':
            self.gen_instr('set zwei %d' % self.names[ast[1]][0])
            self.gen_instr('addi zwei %d' % ast[2])
            self.gen_instr('load ein zwei')
        if ast[0] == 'deref-expr':
            self.code_gen(ast[1])
            self.gen_instr('mov zwei ein')
            self.gen_instr('load ein zwei')
        if ast[0] == 'addrof-expr':
            self.gen_instr('set ein %d' % self.names[ast[1]][0])
            
            
