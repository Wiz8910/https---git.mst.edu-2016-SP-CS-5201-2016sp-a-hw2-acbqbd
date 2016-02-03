//#include "polynomial.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include "arraylist.h"
using namespace std;




//forward declaration for friend function
template<typename T>
class polynomial;

template<typename T>
ostream& operator<< (ostream& os,const polynomial<T>& data);

template<typename T>
class polynomial
{
	private:
		struct monomial
		{
			T coeffecient;
			T power;
			monomial(const T& cof, const T& pow){coeffecient = cof;power = pow;}
			monomial(){	}
		};
		ArrayList<monomial> m_terms;
		void sort();
	
	public:
		
		polynomial(){};
				
		polynomial(const T& coeffecient, const T& power);
		
		polynomial(const vector<T>& coeffecients, const vector<T>& powers);
	
		polynomial<T>& operator+= (const polynomial<T>& rhs);
	
		polynomial<T>& operator-= (const polynomial<T>& rhs);
	
		polynomial<T> operator+ (const polynomial<T>& rhs)const;
	
		polynomial<T> operator- (const polynomial<T>& rhs)const;
	
		bool operator== (const polynomial<T>& rhs)const;
	
		bool operator!= (const polynomial<T>& rhs)const;
	
		polynomial<T>& operator* (const int scalar);
	
		polynomial<T>& operator= (const polynomial<T>& rhs);
	
		polynomial<T>& operator[] (const int index);
		
		polynomial<T>& operator[] (const int index)const;
	
		T operator() (const T & x)const;
	
		polynomial<T>& operator~ ();
	
		//friend std::ostream& operator<< <>(std::ostream& os,const polynomial<T> data)
		friend std::ostream& operator<< (std::ostream& os,const polynomial<T> data)
		{
			//need to output first one then iterate through, know we have at least
			//one term due to constructors
			if(data.m_terms.m_size > 0)
				os<<data.m_terms[0].coeffecient<<"x^"<<data.m_terms[0].power<<" ";
			for(int i =1; i<data.m_terms.m_size;i++)
			{
				if(data.m_terms[i].coeffecient<0)
					os<<"- "<<-1*data.m_terms[i].coeffecient<<"x^"<<data.m_terms[i].power<<" ";
				else
					
					os<<"+ "<<data.m_terms[i].coeffecient<<"x^"<<data.m_terms[i].power<<" ";
			}	
			os<<endl;
		};
};

template<class T>
polynomial<T>& polynomial<T>::operator+= (const polynomial<T>& rhs)
{
	*this = *this + rhs;
	return *this;
}

template<class T>
polynomial<T>& polynomial<T>::operator-= (const polynomial<T>& rhs)
{
	*this = *this -rhs;
	return *this;
}

template<class T>
polynomial<T> polynomial<T>::operator+ (const polynomial<T>& rhs)const
{
	//go through each item in rhs
	//find index where term should be inserted and act accordingly
	int index = 0;
	//dont want to change calling object
	polynomial<T> temp = *this;
	while(index<rhs.m_terms.m_size)
	{
		int goal_indx = 0;
		bool isthere = false;
		bool foundindx = false;
		while(goal_indx < temp.m_terms.m_size && !isthere && !foundindx )
		{
			//first test for ==
			if (temp.m_terms[goal_indx].power == rhs.m_terms[index].power)
			{
				isthere = true;
				temp.m_terms[goal_indx].coeffecient += rhs.m_terms[index].coeffecient;
			}
			//then see if we found goal index
			else if(temp.m_terms[goal_indx].power > rhs.m_terms[index].power)
			{
				foundindx = true;
			}//otherwise check next
			else 
				goal_indx ++;
		}
		//if there being true only case we don't need to insert
		if(!isthere)
		{
			//I have a feeling the number of dots needed is only gonna increase as the semester progresses
			temp.m_terms.insert(rhs.m_terms[index],goal_indx);
		}
		index++;
	}
	return temp;
}

template<class T>
polynomial<T> polynomial<T>::operator- (const polynomial<T>& rhs)const
{
	//go through each item in rhs
	//find index where term should be inserted and act accordingly
	int index = 0;
	//dont want to change calling object
	polynomial<T> temp = *this;
	while(index<rhs.m_terms.m_size)
	{
		int goal_indx = 0;
		bool isthere = false;
		bool foundindx = false;
		while(goal_indx < temp.m_terms.m_size && !isthere && !foundindx )
		{
			//first test for ==
			if (temp.m_terms[goal_indx].power == rhs.m_terms[index].power)
			{
				isthere = true;
				temp.m_terms[goal_indx].coeffecient -= rhs.m_terms[index].coeffecient;
			}
			//then see if we found goal index
			else if(temp.m_terms[goal_indx].power > rhs.m_terms[index].power)
			{
				foundindx = true;
			}//otherwise check next
			else 
				goal_indx ++;
		}
		//if there being true only case we don't need to insert
		if(!isthere)
		{
			//I have a feeling the number of dots needed is only gonna increase as the semester progresses
			temp.m_terms.insert(monomial(-1*rhs.m_terms[index].coeffecient,rhs.m_terms[index].power),goal_indx);
		}
		index++;
	}
	return temp;
}

