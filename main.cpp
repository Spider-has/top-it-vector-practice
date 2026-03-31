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
