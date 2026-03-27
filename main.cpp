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
    std::cout << v.getSize() << "\n";
    return v.at(0) == 10 && v.getSize() == 1;
  }
  catch (...)
  {
    return false;
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
  };

  const size_t count = sizeof(tests) / sizeof(Test::Test);
  std::cout << std::boolalpha;
  size_t success = 0;
  size_t left_success = 1;
  size_t right_success = 1;

  printRunTests();
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].func_ptr();
    if (!res)
    {
      if (left_success != right_success)
      {
        printSuccessedBeforeTests(left_success, right_success);
      }
      printFailedTestInfo(tests[i], i + 1);
      left_success = i + 2;
      right_success = i + 2;
    }
    else
    {
      right_success++;
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
