#define BOOST_TEST_MODULE practical4_test

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

#include "X.h"

BOOST_AUTO_TEST_CASE(empty_vector_test)
{
   X::reset();

   epc::vector<X, 2> v;

   BOOST_TEST( v.data() == nullptr );
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 0 );

   BOOST_TEST( X::constructed() == 0 );
}

