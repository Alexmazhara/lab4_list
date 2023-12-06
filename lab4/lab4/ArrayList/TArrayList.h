#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

#include <iostream>
#include <fstream>
using namespace std;

template <class T1>
class TArrayListIterator;

template <class T>
class TArrayList
{
protected:
  T* data;
  int* links;
  int size;
  int count;
  int root;
public:
  TArrayList(int _size = 1);
  TArrayList(TArrayList<T>& _v);
  ~TArrayList();
  
  TArrayList<T>& operator =(TArrayList<T>& _v);

  void InsFirst(T d); //вставка элемента в начало, конец или после указанного элемента
  void InsLast(T d); 
  void Ins(TArrayListIterator<T>& e, T d); 
  bool IsFull(void) const; //проверка на полноту или пустоту
  bool IsEmpty(void) const; 

  TArrayListIterator<T> begin() ;
  TArrayListIterator<T> end();

  void DelFirst();//удаление элемента с начала или конца
  void DelLast();

  T GetFirst();//получение первого или последнего элемента
  T GetLast();

  void Del(TArrayListIterator<T>& e);//удаление элемента, указанного итератором
  int GetCount();//получение текущего количества элементов


  
  void file();//запись данных в файл
  TArrayList<T> Divide(int _k);//создание нового списка, включающего элементы, которые делятся на заданное число

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TArrayList<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TArrayList<T1> &A);

  template <class T1>
  friend class TArrayListIterator;
};

template <class T>
class TArrayListIterator
{
protected:
  TArrayList<T>& list;
  int index;
public:
  TArrayListIterator(TArrayList<T>& _list, int _index = -2);
  TArrayListIterator(TArrayListIterator<T>& _v);
  ~TArrayListIterator();

  bool IsGoNext();//проверка на возможность перехода к следующему элементу
  void GoNext();//переход к следующему элементу
 
  bool operator == (const TArrayListIterator<T>& _v);
  bool operator != (const TArrayListIterator<T>& _v);
  TArrayListIterator<T>& operator ++ ();
  TArrayListIterator<T>& operator =(const TArrayListIterator<T>& _v);

  T& operator *();//разыменование итератора для получения данных
  T& operator *(int);

  T GetData();//получение данных текущего элемента
  T GetIndex();//получение индекса текущего элемента
};


