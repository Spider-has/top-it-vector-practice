#include <cassert>
#include <ios>
#include <iostream>

#include "top_it_vector.hpp"

bool testEmptyVector()
{
  topit::Vector<int> v;
  return v.isEmpty();
}

bool testPushBack()
{
  topit::Vector<int> v;
  v.pushBack(1);
  assert(v.getSize() == 1 && "size != 1");
  v.pushBack(2);
  assert(v.getSize() == 2 && "size != 2");
  v.pushBack(3);
  assert(v.getCapacity() == 4 && "capacity != 4");

  return v.getSize() == 3 && !v.isEmpty() && v.getCapacity() == 4;
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
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  v.popBack();
  v.popBack();
  v.popBack();

  return v.getSize() == 0 && v.isEmpty() && v.getCapacity() > 0;
}

bool testCapacityChanging()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);

  return v.getSize() == 5 && !v.isEmpty() && v.getCapacity() == 8;
}

int main()
{
  using f_p = std::pair<const char *, bool (*)()>;
  f_p tests[] = {
      {"empty vector test", testEmptyVector},
      {"push back vector check", testPushBack},
      {"pop back method check", testPopBack},
      {"capacity method check", testCapacityChanging},
  };

  const size_t count = sizeof(tests) / sizeof(f_p);
  std::cout << std::boolalpha;
  size_t success = 0;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    success += res;
  }
  std::cout << "\ntests passed: " << success << " / " << count << "\n";
}
