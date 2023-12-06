#include "TArrayList.h"
#include <gtest.h>

TEST(TArrayList, can_create_Arraylist) //Создание листа
{
  ASSERT_NO_THROW(TArrayList<int> temp(10));
}

TEST(TArrayList, can_create_Arraylist_Iterator) //Создание итератора
{
  TArrayList<int> temp(10);
  ASSERT_NO_THROW(TArrayListIterator<int> i(temp));
}

TEST(TArrayList, can_copy_Arraylist) //Копирования листа
{
  TArrayList<int> temp(10);
  ASSERT_NO_THROW(TArrayList<int> temp2(temp));
}

TEST(TArrayList, can_copy_Arraylist_Iterator) //Копирование итератора
{
  TArrayList<int> temp(10);
  TArrayListIterator<int> i(temp);
  ASSERT_NO_THROW(TArrayListIterator<int> j = i);
}

TEST(TArrayList, can_insert_elem_first) //Вставка элемента в начало
{
  TArrayList<int> temp(10);
  ASSERT_NO_THROW(temp.InsFirst(1));
}

TEST(TArrayList, cant_insert_elem_isFull) //Исключение при вставке при отсутствии места
{
  TArrayList<int> temp(1);
  temp.InsFirst(1);
  ASSERT_ANY_THROW(temp.InsFirst(2));
}

TEST(TArrayList, can_insert_elem_last) //Вставка элемента в конец
{
  TArrayList<int> temp(10);
  ASSERT_NO_THROW(temp.InsLast(1));
}

TEST(TArrayList, can_insert_through_iterator)
{
  TArrayList<char> temp(10);
  temp.InsFirst('a');
  temp.InsLast('b');
  temp.InsFirst('c');
  TArrayListIterator<char> i(temp, 1);
  ASSERT_NO_THROW(temp.Ins(i, 'd'));
}

TEST(TArrayList, check_isFull)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

  EXPECT_EQ(temp.IsFull(), true);
}

TEST(TArrayList, check_isEmpty)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

  EXPECT_EQ(temp.IsEmpty(), false);
}


TEST(TArrayList, can_del_first)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

	ASSERT_NO_THROW(temp.DelFirst());
}

TEST(TArrayList, can_del_last)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

  ASSERT_NO_THROW(temp.DelLast());
}

TEST(TArrayList, can_Get_first)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

  EXPECT_EQ(temp.GetFirst(), 'a');
}

TEST(TArrayList, can_Get_last)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

  EXPECT_EQ(temp.GetLast(), 'a');
}

TEST(TArrayList, can_del_iterator)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');
  TArrayListIterator<char> i(temp, 1);

  ASSERT_NO_THROW(temp.Del(i));
}


TEST(TArrayList, can_get_count)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');

  EXPECT_EQ(temp.GetCount(), 1);
}

TEST(TArrayList, can_GetData_iterator)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');
  TArrayListIterator<char> i(temp, 1);
  ASSERT_NO_THROW(i.GetData());
}

TEST(TArrayList, can_GetIndex_iterator)
{
  TArrayList<char> temp(1);
  temp.InsFirst('a');
  TArrayListIterator<char> i(temp, 1);
  ASSERT_NO_THROW(i.GetIndex());
}

TEST(TArrayList, DOP_test_file_write_DOP)
{
  TArrayList<char> temp(3);
  temp.InsFirst('a');
  temp.InsFirst('b');
  temp.InsFirst('c');
  ASSERT_NO_THROW(temp.file());
}

TEST(TArrayList, DOP_test_divide_without_residue_DOP)
{
  TArrayList<int> temp(2);
  temp.InsFirst(10);
  temp.InsFirst(25);
  ASSERT_NO_THROW(temp.Divide(2));
}