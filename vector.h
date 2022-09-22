#ifndef EPC_VECTOR_H
#define EPC_VECTOR_H

#include <cstdlib>

namespace epc
{
    template<typename T>
    class vector {
        std::size_t capacity_{0};
        std::size_t size_{0};
        T* data_{nullptr};

    public:
        vector() noexcept = default;

        vector(const vector&) = delete;
        vector& operator=(const vector&) = delete;

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
            if (size_==capacity_) {
                // increase capacity
                capacity_ = (!capacity_) ? 1 : capacity_*2;

                // allocate new array
                T* temp = new T[capacity_];

                // copy elements
                for (size_t i{0}; i<size_; i++)
                    temp[i] = data_[i];

                // deallocate old array
                delete[] data_;

                // assign new array
                data_ = temp;
            }

            // add last element
            data_[size_++] = el;
        }

        size_t capacity() const
        {
            return capacity_;
        }

        size_t size() const
        {
            return size_;
        }
    };
}

#endif
