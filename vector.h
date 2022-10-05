#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>

namespace epc
{
   template <typename T>
   class vector
   {
      public:
         vector() noexcept { }

         vector(const vector&) { }

         vector& operator=(const vector&) { }

         ~vector() { }

         T* data() { }
         const T* data() const { }

         T& operator[](size_t) { }
         const T& operator[](size_t) const { }

         void push_back(const T&) { }

         void swap(vector& other) noexcept { }

         size_t capacity() const { }
         size_t size() const { }

         void reserve(size_t) { }

         void pop_back() { } 
   };
}

#endif
