#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>

namespace topit
{
  template <class T> struct Vector
  {
  public:
    ~Vector();
    Vector() noexcept;

  private:
    T *data_;
    size_t size_, cap_;
  };

  template <class T> Vector<T>::~Vector()
  {
    delete[] data_;
  }

  template <class T> Vector<T>::Vector() noexcept : data_(nullptr), size_(0), cap_(0)
  {
  }
}

#endif
