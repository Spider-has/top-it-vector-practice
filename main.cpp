#include <cassert>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Test.hpp"
#include "prettyOutput.hpp"
#include "top_it_vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  assert(v.getSize() == 1 && "size != 1");
  v.pushBack(2);
  assert(v.getSize() == 2 && "size != 2");
  v.pushBack(3);
  assert(v.getCapacity() == 4 && "capacity != 4");

  assert(v[0] == 1 && "v[0] != 1");
  assert(v[1] == 2 && "v[1] != 2");
  assert(v[2] == 3 && "v[2] != 3");

  return v.getSize() == 3 && !v.isEmpty() && v.getCapacity() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(20);
  v.pushBack(10);
  v.pushBack(30);

  assert(v[0] == 20 && "v[0] != 20");
  assert(v[1] == 10 && "v[1] != 10");
  assert(v[2] == 30 && "v[2] != 30");

  v.popBack();
  v.popBack();
  v.popBack();

  return v.getSize() == 0 && v.isEmpty() && v.getCapacity() > 0;
}

bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    int &val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutofboundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range &e)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > &c_v = v;
  try
  {
    const int &val = c_v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutofboundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range &e)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testCapacityChanging()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);

  assert(v[0] == 1 && "v[0] != 1");
  assert(v[1] == 2 && "v[1] != 2");
  assert(v[2] == 3 && "v[2] != 3");
  assert(v[3] == 4 && "v[1] != 4");
  assert(v[4] == 5 && "v[2] != 5");

  return v.getSize() == 5 && !v.isEmpty() && v.getCapacity() == 8;
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  topit::Vector< int > yav{v};
  return v == yav;
}

bool testCopyConstructorNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav{v};
  try
  {
    return yav.getSize() == v.getSize() && yav.at(0) == v.at(0);
  }
  catch (...)
  {
    return false;
  }
  return v == yav;
}

bool testNotEqualVectorsDiffSize()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2{v1};
  v2.popBack();
  return v1 != v2;
}

bool testNotEqualVectorsDiffElemetnts()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2{v1};
  v2[2] = 5;
  return v1 != v2;
}

bool testEqualVectorsWithCopyConstuctor()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2{v1};
  return v1 == v2;
}

bool testEqualVectors()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  topit::Vector< int > v2;
  v2.pushBack(1);
  v2.pushBack(2);
  v2.pushBack(3);
  return v1 == v2;
}

bool testOperatorAssign()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);

  topit::Vector< int > v2;
  v2.pushBack(1);
  v2 = v1;
  return v2 == v1;
}

bool testMoveConstructor()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);

  topit::Vector< int > v2{std::move(v1)};

  try
  {
    v1.at(0);
    return false;
  }
  catch (...)
  {
  }

  return v1.getSize() == 0 && v1.isEmpty() && v2.getSize() == 3;
}

bool testMoveAssign()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);

  topit::Vector< int > v2;

  v2 = std::move(v1);

  try
  {
    v1.at(0);
    return false;
  }
  catch (...)
  {
  }

  return v1.getSize() == 0 && v1.isEmpty() && v2.getSize() == 3;
}

bool testInsert()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.insert(0, 2);
  v.insert(2, 3);
  return v.getSize() == 3 && v[0] == 2 && v[1] == 1 && v[2] == 3;
}

bool testInsertOutOfRange()
{
  topit::Vector< int > v;
  try
  {
    v.insert(12, 1);
    return false;
  }
  catch (...)
  {
  }
  return v.isEmpty();
}

