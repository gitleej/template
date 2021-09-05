#pragma once
#include <iostream>
#include <string>

using namespace std;

template<class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age);
	~Person();

	void showPerson();

	T1 m_name;
	T2 m_age;
};

//template<class T1, class T2>
//Person<T1, T2>::Person(T1 name, T2 age) {
//	this->m_name = name;
//	this->m_age = age;
//}
//
//template<class T1, class T2>
//Person<T1, T2>::~Person() {
//	
//}
//
//template<class T1, class T2>
//void Person<T1, T2>::showPerson() {
//	cout << "������" << this->m_name << "���䣺" << this->m_age << endl;
//}