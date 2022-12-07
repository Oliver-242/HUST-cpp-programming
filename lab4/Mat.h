#define _CRT_SECURE_NO_WARNINGS 


#include <iostream>
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;


template <typename T>
class MAT {
	T* const e;							//ָ���������;���Ԫ�ص�ָ��
	const int r, c;							//�������r����c��С
public:
	MAT(int r, int c);						//������
	MAT(const MAT& a);				//�������
	MAT(MAT&& a)noexcept;			//�ƶ�����
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a)const;	//����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a)const;	//������������ܼ����쳣
	virtual MAT operator*(const MAT& a)const;	//����˷������ܳ����쳣
	virtual MAT operator~()const;					//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT<T>& operator*=(const MAT& a);		//��*=������
	virtual char* print(char* s)const noexcept;     //print�����s������s�����ÿո���������ûس�����
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
	else throw("r������ȡֵ��Χ��");
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
	else throw("����������ȫ��ͬ������ӣ�");
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
	else throw("����������ȫ��ͬ���������");
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
	else throw("����������������Ҿ�������������ˣ�");
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
	else throw("����������ȫ��ͬ������ӣ�");
}

template<typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a) {
	if (r == a.r && c == a.c) {
		for (int i = 0; i < r * c; i++) {
			this->e[i] -= a.e[i];
		}
		return *this;
	}
	else throw("����������ȫ��ͬ���������");
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
	else throw("����������������Ҿ�������������ˣ�");
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


template MAT<int>;			//����ʵ���ģ��������ģ�嶨���ļ���β��������ǿ��ʵ����
template MAT<long long>;		//����ʵ���ģ��������ģ�嶨���ļ���β��������ǿ��ʵ����