bool testInsertToBegin()
{
  topit::Vector< int > v;
  try
  {
    v.insert(0, 10);
    return v.at(0) == 10 && v.getSize() == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testInsertIntoCenter()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(5);
  v.pushBack(6);
  v.pushBack(8);

  try
  {
    v.insert(3, 4);
    v.insert(6, 7);
    bool correct = true;
    for (size_t i = 0; i < v.getSize() && correct; ++i)
    {
      correct = v[i] == int(i + 1);
    }
    return correct && v.getSize() == 8;
  }
  catch (...)
  {
    return false;
  }
}

bool testErase()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(10);
  v.pushBack(3);

  try
  {
    v.erase(2);
    bool correct = true;
    for (size_t i = 0; i < v.getSize() && correct; ++i)
    {
      correct = v[i] == int(i + 1);
    }
    return correct && v.getSize() == 3;
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseEmpty()
{
  topit::Vector< int > v;

  try
  {
    v.erase(1);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testEraseBegin()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  try
  {
    v.erase(0);
    return v.getSize() == 1 && v[0] == 2;
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseEnd()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  try
  {
    v.erase(1);
    return v.getSize() == 1 && v[0] == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testInsertRange()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  topit::Vector< int > v2;
  v2.pushBack(1);
  v2.pushBack(4);
  try
  {
    v2.insert(1, v1, 1, 3);
    bool correct = true;
    for (size_t i = 0; i < v2.getSize() && correct; ++i)
    {
      correct = v2[i] == int(i + 1);
    }
    return correct && v2.getSize() == 4;
  }
  catch (...)
  {
    return false;
  }
}

bool testInsertRangeToBegin()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  topit::Vector< int > v2;
  try
  {
    v2.insert(0, v1, 0, 3);
    bool correct = true;
    for (size_t i = 0; i < v2.getSize() && correct; ++i)
    {
      correct = v2[i] == int(i + 1);
    }
    return correct && v2.getSize() == 3;
  }
  catch (...)
  {
    return false;
  }
}

bool testInsertRangeToEnd()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  topit::Vector< int > v2;
  v2.pushBack(1);
  try
  {
    v2.insert(1, v1, 1, 3);
    bool correct = true;
    for (size_t i = 0; i < v2.getSize() && correct; ++i)
    {
      correct = v2[i] == int(i + 1);
    }
    return correct && v2.getSize() == 3;
  }
  catch (...)
  {
    return false;
  }
}

bool testInsertRangeOutOfRange()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  topit::Vector< int > v2;
  try
  {
    v2.insert(10, v1, 0, 1);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testInsertRhsRangeOutOfRange()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  topit::Vector< int > v2;
  try
  {
    v2.insert(0, v2, 11, 15);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testInsertRangeLhsBiggerThanRhs()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  topit::Vector< int > v2;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  try
  {
    v2.insert(0, v2, 3, 2);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testInsertRangeIntoItself()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  try
  {
    v1.insert(1, v1, 2, 4);
    bool correct = true;
    correct = correct && v1[0] == 1;
    correct = correct && v1[1] == 3;
    correct = correct && v1[2] == 4;
    correct = correct && v1[3] == 2;
    correct = correct && v1[4] == 3;
    correct = correct && v1[5] == 4;
    return correct && v1.getSize() == 6;
  }
  catch (...)
  {
    return true;
  }
}

bool testInsertRangeIntoItselfInTheSamePlace()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  try
  {
    v1.insert(3, v1, 2, 4);
    bool correct = true;
    correct = correct && v1[0] == 1;
    correct = correct && v1[1] == 2;
    correct = correct && v1[2] == 3;
    correct = correct && v1[3] == 3;
    correct = correct && v1[4] == 4;
    correct = correct && v1[5] == 4;
    return correct && v1.getSize() == 6;
  }
  catch (...)
  {
    return true;
  }
}

bool testEraseRange()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(10);
  v1.pushBack(11);
  v1.pushBack(2);
  try
  {
    v1.erase(1, 3);
    bool correct = true;
    for (size_t i = 0; i < v1.getSize() && correct; ++i)
    {
      correct = v1[i] == int(i + 1);
    }
    return correct && v1.getSize() == 2;
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseRangeFromBegin()
{
  topit::Vector< int > v1;
  v1.pushBack(5);
  v1.pushBack(6);
  v1.pushBack(1);
  v1.pushBack(2);
  try
  {
    v1.erase(0, 2);
    bool correct = true;
    for (size_t i = 0; i < v1.getSize() && correct; ++i)
    {
      correct = v1[i] == int(i + 1);
    }
    return correct && v1.getSize() == 2;
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseRangeToEnd()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  try
  {
    v1.erase(2, 4);
    bool correct = true;
    for (size_t i = 0; i < v1.getSize() && correct; ++i)
    {
      correct = v1[i] == int(i + 1);
    }
    return correct && v1.getSize() == 2;
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseOutOfRange()
{
  topit::Vector< int > v1;
  try
  {
    v1.erase(1, 3);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testEraseRangeLhsMoreThanRhs()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(1);
  v1.pushBack(1);
  v1.pushBack(1);
  try
  {
    v1.erase(3, 1);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testInitializerList()
{
  topit::Vector< int > v({1, 2, 3});
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testIteratorDistance()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; ++i)
  {
    v.pushBack(i);
  }

  auto itBegin = v.begin();
  auto itEnd = v.end();

  if ((itEnd - itBegin) != 5)
  {
    return false;
  }

  if ((itBegin - itEnd) != -5)
  {
    return false;
  }

  return true;
}

bool testIteratorSubscript()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);

  auto it = v.begin();

  if (it[0] != 10 || it[2] != 30)
  {
    return false;
  }

  if (*it != 10)
  {
    return false;
  }

  return true;
}

bool testIteratorComparisons()
{
  topit::Vector< int > v;
  for (int i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }

  auto it1 = v.begin() + 2;
  auto it2 = v.begin() + 5;
  auto it3 = v.begin() + 5;

  if (!(it1 < it2))
  {
    return false;
  }
  if (!(it2 > it1))
  {
    return false;
  }
  if (!(it2 <= it3) || !(it2 >= it3))
  {
    return false;
  }
  if (it1 == it2)
  {
    return false;
  }

  it1 += 3;
  return it1 == it2;
}

bool testRangeBasedFor()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);

  int sum = 0;
  int count = 0;

  for (auto x : v)
  {
    sum += x;
    count++;
  }

  if (sum != 60)
  {
    return false;
  }
  if (count != 3)
  {
    return false;
  }

  return true;
}

bool testIteratorMutation()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  for (auto &x : v)
  {
    x *= 10;
  }

  return v[0] == 10 && v[1] == 20;
}

bool testIteratorEmptyVector()
{
  topit::Vector< int > v;
  auto it = v.begin();

  try
  {
    *it = 10;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testIteratorOverflow()
{
  topit::Vector< int > v;
  auto it = v.begin();

  try
  {
    it[10] = 10;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testInsertMultipleCountInMiddle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(5);

  auto it = v.begin() + 2;
  v.insert(it, 2, 100);

  if (v.getSize() != 5)
  {
    return false;
  }
  if (v[2] != 100 || v[3] != 100 || v[4] != 5)
  {
    return false;
  }

  return true;
}

bool testInsertAtBegin()
{
  topit::Vector< int > v;
  v.pushBack(10);

  v.insert(v.begin(), 3, 7);

  if (v.getSize() != 4)
  {
    return false;
  }
  if (v[0] != 7 || v[3] != 10)
  {
    return false;
  }

  return true;
}

bool testInsertAtEnd()
{
  topit::Vector< int > v;
  v.pushBack(1);

  v.insert(v.end(), 2, 9);

  if (v.getSize() != 3)
  {
    return false;
  }
  if (v[1] != 9 || v[2] != 9)
  {
    return false;
  }

  return true;
}

bool testInsertZeroCount()
{
  topit::Vector< int > v;
  v.pushBack(42);

  size_t oldSize = v.getSize();
  v.insert(v.begin(), 0, 100);

  return (v.getSize() == oldSize && v[0] == 42);
}

bool testInsertForeignIterator()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2;
  v1.pushBack(1);
  v2.pushBack(2);
  try
  {
    v1.insert(v2.begin(), 1, 100);
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testInsertRangeFromOtherVector()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(5);

  topit::Vector< int > v2;
  v2.pushBack(100);
  v2.pushBack(200);

  v1.insert(v1.begin() + 2, v2.begin(), v2.end());

  if (v1.getSize() != 5)
  {
    return false;
  }
  if (v1[2] != 100 || v1[3] != 200 || v1[4] != 5)
  {
    return false;
  }

  return true;
}

bool testInsertSelfRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  v.insert(v.end(), v.begin(), v.begin() + 2);

  if (v.getSize() != 5)
  {
    return false;
  }
  if (v[3] != 1 || v[4] != 2 || v[2] != 3)
  {
    return false;
  }

  return true;
}

bool testInsertEmptyRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  topit::Vector< int > vEmpty;
  size_t oldSize = v.getSize();
  size_t oldCap = v.getCapacity();

  v.insert(v.begin() + 1, vEmpty.begin(), vEmpty.end());

  return (v.getSize() == oldSize && v[0] == 1 && v[1] == 2);
}

bool testInsertSelfRangeOverlap()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);

  v.insert(v.begin() + 1, v.begin(), v.begin() + 2);

  if (v.getSize() != 5)
  {
    return false;
  }
  if (v[0] != 10 || v[1] != 10 || v[2] != 20 || v[3] != 20 || v[4] != 30)
  {
    return false;
  }

  return true;
}

bool testInsertRangeExactlyToCapacity()
{
  topit::Vector< int > v;
  v.reserve(10);
  for (int i = 0; i < 5; ++i)
  {
    v.pushBack(i);
  }

  topit::Vector< int > additional;
  for (int i = 0; i < 5; ++i)
  {
    additional.pushBack(100);
  }

  v.insert(v.end(), additional.begin(), additional.end());

  return (v.getSize() == 10 && v[9] == 100);
}

struct ThrowingType
{
  static int count;
  int val;
  ThrowingType():
      val(0)
  {
    count = 0;
  }
  ThrowingType(int v):
      val(v)
  {
  }
  ThrowingType &operator=(const ThrowingType &other)
  {
    if (++count > 5)
    {
      throw std::runtime_error("Copy limit exceeded");
    }
    val = other.val;
    return *this;
  }
};

int ThrowingType::count = 0;

bool testInsertRangeExceptionSafety()
{
  topit::Vector< ThrowingType > v;
  v.pushBack(ThrowingType(1));
  v.pushBack(ThrowingType(2));

  topit::Vector< ThrowingType > src;
  for (int i = 0; i < 5; ++i)
  {
    src.pushBack(ThrowingType(100));
  }

  ThrowingType::count = 0;
  try
  {
    v.insert(v.begin() + 1, src.begin(), src.end());
    return false;
  }
  catch (...)
  {
    return (v.getSize() == 2 && v[0].val == 1 && v[1].val == 2);
  }
}

bool testInsertInitializerListBasic()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(10);

  v.insert(v.begin() + 1, {2, 3, 4});

  if (v.getSize() != 5)
  {
    return false;
  }
  if (v[1] != 2 || v[2] != 3 || v[3] != 4 || v[4] != 10)
  {
    return false;
  }

  return true;
}

bool testInsertListIntoEmpty()
{
  topit::Vector< int > v;
  v.insert(v.begin(), {100, 200});

  return (v.getSize() == 2 && v[0] == 100 && v[1] == 200);
}

bool testInsertEmptyList()
{
  topit::Vector< int > v;
  v.pushBack(42);

  v.insert(v.end(), {});

  return (v.getSize() == 1 && v[0] == 42);
}

bool testInsertListGrowth()
{
  topit::Vector< int > v;
  v.insert(v.begin(), {1, 2});
  v.insert(v.end(), {3, 4});
  v.insert(v.begin() + 2, {10, 20, 30});

  return (v.getSize() == 7 && v[2] == 10 && v[5] == 3);
}

bool testEraseRangeMiddle()
{
  topit::Vector< int > v;
  for (int i = 0; i < 6; ++i)
  {
    v.pushBack(i);
  }

  auto it1 = v.begin() + 1;
  auto it2 = v.begin() + 4;
  v.erase(it1, it2);

  if (v.getSize() != 3)
  {
    return false;
  }
  if (v[0] != 0 || v[1] != 4 || v[2] != 5)
  {
    return false;
  }

  return true;
}

bool testEraseToTheEnd()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);

  v.erase(v.begin() + 1, v.end());

  return (v.getSize() == 1 && v[0] == 10);
}

bool testEraseAll()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  v.erase(v.begin(), v.end());

  return (v.getSize() == 0);
}

