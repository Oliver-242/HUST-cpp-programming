#include"Stack.h"

QUEUE::QUEUE(int m) : elems(new int[m]), max(m) {
	head = tail = 0;
}

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max) {
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
	(int*&)q.elems = nullptr;
	(int&)q.max = 0;
	q.head = q.tail = 0;
	return *this;
}

char* QUEUE::print(char* s) const noexcept {
	for (int i = head; i != tail; i = (i + 1)%max) {
		s = s + sprintf(s, "%d", elems[i]);
		if ((i + 1) % max == tail) {
			s += sprintf(s, "%c", '\0');
		}
		else {
			s += sprintf(s, "%c", ',');
		}
	}
	return s;
}

QUEUE::~QUEUE() {
	if (elems != nullptr) {
		delete[] elems;
		(int*&)elems = nullptr;
		(int&)max = 0;
		head = tail = 0;
	}
}

STACK::STACK(int m) : QUEUE(m), q(m) {

}

STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {

}

STACK::STACK(STACK&& s) noexcept : QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {

}

int STACK::size() const noexcept {
	return QUEUE::size() * 2;
}

STACK::operator int() const noexcept {
	return QUEUE::operator int() + int(q);
}

STACK& STACK::operator<<(int e) {
	if (operator int() >= size() - 2) throw("STACK is full!");
	else if (QUEUE::operator int() == QUEUE::size() - 1) {
		int trans;
		QUEUE::operator>>(trans);
		q << trans;
	}
	QUEUE::operator<<(e);
	return *this;
}

STACK& STACK::operator>>(int& e) {
	if (operator int() == 0) throw("STACK is empty!");
	int i, trans;
	for (i = 1; i <= QUEUE::operator int() - 1; i++) {    //实现将队尾元素移至对头保持其他元素顺序不变
		QUEUE::operator>>(trans);
		QUEUE::operator<<(trans);
	}
	QUEUE::operator>>(e);
	if (int(q) != 0) {
		for (i = 1; i <= int(q) - 1; i++) {
			q >> (trans);
			q << (trans);
		}
		q >> trans;     //取出子类队列的队尾
		QUEUE::operator<<(trans);
		for (i = 1; i <= QUEUE::operator int() - 1; i++) {    //调整顺序
			QUEUE::operator>>(trans);
			QUEUE::operator<<(trans);
		}
	}
	return *this;
}

STACK& STACK::operator=(const STACK& s) {
	q = s.q;
	QUEUE::operator=(s);
	return *this;
}

STACK& STACK::operator=(STACK&& s) noexcept {
	q = (QUEUE&&)s.q;
	QUEUE::operator=((QUEUE&&)s);
	return *this;
}

char* STACK::print(char* b) const noexcept {
	if (int(q) != 0)
	{
		q.print(b);
		int len = strlen(b);
		b[len] = ',';
		QUEUE::print(b + len + 1);
	}
	else
	{
		QUEUE::print(b);
	}
	return b;
}

STACK::~STACK() noexcept {
	QUEUE::~QUEUE();
	q.~QUEUE();
}
