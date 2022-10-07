#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>
#include <algorithm>

namespace epc {
    template<typename T>
    class vector {
        std::size_t capacity_{0};
        std::size_t size_{0};
        T* data_{nullptr};

    public:
        vector() noexcept = default;

        vector(const vector& src)
                :capacity_{src.size_}, size_{src.size_}
        {
            try {
                data_ = size_ ? new T[size_] : nullptr;
                std::copy(src.data_, src.data_+src.size_, data_);
            }
            catch (...) {
                delete[] data_;
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
            if (capacity_) delete[] data_;
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
                data_[size_++] = el;
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

        void swap(vector& other) noexcept
        {
            std::swap(data_, other.data_);
            std::swap(capacity_, other.capacity_);
            std::swap(size_, other.size_);
        }

        void reserve(size_t capacity)
        {
            if (capacity>capacity_) {
                T* temp{nullptr};

                try {
                    temp = new T[capacity];
                    std::copy(data_, data_+size_, temp);
                }
                catch (...) {
                    delete[] temp;
                    throw;
                }

                delete[] data_;
                data_ = temp;
                capacity_ = capacity;
            }
        }

        void pop_back()
        {
            if (size_) size_--;
        }
    };
}

#endif
