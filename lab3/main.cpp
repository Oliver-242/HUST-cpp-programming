#include"Stack.h"

extern const char* TestSTACK(int& s);	//用于实验三，可以放在主函数之前

int main(int argc, char* argv[]) {
	int s;
	const char* e = TestSTACK(s);
	cout << s << " " << e << endl;
	return 0;
}
