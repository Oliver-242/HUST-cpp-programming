#include"QUEUE.h"

extern const char* TestQUEUE(int& s);	//����ʵ��������Է���������֮ǰ

int main(int argc, char* argv[]) {
	int s;
	const char* e = TestQUEUE(s);
	cout << s << " " << e << endl;
	return 0;
}

