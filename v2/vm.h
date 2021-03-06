#pragma once

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define SP 4
#define PC 5


#define INSTR_LOADI 0x1
#define INSTR_LOADR 0x2
#define INSTR_ADD	0x3
#define INSTR_ADDR	0xB
#define INSTR_SUB	0x4
#define INSTR_SUBR	0xC
#define INSTR_PUSHI	0xD
#define INSTR_PUSHR	0xE
#define INSTR_INC	0x5 //
#define INSTR_DEC	0x6 //remove these for ret/call
#define INSTR_CMP	0x7
#define INSTR_JNZ	0x8
#define INSTR_JMP	0x9
#define INSTR_CMPR  0xA
//More
#define INSTR_HALT	0xF

int machine_encode(int instr, int reg1, int reg2, int imm);

typedef struct {
	int inst;
	int op1;
	int op2;
	int imm;
} instruction;

typedef struct {
	int r0;
	int r1;
	int r2;
	int r3;
	int pc;
	int sp;
	int stack[255];
	instruction code[100];
	int code_size;
	int stack_size;
	int cflag;
	int zflag;
	int oflag;
	int wc;
} machine;

/*
	Machine functions
	-----------------

*/

void machine_init(machine* m);
void machine_display_registers(machine *m);
instruction *machine_decode(int inst);
void machine_fill_instruction(machine *m, int inst);
void machine_add_instruction(machine *m, instruction in);
void machine_execute_instruction(machine *m, instruction *inst);
int machine_to_opcode(instruction *inp);

/*
	VM Functions
	------------

*/
//Load
void vm_loadi(machine *m, int r_index, int value);
void vm_loadr(machine *m, int r_source, int r_dest);

//Add
void vm_add(machine *m, int r_index, int value);
void vm_addr(machine *m, int r_source, int r_dest);

//Sub
void vm_sub(machine *m, int r_index, int value);
void vm_subr(machine *m, int r_source, int r_dest);


void vm_inc(machine *m, int value);
void vm_dec(machine *m, int value);

//Cmp
void vm_cmp(machine *m, int r_source, int r_dest);
void vm_cmpr(machine *m, int r_source, int r_dest);

void vm_nop(machine *m);

void vm_pushi(machine *m, int value);
void vm_pushr(machine *m, int r_index);

void vm_jmp(machine *m, int jmpto);
void vm_hlt(machine *m);

/*
	VM Tests
	------------


*/
void test_loadi(machine *m, int argc, char *argv[]);
void test_instruction(machine *m, int argc, char *argv[]);

//Misc Helpers
void input(char *str, char *buffer);
int get_int(char *input);
int filter_register(int reg);
int get_register(char *rname);
char *get_register_name(int reg);
char *get_instruction_name(int inst);
int get_register_value(machine *m, int reg);
int fsize(char *filename);

