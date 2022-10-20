#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>
#include <algorithm>
#include <new>
#include <functional>

namespace epc {
    template<typename T>
    class vector {
        std::size_t capacity_{0};
        std::size_t size_{0};
        T* data_{nullptr};

    public:
        vector()
        noexcept =
        default;

        vector(const vector& src)
                :capacity_{src.size_}, size_{src.size_}
        {
            if (size_) {
                std::size_t s;

                try {
                    // allocate memory
                    data_ = static_cast<T*>(::operator new(size_*sizeof(T)));

                    // initialize elements
                    for (s = 0; s<src.size(); s++)
                        new(data_+s) T(src.data_[s]);
                }
                catch (...) {
                    // destroy elements
                    for (std::size_t d{0}; d<s; d++)
                        data_[d].T::~T();

                    // deallocate memory
                    ::operator delete(data_);
                    throw;
                }
            }
        }

        vector& operator=(const vector& rhs)
        {
            if (&rhs!=this) {
                // copy-and-swap idiom
                vector temp(rhs);
                swap(temp);
            }
            return *this;
        }

        ~vector()
        {
            if (capacity_) {
                // destroy elements
                for (std::size_t i{0}; i<size_; i++)
                    data_[i].T::~T();

                // deallocate memory
                ::operator delete(data_);
            }
        }

        T* data()
        {
            return data_;
        }

        const T* data() const
        {
            return data_;
        }

        T& operator[](size_t i)
        {
            return data_[i];
        }

        const T& operator[](size_t i) const
        {
            return data_[i];
        }

        void push_back(const T& el)
        {
            if (size_==capacity_)
                reserve((!capacity_) ? 1 : capacity_*2);

            try {
                new(data_+(size_++)) T(el);
            }
            catch (...) {
                size_--;
                throw;
            }
        }

        size_t capacity() const
        {
            return capacity_;
        }

        size_t size() const
        {
            return size_;
        }

        void swap(vector& other)
        noexcept
        {
            std::swap(data_, other.data_);
            std::swap(capacity_, other.capacity_);
            std::swap(size_, other.size_);
        }

        void reserve(size_t capacity)
        {
            if (capacity>capacity_) {
                T* temp{nullptr};
                std::size_t s;

                try {
                    // allocate memory
                    temp = static_cast<T*>(::operator new(capacity*sizeof(T)));

                    // initialize elements
                    for (s = 0; s<size_; s++)
                        new(temp+s) T(data_[s]);
                }
                catch (...) {
                    // destroy elements
                    for (std::size_t d{0}; d<s; d++)
                        data_[d].T::~T();

                    // deallocate memory
                    ::operator delete(temp);
                    throw;
                }

                // destroy elements
                for (std::size_t i{0}; i<size_; i++)
                    data_[i].T::~T();

                // deallocate memory
                ::operator delete(data_);

                data_ = temp;
                capacity_ = capacity;
            }
        }

        void pop_back()
        {
            if (size_) {
                data_[size_-1].T::~T();
                size_--;
            }
        }

        void clear()
        {
            if (size_) {
                for (std::size_t i{0}; i<size_; i++)
                    data_[i].T::~T();

                size_ = 0;
            }
        }
    };
}

#endif