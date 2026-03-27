#include <cassert>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "top_it_vector.hpp"

static constexpr char BOLD_TEXT[] = "\033[1m";
static constexpr char GREEN_TEXT[] = "\033[32m";
static constexpr char RED_TEXT[] = "\033[31m";
static constexpr char CLEAR_STYLE[] = "\033[0m";

struct Test
{
  const char *desc;
  const char *func_name;
  bool (*func_ptr)();
  int line;
};

#define REGISTER_TEST(desc, func)                                                                                      \
  Test                                                                                                                 \
  {                                                                                                                    \
    desc, #func, func, __LINE__                                                                                        \
  }

bool testEmptyVector()
{
  int line = __LINE__;
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

bool testInsert()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.insert(0, 2);
  v.insert(2, 3);
  return v.getSize() == 3 && v[0] == 2 && v[1] == 1 && v[2] == 3;
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

void printFailedTestInfo(const Test &test, int i)
{
  std::cout << RED_TEXT << i << ". [-] " << test.desc << ": " << BOLD_TEXT << __FILE_NAME__ << ":" << test.line << "-"
            << test.func_name << CLEAR_STYLE << "\n";
}

int main()
{
  Test tests[] = {REGISTER_TEST("empty vector test", testEmptyVector),
                  REGISTER_TEST("push back vector check", testPushBack),
                  REGISTER_TEST("pop back method check", testPopBack),
                  REGISTER_TEST("capacity method check", testCapacityChanging),
                  REGISTER_TEST("element inbound access", testElementInboundAccess),
                  REGISTER_TEST("element out of bound access", testElementOutofboundAccess),
                  REGISTER_TEST("const element inbound access", testElementInboundConstAccess),
                  REGISTER_TEST("const element out of bound access", testElementOutofboundConstAccess),
                  REGISTER_TEST("copy constructor test", testCopyConstructor),
                  REGISTER_TEST("copy construtcot not empty", testCopyConstructorNonEmpty),
                  REGISTER_TEST("not equal diff size vectors", testNotEqualVectorsDiffSize),
                  REGISTER_TEST("not equal diff elements vectors", testNotEqualVectorsDiffElemetnts),
                  REGISTER_TEST("equal copy constructor vector", testEqualVectorsWithCopyConstuctor),
                  REGISTER_TEST("equal vectors", testEqualVectors),
                  REGISTER_TEST("assing operator", testOperatorAssign),
                  REGISTER_TEST("move constructor", testMoveConstructor),
                  REGISTER_TEST("test move assign", testMoveAssign)};

  const size_t count = sizeof(tests) / sizeof(Test);
  std::cout << std::boolalpha;
  size_t success = 0;

  std::cout << "Run tests in file: " << BOLD_TEXT << __FILE_NAME__ << CLEAR_STYLE << "\n\n";
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].func_ptr();
    if (!res)
    {
      printFailedTestInfo(tests[i], i);
    }
    else
    {
      std::cout << GREEN_TEXT << i << ". [+]" << CLEAR_STYLE << "\n";
    }
    success += res;
  }
  // TODO: Подсчет пройденных/непройденных тестов
  // TODO: Вывод только пройденных тестов

  std::cout << "\n";
  if (success == count)
  {
    std::cout << GREEN_TEXT << "All tests passed successfully: " << BOLD_TEXT << success << " / " << count << "\n"
              << CLEAR_STYLE;
  }
  else
  {
    std::cout << "Some test " << RED_TEXT << "failed with errors: " << CLEAR_STYLE << BOLD_TEXT << success << " / "
              << count << "\n"
              << CLEAR_STYLE;
  }
}
