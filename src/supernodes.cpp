#include "readFromFile.hpp"
#include "wikipediagraph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 2) {
    cout << "Please enter the number of top nodes" << endl;
    return 0;
  }
  WikiGraph g("data/wikidata.txt");
  // unsigned int n = 10;
  unsigned int topN = stoi(argv[1]);
  g.displaySuperNodes(topN);
  return 0;
}