#define BOOST_TEST_MODULE practical3_test

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

#include "X.h"

BOOST_AUTO_TEST_CASE(empty_vector_test)
{
   X::reset();

   epc::vector<X> v;

   BOOST_TEST( v.data() == nullptr );
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 0 );

   BOOST_TEST( X::constructed() == 0 );
}

BOOST_AUTO_TEST_CASE(reserve_test)
{
   X::reset();

   epc::vector<X> v;
   v.reserve(3);

   BOOST_TEST( v.data() != nullptr );
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 3 );

   BOOST_TEST( X::constructed() == 0 );
}

BOOST_AUTO_TEST_CASE(push_back_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(2);

      auto data = v.data();

      v.push_back(1);
      v.push_back(2);

      BOOST_TEST( v.data() == data );
      BOOST_TEST( v.size() == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(2);

      v.push_back(1);
      v.push_back(2);

      auto destructed = X::destructed();

      v.pop_back();

      BOOST_TEST( v.size() == 1 );
      BOOST_TEST( v.capacity() == 2 );
      BOOST_TEST( X::destructed() == destructed + 1 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(clear_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(2);

      v.push_back(1);
      v.push_back(2);

      auto destructed = X::destructed();

      v.clear();

      BOOST_TEST( v.size() == 0 );
      BOOST_TEST( v.capacity() == 2 );
      BOOST_TEST( X::destructed() == destructed + 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}


BOOST_AUTO_TEST_CASE(reallocation_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(2);

      v.push_back(1);
      v.push_back(2);

      auto data = v.data();

      v.push_back(3);

      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v.data() != data );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(2);

      v.push_back(1);
      v.push_back(2);

      epc::vector<X> v2(v);

      BOOST_TEST( v2.size() == 2 );
      BOOST_TEST( v2.data() != v.data() );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_assignment_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(2);

      v.push_back(1);
      v.push_back(2);

      epc::vector<X> v2;

      v2.push_back(3);

      v2 = v;

      BOOST_TEST( v2.size() == 2 );
      BOOST_TEST( v2.data() != v.data() );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}