template <class T1>
ostream& operator<< (ostream& ostr, const TArrayList<T1> &A) 
{
  int i = A.root;
  while (A.links[i] != -1)
  {
    ostr << A.data[i] << " ";
    i = A.links[i];
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TArrayList<T1> &A) 
{
  int count;
  istr >> count;
  for (int i = 0; i < count; i++)
  {
    T1 d;
    istr >> d;
    A.InsLast(d);
  }
  return istr;
}

template<class T>
inline TArrayList<T>::TArrayList(int _size)
{
  if (_size <= 0)
  {
    throw "Error";
  }
  size = _size;

  data = new T[size];
  links = new int[size];
  count = 0;

  for (int i = 0; i < size; i++)
  {
    links[i] = -2;
  }

  root = -1;
}

template <class T>
TArrayList<T>::TArrayList(TArrayList<T>& _v)
{
  count = _v.count;
  size = _v.size;
  root = _v.root;

  data = new T[size];
  links = new int[size];
 
  for (int i = 0; i < size; i++)
  {
    links[i] = _v.links[i];
    data[i] = _v.data[i];
  }
}

template <class T>
TArrayList<T>::~TArrayList()
{
  if (data != 0)
  {
    delete[] data;
    delete[] links;
    data = 0;
    links = 0;
    count = 0;
    size = 0;
    root = -1;
  }
}

template <class T>
TArrayList<T>& TArrayList<T>::operator =(TArrayList<T>& _v)
{
  if (this == &_v)
    return *this;

  if (size != _v.size)
  {
    delete[] data;
    delete[] links;

    data = new T[_v.size];
    links = new int[_v.size];
  }

  count = _v.count;
  size = _v.size;
  root = _v.root;

  for (int i = 0; i < size; i++)
  {
    links[i] = _v.links[i];
    data[i] = _v.data[i];
  }

  return *this;
}

template<class T>
inline void TArrayList<T>::InsFirst(T d)
{
  if (this->IsFull())
  {
    throw "Error";
  }

  int i = 0;
  for (i = 0; i < size; i++)
  {
    if (links[i] == -2)
    {
      break;
    }
  }
  data[i] = d;
  links[i] = root;
  root = i;
  count++;
}

template<class T>
inline void TArrayList<T>::InsLast(T d)
{
  if (this->IsFull())
  {
    throw "Error";
  }
  if (this->IsEmpty())
  {
    root = 0;
    data[0] = d;
    links[0] = -1;
  }
  else
  {
    int i = 0;
    for (i = 0; i < size; i++)
    {
      if (links[i] == -2)
      {
        break;
      }
    }

    int end = root;
    while (links[end] != -1)
    {
      end = links[end];
    }
    data[i] = d;
    links[i] = -1;
    links[end] = i;
  }
  count++;
}

template<class T>
inline void TArrayList<T>::Ins(TArrayListIterator<T>& e, T d)
{
  if (this->IsFull())
  {
    throw "Error";
  }
  if (this->IsEmpty())
  {
    root = 0;
    data[0] = d;
    links[0] = -1;
  }
  else
  {
    int temp = e.GetIndex();
    if (links[temp] == -2)
    {
      int end = root;
      while (links[end] != -1)
      {
        end = links[end];
      }
      data[temp] = d;
      links[temp] = -1;
      links[end] = temp;
    }
  }
  count++;
}

template<class T>
inline bool TArrayList<T>::IsFull(void) const
{
  return count >= size;
}

template<class T>
inline bool TArrayList<T>::IsEmpty(void) const
{
  return count == 0;
}

template<class T>
inline void TArrayList<T>::DelFirst()
{
  if (this->IsEmpty())
  {
    throw "Error";
  }
  int i = root;
  root = links[root];
  links[i] = -2;
  count--;
}

template<class T>
inline void TArrayList<T>::DelLast()
{
  if (this->IsEmpty())
  {
    throw "Error";
  }

  if (links[root] == -1)
  {
    links[root] = -2;
    root = -1;
  }
  else
  {
    int pEnd = root;
    int end = links[root];

    while (links[end] != -1)
    {
      pEnd = end;
      end = links[end];
    }

    links[pEnd] = -1;
    links[end] = -2;
  } 
  count--;
}

template<class T>
inline T TArrayList<T>::GetFirst()
{
  if (this->IsEmpty())
  {
    throw "error";
  }
  return data[root];
}

template<class T>
inline T TArrayList<T>::GetLast()
{
  if (this->IsEmpty())
  {
    throw "error";
  }

  int end = root;
  while (links[end] != -1)
  {
    end = links[end];
  }
  return data[end];
}

template<class T>
inline void TArrayList<T>::Del(TArrayListIterator<T>& e)
{
  if (this->IsEmpty())
  {
    throw "Error";
  }

  if (links[root] == -1)
  {
    links[root] = -2;
    root = -1;
  }
  else
  {
    int pEnd = e.GetIndex();
    int end = links[root];

    while (links[end] != -1)
    {
      pEnd = end;
      end = links[end];
    }

    links[pEnd] = -1;
    links[end] = -2;
  }
  count--;
}

template<class T>
inline int TArrayList<T>::GetCount()
{
  return count;
}
template<class T>
inline void TArrayList<T>::file()
{
  ofstream outf("Data.txt");
  if (!outf)
  {
    throw "Error file";
  }

  for (int i = 0; i < this->size; i++)
  {
    outf << this->data[i] << " ";
  }
}

template <class T>
TArrayList<T> TArrayList<T>::Divide(int _k)
{
  int size_temp = this->size;
  TArrayList<T> temp(size_temp);

  for (int i = 0; i < this->size; i++)
  {
    if (this->data[i] % _k == 0)
    {
      temp.InsFirst(this->data[i]);
    }
  }
  return temp;
}


#endif

template<class T>
inline TArrayListIterator<T> TArrayList<T>::begin()
{
  return TArrayListIterator<T>(*this, this->root);
}

template<class T>
inline TArrayListIterator<T> TArrayList<T>::end()
{
  return TArrayListIterator<T>(*this, -1);
}


template<class T>
inline TArrayListIterator<T>::TArrayListIterator(TArrayList<T>& _list, int _index): list(_list)
{
  this->index = _index;
}

template<class T>
inline TArrayListIterator<T>::TArrayListIterator(TArrayListIterator<T>& _v): list(_v.list), index(_v.index)
{
}

template<class T>
inline TArrayListIterator<T>::~TArrayListIterator()
{
  index = -2;
}

template<class T>
inline bool TArrayListIterator<T>::IsGoNext()
{
  return (index >= 0);
}

template<class T>
inline void TArrayListIterator<T>::GoNext()
{
  if (IsGoNext())
  {
    index = list.links[index];
  }
}

template<class T>
inline bool TArrayListIterator<T>::operator==(const TArrayListIterator<T>& _v)
{
  return index == _v.index;
}

template<class T>
inline bool TArrayListIterator<T>::operator!=(const TArrayListIterator<T>& _v)
{
  return !this->operator==(_v);
}

template<class T>
inline TArrayListIterator<T>& TArrayListIterator<T>::operator++()
{
  GoNext();
  return *this;
}

template<class T>
inline TArrayListIterator<T>& TArrayListIterator<T>::operator=(const TArrayListIterator<T>& _v)
{
  list = _v.list;
  index = _v.index;
}

template<class T>
inline T& TArrayListIterator<T>::operator*()
{
  return list.data[index];
}

template<class T>
inline T& TArrayListIterator<T>::operator*(int)
{
  return list.data[index];
}

template<class T>
inline T TArrayListIterator<T>::GetData()
{
  if (index < 0)
  {
    throw "Error";
  }
  return list.data[index];
}

template<class T>
inline T TArrayListIterator<T>::GetIndex()
{
  if (index < 0)
  {
    throw "Error";
  }
  return index;
}