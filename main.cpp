#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include "emit.h"

using namespace std;

char tape[30000];

int main(void)
{
    uint8_t *code = (uint8_t *)mmap(NULL, 4096*200, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    int (*func)(void) = (int(*)(void))code;
	int index=0;

    if(code == MAP_FAILED){
		perror(NULL);
		return -1;
    }

    char c;
    stack<int32_t> lbrackets;
	int32_t ptradd = 0;
	int8_t ptridadd = 0;
    movabs_r8_imm8(tape, code, &index); /* r8レジスタがテープを指す */
    while((c=getchar()) != EOF){
		if(c!='>' && c!='<'){
			if(ptradd==1)
				inc_r8(code, &index);
			else if (ptradd==-1)
				dec_r8(code, &index);
			else if (ptradd>0)
				add_r8_imm4(ptradd, code, &index);
			else if (ptradd<0)
				sub_r8_imm4(-ptradd, code, &index);

			ptradd=0;
		}
		if(c!='+' && c!='-'){
			if(ptridadd==1)
				inc_r8id_byte(code, &index);
			else if (ptridadd==-1)
				dec_r8id_byte(code, &index);
			else if (ptridadd>0)
				add_r8id_imm1(ptridadd, code, &index);
			else if (ptridadd<0)
				sub_r8id_imm1(-ptridadd, code, &index);

			ptridadd=0;
		}

		switch(c){
		case '>':
			ptradd++;
			break;
		case '<':
			ptradd--;
			break;
		case '+':
			ptridadd++;
			break;
		case '-':
			ptridadd--;
			break;
		case ',':
			mov_rax_imm4(0, code, &index);
			mov_rdi_imm4(0, code, &index);
			mov_rsi_r8(code, &index);
			mov_rdx_imm4(1, code, &index);
			syscall(code, &index);
			break;
		case '.':
			mov_rax_imm4(1, code, &index);
			mov_rdi_imm4(1, code, &index);
			mov_rsi_r8(code, &index);
			mov_rdx_imm4(1, code, &index);
			syscall(code, &index);
			break;
		case '[':
			cmp_r8id_0_byte(code, &index);
			lbrackets.push(jz_dword(code, &index));
			lbrackets.push(index);
			break;
		case ']':
			if(lbrackets.empty()){
				fprintf(stderr, "\nerror: no matching rbracket!\n");
				return -1;
			}

			cmp_r8id_0_byte(code, &index);
			int32_t rb_modify_index = jnz_dword(code, &index);

			int32_t jz_next_inst_index = lbrackets.top();	lbrackets.pop();
			int32_t lb_modify_index = lbrackets.top();		lbrackets.pop();
			int32_t jz_distance = index - jz_next_inst_index;
			int32_t jnz_distance = -jz_distance;
			memcpy(code + lb_modify_index, &jz_distance, 4);
			memcpy(code + rb_modify_index, &jnz_distance, 4);

			break;
		}
    }

    ret(code, &index);

    if(!lbrackets.empty()){
		fprintf(stderr, "\nerror: no matching lbracket!\n");
		return -1;
	}

    func();

    munmap(code, 4096);
    return 0;
}
