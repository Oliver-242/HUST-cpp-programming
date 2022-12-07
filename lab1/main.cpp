#include"queue.h"

extern const char* TestQueue(int& s);	//用于实验一，可以放在主函数之前

int main(int argc, char* argv[]) {
	int s;
	const char* e = TestQueue(s);
	cout << s << " " << e << endl;
	return 0;
}


