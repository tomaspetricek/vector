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
            vector* shorter{nullptr};
            vector* longer{nullptr};

            if (size_<other.size_) {
                shorter = this;
                longer = &other;
            }
            else {
                shorter = &other;
                longer = this;
            }

            if (shorter->is_short()) {
                T* shorter_buff = reinterpret_cast<T*>(shorter->buff_);
                T* longer_buff = reinterpret_cast<T*>(longer->buff_);

                // two short
                if (longer->is_short()) {
                    for (std::size_t i{0}; i<shorter->size_; i++)
                        std::swap(shorter_buff[i], longer_buff[i]);

                    for (std::size_t i{shorter->size_}; i<longer->size_; i++) {
                        new(shorter_buff+i) T(longer_buff[i]);
                        longer_buff[i].T::~T();
                    }
                }
                // long and short
                else {
                    for (std::size_t i{0}; i<shorter->size_; i++) {
                        new(longer_buff+i) T(shorter_buff[i]);
                        shorter_buff[i].T::~T();
                    }

                    shorter->data_ = longer->data_;
                    longer->data_ = longer_buff;
                }
            }
            // two long
            else {
                std::swap(shorter->data_, longer->data_);
            }

            std::swap(capacity_, other.capacity_);
            std::swap(size_, other.size_);
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
            data_[--size_].T::~T();
        }

        void clear()
        {
            while (size_) pop_back();
        }
    };
}

#endif