using namespace std;

template<typename T>
ArrayList<T>::~ArrayList()
{
	m_size = 0;
	m_max = 0;
	delete [] m_data;
	m_data = NULL;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
	//if(*this != rhs)
	{
		m_size = rhs.m_size;
		m_max = rhs.m_max;
		delete [] m_data;
		m_data = new T[m_size];
		for(int i =0; i<m_size; i++)
			m_data[i]=rhs.m_data[i];
	}
	return *this;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy)
{
	//if(*this!= cpy)
	{
		m_size = cpy.m_size;
		m_max = cpy.m_max;
		m_data = new T[m_size];
		for(int i =0; i<m_size; i++)
			m_data[i]=cpy.m_data[i];
	}
}

template<typename T>
int ArrayList<T>::size() const
{
	return m_size;
}
template<typename T>
const T& ArrayList<T>::first() const
{
	if(m_size>0)
		return m_data[0];
	else
		cout<<"!-- ERROR : PANIC in ARRAYLIST.first()!!  (List is empty)"<<endl;
	return m_errobj;
}

template<typename T>
T& ArrayList<T>::operator[](int i)
{
	if(i<m_size&&i>=0) 
		return m_data[i];
	else
		cout<<"!-- ERROR : PANIC in ARRAYLIST!!.[]  (index out of bounds)"<<endl;
	return m_errobj;
}

template<typename T>
const T& ArrayList<T>::operator[](int i)const
{
	if(i<m_size&&i>=0) 
		return m_data[i];
	else 
		cout<<"!-- ERROR : PANIC in ARRAYLIST!!.[]()  (index out of bounds)"<<endl;
	return m_errobj;
}
template<typename T>
int ArrayList<T>::find(const T& x)
{
	int i =0;
	int index =-1;
	do
	{
		if(m_data[i] == x)
			index=i;
		i++;
	}while(i<m_size && index ==-1);
	return index;
}

template<typename T>
void ArrayList<T>::clear()
{
	m_size = 0;
	m_max = 0;
	delete [] m_data;
	m_data = NULL;
	return;
}

template<typename T>
void ArrayList<T>::insert_back(const T& x)
{
	if(m_size>=m_max)
	{//grow function
		while(m_size>=m_max)
		{
			m_max= m_max*2+1;
		}
		T* temp;
		temp = new T[m_max];
		for(int i =0; i<m_size; i++)
			temp[i] = m_data[i];
		delete [] m_data;
		m_data = new T[m_max];
		for(int i =0; i<m_size; i++)
			m_data[i] = temp[i];
	}
	//now add x to list
	m_data[m_size] = x;
	m_size++;
	return;
}

template<typename T>
void ArrayList<T>::insert(const T& x, int i)
{
	if((i>=0)&&(i<m_size))
	{
		if(m_size>=m_max-1)
		{//grow function
			while(m_size>=m_max-1)
				m_max=m_max+1;
			T* temp;
			temp = new T[m_max];
			for(int j =0; j<m_size; j++)
				temp[j] = m_data[j];
			delete [] m_data;
			m_data = new T[m_max];
			for(int j =0; j<m_size; j++)
			{
				m_data[j] = temp[j];
			}
		}
		//now add x to list
		for(int k=m_size; k>i; k--)
		{
			m_data[k]=m_data[k-1];
		}
		m_data[i]=x;
		m_size++;
	}
	else
		cout<<"!-- ERROR : PANIC in ARRAYLIST!!.insert()  (index out of bounds)"<<endl;
	return;
}

template<typename T>
void ArrayList<T>::remove(int i)
{
	if(i>=0&& i<m_size)
	{
		for(int k=i; k<m_size-1; k++)
			m_data[k] = m_data[k+1];
		m_size--;
		if(m_size<static_cast<int>(m_max/4))
		{
			T* temp;
			temp = new T[m_max/4];
			m_max=m_max/4;
			for(int i =0; i<m_size; i++)
				temp[i] = m_data[i];
			delete [] m_data;
			m_data = new T[m_max];
			for(int i =0; i<m_size; i++)
				m_data[i] = temp[i];
		}
	}
	else
		cout<<"!-- ERROR : PANIC in ARRAYLIST!!.remove()  (index out of bounds)"<<endl;
	return;
}
template<typename T>
void ArrayList<T>::swap(int i, int k)
{
	if((i>=0&& i<m_size) && (k>=0&& k<m_size))
	{	
		T temp = m_data[i];
		m_data[i]=m_data[k];
		m_data[k]=temp;
	}
	else
		cout<<"!-- ERROR : PANIC in ARRAYLIST!!.swap()  (index out of bounds)"<<endl;
	return;
}

template<typename T>
void ArrayList<T>::append(const ArrayList<T>& alist)
{
	while(m_max<m_size+alist.m_size)
	{//grow function
		T* temp;
		temp = new T[m_max*2+1];
		m_max=m_max*2+1;
		for(int i =0; i<m_size; i++)
			temp[i] = m_data[i];
		delete [] m_data;
		m_data = new T[m_max];
		for(int i =0; i<m_size; i++)
			m_data[i] = temp[i];
	}
	int index2 =0;
	for(int i =m_size;i<m_size+alist.m_size;i++)
	{
		m_data[i] = alist.m_data[index2];
		index2++;
	}
	m_size = m_size+alist.m_size;
	return;
}

template<typename T>
void ArrayList<T>::purge()
{
	for(int i =0; i<m_size; i++)
		for(int k=1+i; k<m_size; k++)
			if(m_data[i]==m_data[k])
				remove(k);
	return;
}
				
