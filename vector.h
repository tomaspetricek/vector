#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>
#include <algorithm>
#include <new>
#include <functional>

namespace epc {
    template<typename T, size_t N>
    class vector {
        std::size_t capacity_{N};
        std::size_t size_{0};
        alignas(T) unsigned char buff_[sizeof(T)*N];
        T* data_{reinterpret_cast<T*>(buff_)};

        bool is_short() const { return capacity_==N; }

        T* ptr() { return is_short() ? reinterpret_cast<T*>(buff_) : data_; }

    public:
        vector() noexcept = default;

        vector(const vector& src)
                :capacity_{src.size_}, size_{src.size_}
        {
            std::size_t s{0};

            if (!src.is_short())
                data_ = static_cast<T*>(::operator new(size_*sizeof(T)));

            try {
                for (s = 0; s<src.size(); s++)
                    new(data_+s) T(src.data_[s]);
            }
            catch (...) {
                for (std::size_t d{0}; d<s; d++)
                    data_[d].T::~T();

                ::operator delete(data_);
                throw;
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
            for (std::size_t i{0}; i<size_; i++)
                data_[i].T::~T();

            if (!is_short())
                ::operator delete(data_);
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

            new(data_+(size_)) T(el);
            size_++;
        }

        size_t capacity() const
        {
            return capacity_;
        }

        size_t size() const
        {
            return size_;
        }

        void swap(vector& other) noexcept
        {
            std::swap(capacity_, other.capacity_);
            std::swap(buff_, other.buff_);
            std::swap(size_, other.size_);
            std::swap(data_, other.data_);
            data_ = ptr();
            other.data_ = other.ptr();
        }

        void reserve(size_t capacity)
        {
            if (capacity>capacity_) {
                T* temp{nullptr};
                std::size_t s{0};

                temp = static_cast<T*>(::operator new(capacity*sizeof(T)));

                try {
                    for (s = 0; s<size_; s++)
                        new(temp+s) T(data_[s]);
                }
                catch (...) {
                    for (std::size_t d{0}; d<s; d++)
                        temp[d].T::~T();

                    ::operator delete(temp);
                    throw;
                }

                for (std::size_t i{0}; i<size_; i++)
                    data_[i].T::~T();

                if (!is_short())
                    ::operator delete(data_);

                data_ = temp;
                capacity_ = capacity;
            }
        }

        void pop_back()
        {
            data_[size_--].T::~T();
        }

        void clear()
        {
            while (size_) pop_back();
        }
    };
}

#endif
