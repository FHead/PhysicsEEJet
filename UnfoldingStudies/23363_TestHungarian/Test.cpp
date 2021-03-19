#include <map>
#include <vector>
using namespace std;

#include "Matching.h"


double Metric(int G, int R)
{
   double Cost[5][5] =
   {
      {11, 7, 10, 17, 10},
      {13, 21, 7, 11, 13},
      {13, 13, 15, 13, 14},
      {18, 10, 13, 16, 14},
      {12, 8, 16, 19, 10}
   };
   return Cost[G][R];
}

int main(int argc, char *argv[])
{
   vector<int> Gen{0, 1, 2, 3, 4};
   vector<int> Reco{0, 1, 2, 3, 4};

   double (*Distance)(int, int) = Metric;

   map<int, int> Mapping = MatchJetsHungarian(Distance, Gen, Reco);

   cout << "Final mapping: " << endl;
   for(int i = 0; i < 5; i++)
      cout << i << " " << Mapping[i] << endl;

   return 0;
}

