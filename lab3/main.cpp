#include"Stack.h"

extern const char* TestSTACK(int& s);	//����ʵ���������Է���������֮ǰ

int main(int argc, char* argv[]) {
	int s;
	const char* e = TestSTACK(s);
	cout << s << " " << e << endl;
	return 0;
}
