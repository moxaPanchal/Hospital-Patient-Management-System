
#include <iostream>
#include <fstream>
#include "PreTriage.h"
#include "utils.h"
using namespace sdds;
using namespace std;
int main() {
   sdds::debug = true;
   ofstream("data.csv").close();
   PreTriage P("data.csv");
   P.run();
   return 0;
}

