#define BOOST_TEST_MODULE practical4_test

#include <utility>

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

#include "X.h"

BOOST_AUTO_TEST_CASE(short_move_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);

      epc::vector<X, 2> v_move(std::move(v));

      BOOST_TEST( v_move.size() == 2 );

      BOOST_TEST( v_move[0] == 1 );
      BOOST_TEST( v_move[1] == 2 );

      BOOST_TEST( v.size() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_move_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      epc::vector<X, 2> v_move(std::move(v));

      BOOST_TEST( v_move.size() == 3 );

      BOOST_TEST( v_move[0] == 1 );
      BOOST_TEST( v_move[1] == 2 );
      BOOST_TEST( v_move[1] == 3 );

      BOOST_TEST( v.size() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(emplace_back_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.emplace_back(1);
      v.emplace_back(2);

      BOOST_TEST( v.size() == 2 );

      v.emplace_back(3);

      BOOST_TEST( v.size() == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