bool testEraseEmptyRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  auto it = v.begin() + 1;
  v.erase(it, it);

  return (v.getSize() == 2 && v[0] == 1 && v[1] == 2);
}

bool testEraseInvalidRange()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2;
  v1.pushBack(1);
  v2.pushBack(2);

  try
  {
    v1.erase(v1.begin(), v2.end());
    return false;
  }
  catch (...)
  {
    return true;
  }

  try
  {

    v1.erase(v1.begin() + 1, v1.begin());
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testEraseBeginIter()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  auto it = v.begin();
  v.erase(it);

  if (v.getSize() != 2)
  {
    return false;
  }
  if (v[0] != 2 || v[1] != 3)
  {
    return false;
  }

  return true;
}

bool testEraseMiddleIter()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);

  v.erase(v.begin() + 1);

  if (v.getSize() != 2)
  {
    return false;
  }
  if (v[0] != 10 || v[1] != 30)
  {
    return false;
  }

  return true;
}

bool testEraseLastIter()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  v.erase(v.end() - 1);

  if (v.getSize() != 1)
  {
    return false;
  }
  if (v[0] != 1)
  {
    return false;
  }

  return true;
}

bool testEraseEndIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);

  try
  {
    v.erase(v.end());
    return false;
  }
  catch (...)
  {
    return true;
  }
}

