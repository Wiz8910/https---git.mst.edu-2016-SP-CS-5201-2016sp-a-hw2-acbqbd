#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include<vector>
#include<iostream>
#include "linkedlist.h"
using namespace std;
template<class T>
struct monomial
{
	T coeffecient;
	T power;
	monomial(const T& cof, const T& pow)
	{
	  coeffecient = cof;
	  power = pow;
	}
};
template<class T>
class polynomial
{
	private:
		vector<monomial<T> > m_terms;
	
	public:
		
		polynomial(){};
		
		polynomial(const T& coeffecient, const T& power);
		
		polynomial(const vector<T>& coeffecients, const vector<T>& powers);
	
		polynomial<T>& operator+= (const polynomial<T>& rhs);
	
		polynomial<T>& operator-= (const polynomial<T>& rhs);
	
		polynomial<T>& operator+ (const polynomial<T>& rhs)const;
	
		polynomial<T>& operator- (const polynomial<T>& rhs)const;
	
		polynomial<T>& operator== (const polynomial<T>& rhs)const;
	
		polynomial<T>& operator!= (const polynomial<T>& rhs)const;
	
		polynomial<T>& operator- ()const;
	
		polynomial<T>& operator* (const int scalar);
	
		polynomial<T>& operator= (const polynomial<T>& rhs);
	
		polynomial<T>& operator[] (const int index)const;
	
		T& operator() (const T & x)const;
	
		polynomial<T>& operator~ ()const;
	
		friend ostream& operator<< (ostream& os,const polynomial<T> data);
};

template<class T>
polynomail<T>::polynomial(const T& coeffecient, const T& power)
{
	m_terms.push_back(monomial(coeffecient,power));
}

template<class T>
polynomail<T>::polynomial(const vector<T>& coeffecient, const vector<T>& power)
{
	for(int i=0; i< coeffecient.size();i++)
		m_terms.push_back(monomial(coeffecient[i],power[i]));
}

template<class T>
polynomial<T>& operator+= (const polynomial<T>& rhs);
{
	
}

template<class T>
polynomial<T>& operator-= (const polynomial<T>& rhs);
{
	
}

template<class T>
polynomial<T>& operator+ (const polynomial<T>& rhs)const;
{
	
}

template<class T>
polynomial<T>& operator- (const polynomial<T>& rhs)const;
{
	
}

template<class T>
polynomial<T>& operator== (const polynomial<T>& rhs)const;
{
	
}

template<class T>
polynomial<T>& operator!= (const polynomial<T>& rhs)const;
{
	
}

template<class T>
polynomial<T>& operator- ()const;
{
	
}

template<class T>
polynomial<T>& operator* (const int scalar);
{
	for(int i=0; i<m_data.size();i++)
	{
		m_data[i].
	}
}

template<class T>
polynomial<T>& operator= (const polynomial<T>& rhs);
{
	
}

template<class T>
polynomial<T>& operator[] (const int index)const;
{
	
}

template<class T>
T& operator() (const T & x)const;
{
	
}

template<class T>
polynomial<T>& operator~ ()
{
	return *this * -1;
}

template<class T>
polynomial<T>& polynomail<T>::operator= (const polynomial<T>& rhs)
{
	terms = vector<monomial<T>>(rhs);
}

template<class T>
ostream& operator<< (ostream& os,const polynomial<T> & data)
{
	for(int i =0; i<data.m_terms.size();i++)
	{
		os<<m_terms[i]<<"\t";
	}
	os<<endl;
}
#include "polynomial.hpp"

#endif
