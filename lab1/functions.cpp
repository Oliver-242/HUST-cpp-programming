#include"queue.h"
#include<stdlib.h>

void initQueue(Queue* const p, int m) {
	(int*&)(p->elems) = (int*)malloc(m * sizeof(int));
	(int&)(p->max) = m;
	p->head = p->tail = 0;
}

void initQueue(Queue* const p, const Queue& s) {
	(int&)(p->max) = s.max;
	(int*&)(p->elems) = (int*)malloc(p->max * sizeof(int));
	memcpy(p->elems, s.elems, p->max * sizeof(int));
	p->head = s.head;
	p->tail = s.tail;
}

void initQueue(Queue* const p, Queue&& s) {
	(int*&)(p->elems) = s.elems;
	(int*&)(s.elems) = nullptr;
	(int&)(p->max) = s.max;
	p->head = s.head;
	p->tail = s.tail;
	s.head = s.tail = 0;
	(int&)s.max = 0;
}

int  number(const Queue* const p){
	int i;
	if ((i = p->tail - p->head) >= 0) return i;
	else return p->max + i;
}	

int  size(const Queue* const p){
	return p->max;
}			

Queue* const enter(Queue* const p, int e) {
	if (p->max - 1 > number(p)) {
		p->elems[p->tail] = e;
		if (p->tail == p->max - 1) p->tail = 0;
		else (p->tail)++;
		return p;
	}
	else throw("Queue is full!");
}

Queue* const leave(Queue* const p, int& e){
	if (number(p) != 0) {
		e = p->elems[p->head];
		if (p->head == p->max - 1) p->head = 0;
		else (p->head)++;
		return p;
	}
	else throw("Queue is empty!");
}

Queue* const assign(Queue* const p, const Queue& q){
	if (p == &q) return p;
	(int&)(p->max) = q.max;
	if(p->elems != nullptr) free(p->elems);
	(int*&)(p->elems) = (int*)malloc(p->max * sizeof(int));
	p->head = q.head;
	p->tail = q.tail;
	memcpy(p->elems, q.elems, (p->max)*sizeof(int));
	return p;
}

Queue* const assign(Queue* const p, Queue&& q) {
	if (p == &q) return p;

	(int&)(p->max) = q.max;
	(int*&)(p->elems) = q.elems;
	p->head = q.head;
	p->tail = q.tail;

	(int*&)(q.elems) = nullptr;
	q.head = q.tail = 0;
	(int&)q.max = 0;
	return p;
}

char* print(const Queue* const p, char* s) {
	if (number(p) == 0) return nullptr;
	int head2 = p->head;
	int  i = 0, j, k;
	while (head2 != p->tail) {
		for (j = p->elems[head2]; j != 0; j /= 10) i++;
		s[i] = ',';
		for (j = p->elems[head2], k = 0; j != 0; j /= 10, k++) {
			s[i - k - 1] = j % 10 + '0';
		}
		i++;
		if (head2 == p->max - 1) head2 = 0;
		else head2++;
	}
	s[i] = '\0';
	return s;
}

void destroyQueue(Queue* const p) {
	(int*&)(p->elems) = nullptr;
	(int&)(p->max) = 0;
	p->head = p->tail = 0;
	(Queue*&)p = nullptr;
}