bool testEraseAnotherVectorIter()
{
  topit::Vector< int > v;
  topit::Vector< int > v2;

  try
  {
    v.erase(v2.end());
    return false;
  }
  catch (...)
  {
    return true;
  }
}

int main()
{
  using namespace prettyOut;

  Test::Test tests[] = {
      REGISTER_TEST("empty vector test", testEmptyVector),
      REGISTER_TEST("push back vector test", testPushBack),
      REGISTER_TEST("pop back method test", testPopBack),
      REGISTER_TEST("capacity method test", testCapacityChanging),
      REGISTER_TEST("element inbound access test", testElementInboundAccess),
      REGISTER_TEST("element out of bound access test", testElementOutofboundAccess),
      REGISTER_TEST("const element inbound access test", testElementInboundConstAccess),
      REGISTER_TEST("const element out of bound access test", testElementOutofboundConstAccess),
      REGISTER_TEST("copy constructor test", testCopyConstructor),
      REGISTER_TEST("copy construtcot not empty test", testCopyConstructorNonEmpty),
      REGISTER_TEST("move constructor test", testMoveConstructor),
      REGISTER_TEST("not equal diff size vectors test", testNotEqualVectorsDiffSize),
      REGISTER_TEST("not equal diff elements vectors test", testNotEqualVectorsDiffElemetnts),
      REGISTER_TEST("equal copy constructor vector test", testEqualVectorsWithCopyConstuctor),
      REGISTER_TEST("equal vectors test", testEqualVectors),
      REGISTER_TEST("copy assing operator test", testOperatorAssign),
      REGISTER_TEST("move assign operator test", testMoveAssign),
      REGISTER_TEST("insert in different pos test", testInsert),
      REGISTER_TEST("insert out of range test", testInsertOutOfRange),
      REGISTER_TEST("insert element into begin", testInsertToBegin),
      REGISTER_TEST("insert some elements into center and end", testInsertIntoCenter),
      REGISTER_TEST("erase element in the mid test", testErase),
      REGISTER_TEST("erase empty test", testEraseEmpty),
      REGISTER_TEST("erase  begin test", testEraseBegin),
      REGISTER_TEST("erase end test", testEraseEnd),
      REGISTER_TEST("insert range of elements in the mid test", testInsertRange),
      REGISTER_TEST("insert range of elements to begin test", testInsertRangeToBegin),
      REGISTER_TEST("insert range of elements to end test ", testInsertRangeToEnd),
      REGISTER_TEST("insert range of elements out of range", testInsertRangeOutOfRange),
      REGISTER_TEST("insert range of elements in the same vector", testInsertRangeIntoItself),
      REGISTER_TEST("insert range of elements in the same vector and same place",
                    testInsertRangeIntoItselfInTheSamePlace),
      REGISTER_TEST("insert range of elements rhs out of range", testInsertRhsRangeOutOfRange),
      REGISTER_TEST("insert range of elements lhs bigger than rhs out of range", testInsertRangeLhsBiggerThanRhs),
      REGISTER_TEST("erase range of elements in the mid test", testEraseRange),
      REGISTER_TEST("erase range of elements to begin test", testEraseRangeFromBegin),
      REGISTER_TEST("erase range of elements to end test ", testEraseRangeToEnd),
      REGISTER_TEST("erase range of elements out of range", testEraseOutOfRange),
      REGISTER_TEST("erase range of elements lhs more than rhs", testEraseRangeLhsMoreThanRhs),
      REGISTER_TEST("erase initializer list contrustor", testInitializerList),
      REGISTER_TEST("rnd access iter distance test", testIteratorDistance),
      REGISTER_TEST("rnd access to diff elems test", testIteratorSubscript),
      REGISTER_TEST("rnd access all type of comprasions test", testIteratorComparisons),
      REGISTER_TEST("rnd access iter range for test", testRangeBasedFor),
      REGISTER_TEST("rnd access iter test item mutation in for range", testIteratorMutation),
      REGISTER_TEST("rnd access iter empty vector error", testIteratorEmptyVector),
      REGISTER_TEST("rnd access iter overflow error test", testIteratorOverflow),
      REGISTER_TEST("insert count in the middle with iter test", testInsertMultipleCountInMiddle),
      REGISTER_TEST("insert count in the begin with iter test", testInsertAtBegin),
      REGISTER_TEST("insert count in the end with iter test", testInsertAtEnd),
      REGISTER_TEST("insert count zero count with iter test", testInsertZeroCount),
      REGISTER_TEST("insert count with foreign iterator test", testInsertForeignIterator),
      REGISTER_TEST("insert range for other vector with iters", testInsertRangeFromOtherVector),
      REGISTER_TEST("insert range for it self vector with iters", testInsertSelfRange),
      REGISTER_TEST("insert range for other vector with iters zero range", testInsertEmptyRange),
      REGISTER_TEST("insert range for other vector with iters to capacity", testInsertRangeExactlyToCapacity),
      REGISTER_TEST("insert range for other vector with iters with catching error", testInsertRangeExceptionSafety),
      REGISTER_TEST("insert range for initializer list basic", testInsertInitializerListBasic),
      REGISTER_TEST("insert range for initializer list to empty vector", testInsertListIntoEmpty),
      REGISTER_TEST("insert range for empty initializer list", testInsertEmptyList),
      REGISTER_TEST("insert range for initializer list multiple times", testInsertListGrowth),
      REGISTER_TEST("erase range from middle test iters", testEraseRangeMiddle),
      REGISTER_TEST("erase range from pos to end test iters", testEraseToTheEnd),
      REGISTER_TEST("erase range all elems test iters`", testEraseAll),
      REGISTER_TEST("erase range empty test iters", testEraseEmptyRange),
      REGISTER_TEST("erase range with invalid iterators test", testEraseInvalidRange),
      REGISTER_TEST("erase iter from begin test", testEraseBeginIter),
      REGISTER_TEST("erase iter from middle test", testEraseMiddleIter),
      REGISTER_TEST("erase iter from end test", testEraseLastIter),
      REGISTER_TEST("erase iter after last test", testEraseEndIterator),
      REGISTER_TEST("erase iter from another vector test", testEraseAnotherVectorIter),
  };

  const size_t count = sizeof(tests) / sizeof(Test::Test);
  std::cout << std::boolalpha;
  size_t success = 0;
  size_t left_success = 1;
  size_t right_success = 1;

  printRunTests(__FILE__);
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].func_ptr();
    if (!res)
    {
      if (left_success != right_success)
      {
        printSuccessedBeforeTests(left_success, right_success);
      }
      printFailedTestInfo(__FILE__, tests[i], i + 1);
      left_success = i + 2;
      right_success = i + 2;
    }
    else
    {
      right_success = i + 1;
    }
    success += res;
  }
  if (left_success != right_success)
  {
    printSuccessedBeforeTests(left_success, right_success);
  }
  std::cout << "\n";
  if (success == count)
  {
    printAllTestsSuccessed(count);
  }
  else
  {
    someTestsFailed(success, count);
  }
}
