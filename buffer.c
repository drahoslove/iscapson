#include "buffer.h"

void initBuffer(Buffer* buffer, unsigned int size) {
	size++;
	buffer->data = malloc(sizeof(*buffer->data)*size);
	if (buffer->data == NULL) {
		fprintf(stderr, "Malloc failed");
		exit(1);
	}
	buffer->size = size;
	buffer->e_index = 0;
	buffer->s_index = 0;
	for (int i = 0; i < size; ++i){
		buffer->data[i] = '\0';
	}
}

char popBuffer(Buffer* buffer){
	char val = buffer->data[buffer->s_index];
	buffer->s_index = (buffer->s_index+1) % buffer->size;
	return isEmpty(buffer) ? '\0' : val;
}

void pushBuffer(Buffer *buffer, char value) {
	if (isFull(buffer)) {
		popBuffer(buffer);
	}
	buffer->data[buffer->e_index] = value;
	buffer->e_index = (buffer->e_index+1) % buffer->size;
}

void forEachInBuffer(Buffer* b, void (*func)(char)){
	if (isEmpty(b)) {
		return;
	}
	for (int i = b->s_index; i != b->e_index; i = (i+1)%b->size) {
		(*func)(b->data[i]);
	}
}
