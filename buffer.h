#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	unsigned int size;
	unsigned int s_index;
	unsigned int e_index;
	char * data;
} Buffer;


void initBuffer(Buffer* buffer, unsigned int size);

void pushBuffer(Buffer*, char);

char popBuffer(Buffer*);

void forEachInBuffer(Buffer*, void (*)(char));

static inline bool isEmpty(Buffer* b){
	return b->s_index == b->e_index;
}

static inline bool isFull(Buffer* b){
	return b->s_index == (b->e_index+1) % b->size;
}

static inline unsigned int getLenOfBuffer(Buffer* b){
	return (b->e_index - b->s_index) % b->size;
}

static inline char getLastInBuffer(Buffer* b){
	return isEmpty(b) ? '\0' : b->data[(b->e_index-1 + b->size) % b->size];
}

static inline char getNthInbuffer(Buffer* b, unsigned int n) {
	return getLenOfBuffer(b) < n ? '\0' : b->data[(b->e_index-1-n + b->size) % b->size];
}


static inline void emptyBuffer(Buffer* b){
	b->s_index = b->e_index = 0;
}