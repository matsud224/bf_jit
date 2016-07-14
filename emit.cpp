#include <string.h>
#include <stdint.h>
#include "emit.h"

void movabs_r8_imm8(void *imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x49, 0xB8, 0xEF, 0xBE, 0xAD, 0xDE, 0xEF, 0xBE, 0xAD, 0xDE };
	memcpy(code+2, &imm, 8);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void inc_r8(uint8_t *dest, int *index){
	uint8_t code[] = { 0x49, 0xFF, 0xC0 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void dec_r8(uint8_t *dest, int *index){
	uint8_t code[] = { 0x49, 0xFF, 0xC8 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void add_r8_imm4(int32_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x49, 0x81, 0xC0, 0x34, 0x12, 0x34, 0x12 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void sub_r8_imm4(int32_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x49, 0x81, 0xE8, 0x34, 0x12, 0x34, 0x12 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void inc_r8id_byte(uint8_t *dest, int *index){
	uint8_t code[] = { 0x41, 0xFE, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void dec_r8id_byte(uint8_t *dest, int *index){
	uint8_t code[] = { 0x41, 0xFE, 0x08 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void add_r8id_imm1(int8_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x41, 0x80, 0x00, 0x12 };
	memcpy(code+3, &imm, 1);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void sub_r8id_imm1(int8_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x41, 0x80, 0x28, 0x12 };
	memcpy(code+3, &imm, 1);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rax_imm4(int32_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rdi_imm4(int32_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x48, 0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rdx_imm4(int32_t imm, uint8_t *dest, int *index){
	uint8_t code[] = { 0x48, 0xC7, 0xC2, 0x01, 0x00, 0x00, 0x00 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rsi_r8(uint8_t *dest, int *index){
	uint8_t code[] = { 0x4C, 0x89, 0xC6 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void cmp_r8id_0_byte(uint8_t *dest, int *index){
	uint8_t code[] = { 0x41, 0x80, 0x38, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void ret(uint8_t *dest, int *index){
	uint8_t code[] = { 0xC3 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void syscall(uint8_t *dest, int *index){
	uint8_t code[] = { 0x0F, 0x05 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

int jz_dword(uint8_t *dest, int *index){
	int modify_index = *index + 2;
	uint8_t code[] = { 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return modify_index;
}

int jnz_dword(uint8_t *dest, int *index){
	int modify_index = *index + 2;
	uint8_t code[] = { 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return modify_index;
}
