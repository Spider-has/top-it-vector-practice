#ifndef TEST_HPP
#define TEST_HPP

#define REGISTER_TEST(desc, func)                                                                                      \
  Test::Test                                                                                                           \
  {                                                                                                                    \
    desc, #func, func, __LINE__                                                                                        \
  }

namespace Test
{
  struct Test
  {
    const char *desc;
    const char *func_name;
    bool (*func_ptr)();
    int line;
  };
}

#endif
