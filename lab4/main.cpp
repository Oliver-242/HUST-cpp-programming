#include"Mat.h"

extern const char* TestMAT(int& s);	//用于实验四，可以放在主函数之前

int main(int argc, char* argv[]) 					//请扩展main()测试其他运算
{
	//MAT<float>   a(1, 2), b(2, 2), c(1, 2);   //更改模板中元素类型即可测试其他情况

	//d[0][0] = 6; d[0][1] = 8;
	//char t[2048];
	//a[0][0] = 1.0; a[0][1] = 2.0; 			//等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”

	//b[0][0] = 3; 	b[0][1] = 4;		//调用T* const operator[ ](int r)初始化数组元素
	//b[1][0] = 5; 	b[1][1] = 6;

	//c[0][0] = 2; c[0][1] = 3;

	//cout << "初始两个矩阵" << endl;
	//cout << "a" << endl;
	//cout << a.print(t) << endl;
	//cout << "b" << endl;
	//cout << b.print(t) << endl;

	//cout << "乘法测试" << endl;
	//c = a * b;						//测试矩阵乘法运算
	//cout << c.print(t) << endl;

	//cout << "*=测试" << endl;
	//a *= b;
	//cout<<a.print(t)<<endl;

	//cout << "加法测试" << endl;
	//a = a + c;
	//cout<<a.print(t)<<endl;					//测试矩阵加法运算
	//cout << "+=测试" << endl;
	//c += a;							//测试矩阵“+=”运算
	//cout<<c.print(t)<<endl;
	//
	//cout << "减法测试" << endl;
	//c = c - a;						//测试矩阵减法运算
	//cout<<c.print(t)<<endl;
	//cout << "-=测试" << endl;
	//c -= a;
	//cout << c.print(t) << endl;
	//
	//cout << "转置测试" << endl;
	//c = ~b;							//测试矩阵转置运算
	//cout<<c.print(t)<<endl;

	int s;
	const char* e = TestMAT(s);
	cout << s << " " << e << endl;
	return 0;
}
