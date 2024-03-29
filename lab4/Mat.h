#define _CRT_SECURE_NO_WARNINGS 


#include <iostream>
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;


template <typename T>
class MAT {
	T* const e;							//指向所有整型矩阵元素的指针
	const int r, c;							//矩阵的行r和列c大小
public:
	MAT(int r, int c);						//矩阵定义
	MAT(const MAT& a);				//深拷贝构造
	MAT(MAT&& a)noexcept;			//移动构造
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a)const;	//矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a)const;	//矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法，不能乘抛异常
	virtual MAT operator~()const;					//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT<T>& operator*=(const MAT& a);		//“*=”运算
	virtual char* print(char* s)const noexcept;     //print输出至s并返回s：列用空格隔开，行用回车结束
};

template<typename T>
MAT<T>::MAT(int r, int c) : MAT::r(r), MAT::c(c), e(new T[r * c]) {

}

template<typename T>
MAT<T>::MAT(const MAT& a) : MAT::r(a.r), MAT::c(a.c), e(new T[a.r * a.c]) {
	memcpy(e, a.e, r * c * sizeof T);
}

template<typename T>
MAT<T>::MAT(MAT&& a) noexcept : MAT::e((T*&&)a.e), MAT::c(a.c), MAT::r(a.r) {
	(T*&)a.e = nullptr;
	(int&)a.r = 0;
	(int&)a.c = 0;
}

template<typename T>
MAT<T>::~MAT() noexcept {
	if (e != nullptr) {
		delete[] e;
		(T*&)e = nullptr;
		(int&)r = (int&)c = 0;
	}
}

template<typename T>
T* const MAT<T>::operator[](int r) {
	if (r >= 0 && r < MAT::r) {
		return &e[r * c];
	}
	else throw("r超出了取值范围！");
}

template<typename T>
MAT<T> MAT<T>::operator+(const MAT& a) const {
	if (r == a.r && c == a.c) {
		MAT<T> wuhu(*this);
		for (int i = 0; i < r * c; i++) {
			wuhu.e[i] += a.e[i];
		}
		return wuhu;
	}
	else throw("行列数不完全相同不能相加！");
}

template<typename T>
MAT<T> MAT<T>::operator-(const MAT& a) const {
	if (r == a.r && c == a.c) {
		MAT<T> wuhu(*this);
		for (int i = 0; i < r * c; i++) {
			wuhu.e[i] -= a.e[i];
		}
		return wuhu;
	}
	else throw("行列数不完全相同不能相减！");
}

template<typename T>
MAT<T> MAT<T>::operator*(const MAT& a) const {
	if (this->c == a.r) {
		MAT<T> wuhu(this->r, a.c);
		T sum;
		for (int i = 0; i < wuhu.r; i++) {
			for (int j = 0; j < wuhu.c; j++) {
				sum = 0;
				for (int k = 0; k < this->c; k++) {
					sum += this->e[i * this->c + k] * a.e[k * a.r + j];
				}
				wuhu.e[i * wuhu.c + j] = sum;
			}
		}
		return wuhu;
	}
	else throw("左矩阵列数不等于右矩阵行数不能相乘！");
}

template<typename T>
MAT<T> MAT<T>::operator~() const {
	MAT<T> wuhu(this->c, this->r);
	for (int i = 0; i < wuhu.r; i++) {
		for (int j = 0; j < wuhu.c; j++) {
			wuhu.e[i * wuhu.c + j] = this->e[j * this->c + i];
		}
	}
	return wuhu;
}

template<typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) {
	if (this == &a) return *this;
	(int&)r = a.r;
	(int&)c = a.c;
	if (this->e != nullptr) {
		delete[] e;
		(T*&)e = new T[r * c];
	}
	memcpy(this->e, a.e, r * c * sizeof T);
	return *this;
}

template<typename T>
MAT<T>& MAT<T>::operator=(MAT&& a) noexcept {
	if (this == &a) return a;
	(int&)r = a.r;
	(int&)c = a.c;
	(T*&)e = a.e;
	(T*&)a.e = nullptr;
	(int&)a.r = (int&)a.c = 0;
	return *this;
}

template<typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a) {
	if (r == a.r && c == a.c) {
		for (int i = 0; i < r * c; i++) {
			this->e[i] += a.e[i];
		}
		return *this;
	}
	else throw("行列数不完全相同不能相加！");
}

template<typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a) {
	if (r == a.r && c == a.c) {
		for (int i = 0; i < r * c; i++) {
			this->e[i] -= a.e[i];
		}
		return *this;
	}
	else throw("行列数不完全相同不能相减！");
}

template<typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a) {
	if (this->c == a.r) {
		MAT<T> wuhu(this->r, a.c);
		T sum;
		for (int i = 0; i < wuhu.r; i++) {
			for (int j = 0; j < wuhu.c; j++) {
				sum = 0;
				for (int k = 0; k < this->c; k++) {
					sum += this->e[i * this->c + k] * a.e[k * a.r + j];
				}
				wuhu.e[i * wuhu.c + j] = sum;
			}
		}
		*this = wuhu;
		wuhu.~MAT();
		return *this;
	}
	else throw("左矩阵列数不等于右矩阵行数不能相乘！");
}

template<typename T>
char* MAT<T>::print(char* s) const noexcept {
	char* t = s;
	for (int i = 0; i < this->r; i++) {
		for (int j = 0; j < this->c; j++) {
			if (!strcmp(typeid(T).name(), "int"))
				s += sprintf(s, "%6d", this->e[i * this->c + j]);
			else if (!strcmp(typeid(T).name(), "__int64"))
				s += sprintf(s, "%6lld", this->e[i * this->c + j]);
			else if (!strcmp(typeid(T).name(), "double"))
				s += sprintf(s, "%8lf", this->e[i * this->c + j]);
			else if (!strcmp(typeid(T).name(), "float"))
				s += sprintf(s, "%8f", this->e[i * this->c + j]);

			if (j + 1 != this->c) s += sprintf(s, "%c", ' ');
		}
		s += sprintf(s, "%c", '\n');
	}
	s += sprintf(s, "%c", '\0');
	return t;
}


template MAT<int>;			//用于实验四，必须放在模板定义文件的尾部，用于强制实例化
template MAT<long long>;		//用于实验四，必须放在模板定义文件的尾部，用于强制实例化