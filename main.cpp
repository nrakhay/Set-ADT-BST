
#include <random>
#include <algorithm>

#include "set.h"
#include "timetable.h"
#include "timer.h"

std::vector<std::string> randomvector(size_t k)
{
   std::vector<std::string> res;
   for (size_t i = 0; i != k; ++i)
   {
      std::ostringstream out;
      out << "string_" << std::abs(rand());
      res.push_back(out.str());
   }
   return res;
}

// without sorting

// Performance table of set (inputsize/runtime in seconds):
// 1000/1.5018e-03     2000/2.8289e-03     4000/2.8600e-02
// 8000/8.9792e-02     16000/2.1426e-01     32000/3.0142e-01

// totaltime 6.3840e-01

// with sorting

// Performance table of set (inputsize/runtime in seconds):
// 1000/1.8291e-02     2000/2.0357e-01     4000/7.7588e-01
// 8000/2.9261e+00     16000/1.0137e+01     32000/3.5318e+01

// totaltime 4.9379e+01

int main(int argc, char *argv[])
{
   set small; // A small test tree.

   std::cout << small.height() << "\n";
   small.insert("if");
   std::cout << small.height() << "\n";
   small.insert("the");
   std::cout << small.height() << "\n";
   small.insert("value");
   std::cout << small << "\n";
   std::cout << small.height() << "\n";

   small.clear();

   std::cout << "this is the tree: \n"
             << small << "\n";

   set small3 = small;

   std::cout << small3 << "\n";

   std::cout << small.contains("xx") << "\n";
   std::cout << small.contains("yy") << "\n";
   // Or not to be, that's the question.

#if 1
   // Some more tests:

   small.insert("oskemen");
   std::cout << small.contains("kostanay") << "\n";

   small.insert("atyrau");
   small.insert("nursultan");
   small.insert("almaty");
   small.insert("shymkent");
   small.insert("pavlodar");

   // small. checksorted( );
   std::cout << small << "\n";
   std::cout << small.size() << "\n";
   std::cout << "Height is " << small.height();
   std::cout << " should be approximately " << log_base2(small.size()) << "\n";
   // If the numbers differ much, the tree is badly balanced.

   auto small2 = small; // Copy constructor.
   std::cout << small2 << "\n";
   std::cout << "size = " << small2.size() << "\n";
   std::cout << "height = " << small2.height() << "\n";
   small2 = small; // Assignment.
   small = small;  // Self assignment.

#endif
   timetable tab(std::string("set"));

   for (size_t s = 1000; s < 4096 * 15; s = 2 * s)
   {
      // Create random test set of size s:

      std::vector<std::string> randvect = randomvector(s);

#if 0
      std::cout << "test vector: ";
      for( const auto& s : randvect )
         std::cout << s << " ";
      std::cout << "\n";
#endif

      // std::sort( randvect. begin( ), randvect. end( ));

      set someset1;

      timer tt;
      size_t nr_insertions = 0;
      for (const auto &s : randvect)
      {
         nr_insertions += someset1.insert(s);
         nr_insertions += someset1.insert(std::string("X") + s);
      }

      auto someset2 = someset1;

      if (nr_insertions != someset2.size())
      {
         std::cout << "nr = " << nr_insertions << "\n";
         std::cout << "size( ) = " << someset2.size() << "\n";
         throw std::runtime_error(
             "something went wrong with counting insertions");
      }

      // Don't use size( )! It is O(n), and will mess up your performance.

      tab.insert(s, tt.time());
      std::cout << "finished test for " << s << "\n";
   }

   std::cout << tab << "\n";
   std::cout << "totaltime " << tab.totaltime() << "\n";
}
