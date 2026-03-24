#include <cassert>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "top_it_vector.hpp"

bool testEmptyVector()
{
  topit::Vector<int> v;
  return v.isEmpty();
}

bool testPushBack()
{
  // std::cout << __func__ << "\n";
  topit::Vector<int> v;
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

bool testInsert()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.insert(0, 2);
  v.insert(2, 3);
  return v.getSize() == 3 && v[0] == 2 && v[1] == 1 && v[2] == 3;
}

bool testPopBack()
{
  topit::Vector<int> v;
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
  topit::Vector<int> v;
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
  topit::Vector<int> v;
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
  topit::Vector<int> v;
  v.pushBack(1);
  const topit::Vector<int> &c_v = v;
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
  const topit::Vector<int> v;
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
  topit::Vector<int> v;
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
  topit::Vector<int> v;
  topit::Vector<int> yav{v};
  return v == yav;
}

bool testCopyConstructorNonEmpty()
{
  topit::Vector<int> v;
  v.pushBack(1);
  topit::Vector<int> yav{v};
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
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector<int> v2{v1};
  v2.popBack();
  return v1 != v2;
}

bool testNotEqualVectorsDiffElemetnts()
{
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector<int> v2{v1};
  v2[2] = 5;
  return v1 != v2;
}

bool testEqualVectorsWithCopyConstuctor()
{
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector<int> v2{v1};
  return v1 == v2;
}

bool testEqualVectors()
{
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  topit::Vector<int> v2;
  v2.pushBack(1);
  v2.pushBack(2);
  v2.pushBack(3);
  return v1 == v2;
}

bool testOperatorAssign()
{
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);

  topit::Vector<int> v2;
  v2.pushBack(1);
  v2 = v1;
  return v2 == v1;
}

bool testMoveConstructor()
{
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);

  topit::Vector<int> v2{std::move(v1)};

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
  topit::Vector<int> v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);

  topit::Vector<int> v2;

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

int main()
{
  using f_p = std::pair<const char *, bool (*)()>;
  f_p tests[] = {{"empty vector test", testEmptyVector},
                 {"push back vector check", testPushBack},
                 {"pop back method check", testPopBack},
                 {"capacity method check", testCapacityChanging},
                 {"element inbound access", testElementInboundAccess},
                 {"element out of bound access", testElementOutofboundAccess},
                 {"const element inbound access", testElementInboundConstAccess},
                 {"const element out of bound access", testElementOutofboundConstAccess},
                 {"copy constructor test", testCopyConstructor},
                 {"copy construtcot not empty", testCopyConstructorNonEmpty},
                 {"not equal diff size vectors", testNotEqualVectorsDiffSize},
                 {"not equal diff elements vectors", testNotEqualVectorsDiffElemetnts},
                 {"equal copy constructor vector", testEqualVectorsWithCopyConstuctor},
                 {"equal vectors", testEqualVectors},
                 {"assing operator", testOperatorAssign},
                 {"move constructor", testMoveConstructor}};

  const size_t count = sizeof(tests) / sizeof(f_p);
  std::cout << std::boolalpha;
  size_t success = 0;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    if (!res)
    {
      std::cout << tests[i].first << ": " << res << "\n";
    }
    success += res;
  }
  // TODO: Подсчет пройденных/непройденных тестов
  // TODO: Вывод только пройденных тестов
  std::cout << "\ntests passed: " << success << " / " << count << "\n";
}
