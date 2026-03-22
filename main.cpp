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
  v.pushBack(2);
  v.pushBack(3);

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

int main()
{
  using f_p = std::pair<const char *, bool (*)()>;
  f_p tests[] = {{"empty vector test", testEmptyVector}, {"push back vector check", testPushBack}};

  const size_t count = sizeof(tests) / sizeof(f_p);
  std::cout << std::boolalpha;
  size_t success = 0;
  for (size_t i = 0; i < count; ++i)
  {
    std::cout << tests[i].first << ": " << (success += tests[i].second()) << "\n";
  }
  std::cout << "\ntests passed: " << success << " / " << count << "\n";
}
