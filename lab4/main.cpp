#include"Mat.h"

extern const char* TestMAT(int& s);	//����ʵ���ģ����Է���������֮ǰ

int main(int argc, char* argv[]) 					//����չmain()������������
{
	//MAT<float>   a(1, 2), b(2, 2), c(1, 2);   //����ģ����Ԫ�����ͼ��ɲ����������

	//d[0][0] = 6; d[0][1] = 8;
	//char t[2048];
	//a[0][0] = 1.0; a[0][1] = 2.0; 			//�ȼ��ڡ�*(a.operator[ ](0)+1)=2;�����ȼ��ڡ�*(a[0]+1)=2;��

	//b[0][0] = 3; 	b[0][1] = 4;		//����T* const operator[ ](int r)��ʼ������Ԫ��
	//b[1][0] = 5; 	b[1][1] = 6;

	//c[0][0] = 2; c[0][1] = 3;

	//cout << "��ʼ��������" << endl;
	//cout << "a" << endl;
	//cout << a.print(t) << endl;
	//cout << "b" << endl;
	//cout << b.print(t) << endl;

	//cout << "�˷�����" << endl;
	//c = a * b;						//���Ծ���˷�����
	//cout << c.print(t) << endl;

	//cout << "*=����" << endl;
	//a *= b;
	//cout<<a.print(t)<<endl;

	//cout << "�ӷ�����" << endl;
	//a = a + c;
	//cout<<a.print(t)<<endl;					//���Ծ���ӷ�����
	//cout << "+=����" << endl;
	//c += a;							//���Ծ���+=������
	//cout<<c.print(t)<<endl;
	//
	//cout << "��������" << endl;
	//c = c - a;						//���Ծ����������
	//cout<<c.print(t)<<endl;
	//cout << "-=����" << endl;
	//c -= a;
	//cout << c.print(t) << endl;
	//
	//cout << "ת�ò���" << endl;
	//c = ~b;							//���Ծ���ת������
	//cout<<c.print(t)<<endl;

	int s;
	const char* e = TestMAT(s);
	cout << s << " " << e << endl;
	return 0;
}
