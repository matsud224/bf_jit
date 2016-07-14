#include <stdint.h>

void movabs_r8_imm8(void *imm, uint8_t *dest, int *index);
void inc_r8(uint8_t *dest, int *index);
void dec_r8(uint8_t *dest, int *index);
void inc_r8id_byte(uint8_t *dest, int *index);
void dec_r8id_byte(uint8_t *dest, int *index);
void add_r8_imm4(int32_t imm, uint8_t *dest, int *index);
void sub_r8_imm4(int32_t imm, uint8_t *dest, int *index);
void add_r8id_imm1(int8_t imm, uint8_t *dest, int *index);
void sub_r8id_imm1(int8_t imm, uint8_t *dest, int *index);
void mov_rax_imm4(int32_t imm, uint8_t *dest, int *index);
void mov_rdi_imm4(int32_t imm, uint8_t *dest, int *index);
void mov_rdx_imm4(int32_t imm, uint8_t *dest, int *index);
void mov_rsi_r8(uint8_t *dest, int *index);
void cmp_r8id_0_byte(uint8_t *dest, int *index);
void ret(uint8_t *dest, int *index);
void syscall(uint8_t *dest, int *index);
int jz_dword(uint8_t *dest, int *index);
int jnz_dword(uint8_t *dest, int *index);
