#include"QUEUE.h"

QUEUE::QUEUE(int m) : elems(new int[m]), max(m) {
	head = tail = 0;
}

QUEUE::QUEUE(const QUEUE& q) :elems(new int[q.max]), max(q.max) {
	memcpy(elems, q.elems, max * sizeof(int));
	head = q.head;
	tail = q.tail;
}

QUEUE::QUEUE(QUEUE&& q) noexcept : elems(q.elems), max(q.max) {
	head = q.head;
	tail = q.tail;
	(int*&)q.elems = nullptr;
	(int&)q.max = 0;
	q.head = q.tail = 0;
}

QUEUE::operator int() const noexcept {
	if (max == 0) return 0;
	return int((tail - head + max) % max);
}

int QUEUE::size() const noexcept
{
	return max;
}

QUEUE& QUEUE::operator<<(int e) {
	if (head == (tail + 1) % max) throw("QUEUE is full!");
	elems[tail] = e;
	tail = (tail + 1) % max;
	return *this;
}

QUEUE& QUEUE::operator>>(int& e) {
	if (head == tail) throw("QUEUE is empty!");
	e = elems[head];
	head = (head + 1) % max;
	return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& q) {
	if (this == &q) return *this;
	(int&)max = q.max;
	head = q.head;
	tail = q.tail;
	(int*&)elems = new int[max];
	memcpy(elems, q.elems, max * sizeof(int));
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&& q) noexcept {
	if (this == &q) return *this;
	(int&)max = q.max;
	head = q.head;
	tail = q.tail;
	(int*&)elems = q.elems;
	(int*&)q. elems = nullptr;
	(int&)q.max = 0;
	q.head = q.tail = 0;
	return *this;
}

char* QUEUE::print(char* s) const noexcept {
	for (int i = head; i != tail; i = (i + 1) % max) {
		s = s + sprintf(s, "%d,", elems[i]);
	}
	return s;
}

QUEUE::~QUEUE() {
	if (elems != nullptr) {
		delete [] elems;
		(int*&)elems = nullptr;
		(int&)max = 0;
		head = tail = 0;
	}
}