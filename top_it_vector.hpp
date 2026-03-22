#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>
#include <iostream>

namespace topit
{
  template <class T> struct Vector
  {
  public:
    ~Vector();
    Vector() noexcept;

    Vector(const Vector &vec);
    Vector(Vector &&vec) noexcept;

    Vector &operator=(const Vector &vec);
    Vector &operator=(Vector &&vec) noexcept;

    T &operator[](size_t index);

    // Сделать
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    // Сделать pushBack
    void pushBack(const T &val);

    // Сделать popBack
    void popBack();

    // Сделать insert
    void insert(size_t i, const T &val);

    // Сделать erase
    void erase(size_t i);

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

  template <class T> bool Vector<T>::isEmpty() const noexcept
  {
    return size_ == 0;
  }

  template <class T> size_t Vector<T>::getSize() const noexcept
  {
    return -1;
  }

  template <class T> size_t Vector<T>::getCapacity() const noexcept
  {
    return -1;
  }

  template <class T> void Vector<T>::pushBack(const T &val)
  {
    std::cout << val << "\n";
  }

  template <class T> void Vector<T>::popBack()
  {
  }

  template <class T> void Vector<T>::insert(size_t i, const T &val)
  {
    std::cout << i << " " << val << "\n";
  }

  template <class T> T &Vector<T>::operator[](size_t index)
  {
    std::cout << index << "\n";
    return *(new T());
  }
}

#endif
