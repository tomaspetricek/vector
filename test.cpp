#define BOOST_TEST_MODULE practical4_test

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

#include "X.h"

BOOST_AUTO_TEST_CASE(empty_vector_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      BOOST_TEST( v.size() == 0 );
      BOOST_TEST( v.capacity() == 2 );
   }

   BOOST_TEST( X::constructed() == 0 );
   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_vector_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);

      BOOST_TEST( v.size() == 2 );
      BOOST_TEST( v.capacity() == 2 );

      unsigned char* begin = reinterpret_cast<unsigned char*>(&v);
      unsigned char* end = begin + sizeof(v);

      unsigned char* data = reinterpret_cast<unsigned char*>(v.data());

      BOOST_TEST(( (data >= begin) && (data < end) ));
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_vector_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      unsigned char* begin = reinterpret_cast<unsigned char*>(&v);
      unsigned char* end = begin + sizeof(v);

      unsigned char* data = reinterpret_cast<unsigned char*>(v.data());

      BOOST_TEST(( (data < begin) || (data >= end) ));
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_copy_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);

      epc::vector<X, 2> v_copy(v);

      BOOST_TEST( v_copy.size() == 2 );
      BOOST_TEST( v_copy.capacity() == 2 );

      unsigned char* begin = reinterpret_cast<unsigned char*>(&v_copy);
      unsigned char* end = begin + sizeof(v_copy);

      unsigned char* data = reinterpret_cast<unsigned char*>(v_copy.data());

      BOOST_TEST(( (data >= begin) && (data < end) ));
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_copy_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      epc::vector<X, 2> v_copy(v);

      BOOST_TEST( v_copy.size() == 3 );

      unsigned char* begin = reinterpret_cast<unsigned char*>(&v_copy);
      unsigned char* end = begin + sizeof(v_copy);

      unsigned char* data = reinterpret_cast<unsigned char*>(v_copy.data());

      BOOST_TEST(( (data < begin) || (data >= end) ));
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_long_swap_test)
{
   X::reset();

   {
      epc::vector<X, 2> v1;

      v1.push_back(1);
      v1.push_back(2);
      v1.push_back(3);

      epc::vector<X, 2> v2;
      v2.push_back(4);
      v2.push_back(5);
      v2.push_back(6);
      v2.push_back(7);

      v1.swap(v2);

      BOOST_TEST( v1.size() == 4 );
      BOOST_TEST( v2.size() == 3 );

      BOOST_TEST( v1[0] == 4 );
      BOOST_TEST( v1[1] == 5 );
      BOOST_TEST( v1[2] == 6 );
      BOOST_TEST( v1[3] == 7 );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
      BOOST_TEST( v2[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_short_swap_test)
{
   X::reset();

   {
      epc::vector<X, 2> v1;

      v1.push_back(1);
      v1.push_back(2);

      epc::vector<X, 2> v2;
      v2.push_back(3);

      v1.swap(v2);

      BOOST_TEST( v1.size() == 1 );
      BOOST_TEST( v2.size() == 2 );

      BOOST_TEST( v1[0] == 3 );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_long_swap_test)
{
   X::reset();

   {
      epc::vector<X, 2> v1;

      v1.push_back(1);
      v1.push_back(2);

      epc::vector<X, 2> v2;
      v2.push_back(3);
      v2.push_back(4);
      v2.push_back(5);

      v1.swap(v2);

      BOOST_TEST( v1.size() == 3 );
      BOOST_TEST( v2.size() == 2 );

      BOOST_TEST( v1[0] == 3 );
      BOOST_TEST( v1[1] == 4 );
      BOOST_TEST( v1[2] == 5 );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}