template<class T>
bool polynomial<T>::operator== (const polynomial<T>& rhs)const
{
	if(m_terms.m_size == rhs.m_terms.m_size)
	{
		for(int i =0; i<m_terms.m_size;i++)
			if(!(m_terms[i].coeffecient==rhs.m_terms[i].coeffecient) or 
			   !(m_terms[i].power==rhs.m_terms[i].power))
				return false;
		return true;
	}
	return false;
}

template<class T>
bool polynomial<T>::operator!= (const polynomial<T>& rhs)const
{
	return !(*this == rhs);
}

template<class T>
polynomial<T>& polynomial<T>::operator* (const int scalar)
{
	for(int i =0; i<m_terms.m_size;i++)
	{
		m_terms[i].coeffecient = m_terms[i].coeffecient * scalar;
		//dont multiply power silly
		//m_terms[i].power = m_terms[i].power * scalar;
	}
	return *this;
}

template<class T>
polynomial<T>& polynomial<T>::operator[] (const int index)
{
	if(0<=index && index<m_terms.m_size)
		return m_terms[index];
	else
	{
		cout<<"invalid index"<<endl;
		return NULL;
	}
		
}

template<class T>
polynomial<T>& polynomial<T>::operator[] (const int index)const
{
	if(0<=index && index<m_terms.m_size)
		return m_terms[index];
	else
	{
		cout<<"invalid index"<<endl;
		return NULL;
	}
		
}

template<class T>
T polynomial<T>::operator() (const T & x)const
{
	T sum = 0;
	for(int i =0; i<m_terms.m_size;i++)
	{
		sum += m_terms[i].coeffecient * pow(x,m_terms[i].power);
	}
	return sum;
}

template<class T>
polynomial<T>& polynomial<T>::operator~()
{
	return *this * -1;
}

template<typename T>
polynomial<T>::polynomial(const T& coeffecient, const T& power)
{
	m_terms.insert_back(monomial(coeffecient,power));
}

template<typename T>
polynomial<T>::polynomial(const vector<T>& coeffecient, const vector<T>& power)
{
	if(coeffecient.size()!=power.size())
	{
		cout<<"Error must pass same number of coeffecients and powers";
		exit(1);
	}
	for(int i=0; i< coeffecient.size();i++)
		m_terms.insert_back(monomial(coeffecient[i],power[i]));
	sort();
}

template<typename T>
polynomial<T>& polynomial<T>::operator= (const polynomial<T>& rhs)
{
	m_terms = rhs.m_terms;
	return *this;
}

template<typename T>
void polynomial<T>::sort()
{
	//simple insertion sort to sort terms when creating or adding polynomials
	//may go back and do better sort depending on time left
	for(int i=1; i<m_terms.m_size;i++)
	{
		int j = i;
		//go till we find a lesser term than x
		//have to make sure j<max due to the possiblility of removiing a term
		while( j>0 && j<m_terms.m_size 
		       && m_terms[j-1].power>=m_terms[j].power)
		{
			// if we have two equal powers consolidate
			if(m_terms[j-1].power==m_terms[j].power)
			{
				m_terms[j-1].coeffecient = m_terms[j-1].coeffecient + m_terms[j].coeffecient;
				m_terms.remove(j);
				//don't need to decrement j since it was removed
			}
			//otherwise terms[i]>terms[j]
			else
			{
				m_terms.swap(j-1,j);
				j --;
			}
		}
	}
	
	return;
}


int main()
{
	//gonna get file to open here and error handling

	//first get input
	ifstream fin;
	polynomial<float> temp(1.2,2.3);
	do
	{
		fin.open("input.txt");
	} while (!fin);
	int num_polies;
	fin >> num_polies;
	if (num_polies <= 0)
	{
		cout << "Error, must enter 1 or more polynomials" << endl;
		exit(1);
	}
	vector<polynomial<float> > terms;
	int num_terms;
	for (int i = 0; i < num_polies; i++)
	{
		fin >> num_terms;
		if (num_terms <= 0)
		{
			cout << "Error, must enter 1 or more monomials" << endl;
			exit(1);
		}
		vector<float> coeffecients;
		vector<float> powers;
		float coeffecient;
		float power;
		for (int k = 0; k < num_terms; k++)
		{
			fin >> coeffecient;
			//cout<< coeffecient << " ";
			fin >> power;
			//cout<< power <<" ";
			coeffecients.push_back(coeffecient);
			powers.push_back(power);
		}
		//cout<<endl;
		terms.push_back(polynomial<float>(coeffecients, powers));
		coeffecients.clear();
		powers.clear();
		cout << terms[i]<<endl;
	}
	terms[0]+= terms[4];
	cout<<terms[0]<<terms[4];
	return 0;
}
