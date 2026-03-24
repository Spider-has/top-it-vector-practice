#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace topit
{
  template <class T> struct Vector
  {
  public:
    ~Vector();
    Vector() noexcept;

    Vector(const Vector<T> &rhs);
    Vector(Vector<T> &&vec) noexcept;
    Vector(size_t size, const T &init);

    explicit Vector(size_t size);

    Vector<T> &operator=(const Vector<T> &vec);
    Vector<T> &operator=(Vector<T> &&vec) noexcept;

    T &operator[](size_t index) noexcept;
    const T &operator[](size_t index) const noexcept;

    T &at(size_t id);
    const T &at(size_t id) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T &val);

    void popBack();

    void insert(size_t i, const T &val);

    void erase(size_t i);

    void swap(Vector<T> &rhs) noexcept;

    void changeVectorInSomeWay();

  private:
    static T *createCopy(T *start, T *end, size_t cap);

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

  template <class T> Vector<T>::Vector(const Vector<T> &rhs) : Vector(rhs.size_)
  {
    for (size_t i = 0; i < rhs.getSize(); ++i)
    {
      data_[i] = rhs[i];
    }
  }

  template <class T> Vector<T>::Vector(size_t size, const T &init) : Vector(size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      data_[i] = init;
    }
  }

  template <class T> Vector<T>::Vector(size_t size) : data_(size ? new T[size] : nullptr), size_(size), cap_((size))
  {
  }

  template <class T> bool Vector<T>::isEmpty() const noexcept
  {
    return size_ == 0;
  }

  template <class T> size_t Vector<T>::getSize() const noexcept
  {
    return size_;
  }

  template <class T> size_t Vector<T>::getCapacity() const noexcept
  {
    return cap_;
  }

  template <class T> void Vector<T>::swap(Vector<T> &rhs) noexcept
  {
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(cap_, rhs.cap_);
  }

  template <class T> Vector<T> &Vector<T>::operator=(const Vector<T> &rhs)
  {
    if (this == std::addressof(rhs))
    {
      return *this;
    }
    Vector<T> cpy{rhs};
    swap(cpy);
    return *this;
  }

  // Пример использования copy and swap
  template <class T> void Vector<T>::changeVectorInSomeWay()
  {
    Vector<T> cpy(*this);
    cpy.pushBack(1);
    cpy.pushBack(1);
    cpy.pushBack(1);
    cpy.pushBack(1);
    cpy.pushBack(1);
    cpy.pushBack(1);
    cpy.pushBack(1);
    swap(cpy); //  SWAAAAAP NOOOOEXXCEEPT!!!!!!
  }

  template <class T> T *Vector<T>::createCopy(T *start, T *end, size_t cap)
  {
    T *new_data = new T[cap];
    try
    {
      size_t i = 0;
      for (; start != end; ++start, ++i)
      {
        new_data[i] = *start;
      }
    }
    catch (...)
    {
      delete[] new_data;
      throw;
    }
    return new_data;
  }

  template <class T> void Vector<T>::pushBack(const T &val)
  {
    if (size_ >= cap_)
    {
      size_t new_cap = cap_ ? cap_ * 2 : 1;
      T *new_arr = createCopy(data_, data_ + size_, new_cap);
      new_arr[size_] = val;
      cap_ = new_cap;
      delete[] data_;
      data_ = new_arr;
    }
    else
    {
      data_[size_] = val;
    }
    size_++;
  }

  template <class T> void Vector<T>::popBack()
  {
    if (!size_)
    {
      throw std::runtime_error("can't pop back, vector size is already zero");
    }
    --size_;
  }

  template <class T> void Vector<T>::insert(size_t i, const T &val)
  {
    std::cout << i << " " << val << "\n";
  }

  template <class T> T &Vector<T>::operator[](size_t index) noexcept
  {
    const Vector<T> *cthis = this;
    return const_cast<T &>((*cthis)[index]);
  }

  template <class T> const T &Vector<T>::operator[](size_t index) const noexcept
  {

    return data_[index];
  }

  template <class T> T &Vector<T>::at(size_t id)
  {
    const Vector<T> *cthis = this;
    return const_cast<T &>(cthis->at(id));
  }

  template <class T> const T &Vector<T>::at(size_t id) const
  {
    if (id < getSize())
    {
      return data_[id];
    }
    throw std::out_of_range("can't get element out of range");
  }

  template <class T> bool operator==(const Vector<T> lhs, const Vector<T> &rhs) noexcept
  {
    bool isEqual = lhs.getSize() == rhs.getSize();
    for (size_t i = 0; i < lhs.getSize() && (isEqual = isEqual && lhs[i] == rhs[i]); ++i)
    {
    }
    return isEqual;
  }

  template <class T> bool operator!=(const Vector<T> lhs, const Vector<T> &rhs) noexcept
  {
    return !(lhs == rhs);
  }
}

#endif
