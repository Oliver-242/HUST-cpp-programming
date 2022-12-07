#include"QUEUE.h"

extern const char* TestQUEUE(int& s);	//用于实验二，可以放在主函数之前

int main(int argc, char* argv[]) {
	int s;
	const char* e = TestQUEUE(s);
	cout << s << " " << e << endl;
	return 0;
}

