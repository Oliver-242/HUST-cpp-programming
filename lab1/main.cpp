#include"queue.h"

extern const char* TestQueue(int& s);	//����ʵ��һ�����Է���������֮ǰ

int main(int argc, char* argv[]) {
	int s;
	const char* e = TestQueue(s);
	cout << s << " " << e << endl;
	return 0;
}


