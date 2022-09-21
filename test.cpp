#define BOOST_TEST_MODULE practical1_test

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

class X
{
   static unsigned long
      constructed_,
      alive_,
      destructed_;

   int i_;

public:
   X() : i_(-1)
   {
      constructed_++;
      alive_++;
   }

   X(int i) : i_(i)
   {
      constructed_++;
      alive_++;
   }

   X(const X& other) : i_(other.i_)
   {
      constructed_++;
      alive_++;
   }

   X& operator=(const X& other)
   {
      i_ = other.i_;
      return *this;
   }

   ~X() 
   {
      alive_--;
      destructed_++;
   }

   operator int() const { return i_; }

   static unsigned long constructed() { return constructed_; }
   static unsigned long alive() { return alive_; }
   static unsigned long destructed() { return destructed_; }

   static void reset_counters()
   {
      constructed_ = 0;
      alive_ = 0;
      destructed_ = 0;
   }
};

unsigned long X::constructed_ = 0;
unsigned long X::alive_ = 0;
unsigned long X::destructed_ = 0;

BOOST_AUTO_TEST_CASE(empty_vector_test)
{
   X::reset_counters();

   epc::vector<X> v;

   BOOST_TEST( v.data() == nullptr );
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 0 );

   BOOST_TEST( X::constructed() == 0 );
}

BOOST_AUTO_TEST_CASE(growing_capcacity_test)
{
   X::reset_counters();

   epc::vector<X> v;
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 0 );

   v.push_back(1);
   BOOST_TEST( v.size() == 1 );
   BOOST_TEST( v.capacity() == 1 );

   v.push_back(2);
   BOOST_TEST( v.size() == 2 );
   BOOST_TEST( v.capacity() == 2 );

   v.push_back(3);
   BOOST_TEST( v.size() == 3 );
   BOOST_TEST( v.capacity() == 4 );

   v.push_back(4);
   BOOST_TEST( v.size() == 4 );
   BOOST_TEST( v.capacity() == 4 );
   
   v.push_back(5);
   BOOST_TEST( v.size() == 5 );
   BOOST_TEST( v.capacity() == 8 );
}

BOOST_AUTO_TEST_CASE(clean_up_test)
{
   X::reset_counters();

   {
      epc::vector<X> v;

      for (int i = 1; i < 8; i++)
         v.push_back(i);
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(correct_values_test)
{
   X::reset_counters();

   epc::vector<X> v;

   v.push_back(1);
   BOOST_TEST( v[0] == 1 );
   BOOST_TEST( *v.data() == 1 );

   v.push_back(2);
   BOOST_TEST( v[0] == 1 );
   BOOST_TEST( v[1] == 2 );
   BOOST_TEST( *(v.data() + 1) == 2 );

   v.push_back(3);
   BOOST_TEST( v[0] == 1 );
   BOOST_TEST( v[1] == 2 );
   BOOST_TEST( v[2] == 3 );
   BOOST_TEST( *(v.data() + 2) == 3 );
}
