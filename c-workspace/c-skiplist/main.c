#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skiplist.h"

#define KV_TBL_SZ		1024

int kv_table[KV_TBL_SZ];
unsigned int global_seed = 0xabcd; // 난수 생성을 위한 seed

void generate_kv_pair() {
	for (int i = 0; i < KV_TBL_SZ; i++)
		kv_table[i] = i; // key - 값 쌍
}

int get_test_kv() {
	return rand() % KV_TBL_SZ;
}

int skiplist_strcmp(void* a, void* b) { 
	return strcmp((char*)a, (char*)b); // char a가 크면 1, 작으면 -1, 같으면 0
}

int skiplist_intcmp(void* ia, void* ib) {
	int a = *((int*)ia);
	int b = *((int*)ib);

	int res = a < b ? -1 : a > b ? 1 : 0; // int a가 크면 1, 작으면 -1, 같으면 0
	return res;
}

void skiplist_print_int_kv(void* lkey, void* lvalue) {
	int key = *((int*)lkey);
	int value = *((int*)lvalue);

	printf("key = %d, value = %d\n", key, value);
}

void skiplist_print_str_kv(void* lkey, void* lvalue) {
	char* key = lkey;
	char* value = lvalue;

	printf("key = %s, value = %s\n", key, value);
}

int main() {
	int kv, res;
	void* value;
	struct skiplist* sl;

	sl = skiplist_create(skiplist_intcmp, skiplist_print_int_kv, global_seed);
	if (!sl) {
		printf("fail to creat skiplist!");
		exit(-1);
	}
	generate_kv_pair();

	for (int i = 0; i < KV_TBL_SZ; i++) {
		kv = get_test_kv();
		res = skiplist_add(sl, &kv_table[kv], &kv_table[kv]);
		if (!res) {
			printf("skiplist_add fails!");
			exit(-1);
		}

		res = skiplist_get(sl, &kv_table[kv], &value);
		if (!res) {
			printf("skiplist_get fails!");
			exit(-1);
		}

		if (*((int*)value) != kv_table[kv]) {
			printf("value does not match!");
			exit(-1);
		}

		if (skiplist_count(sl) != i + 1) {
			printf("the number of nodes do not match!");
			exit(-1);
		}
	}

	skiplist_debug(sl);

	res = skiplist_destroy(sl);
	if (res != KV_TBL_SZ) {
		printf("Error: inputs != nodes\n");
		exit(-1);
	}

	printf("Done!\n");

	return 0;
}
