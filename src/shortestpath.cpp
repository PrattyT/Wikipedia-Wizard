#include "readFromFile.hpp"
#include "wikipediagraph.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

<<<<<<< HEAD:shortestpath.cpp
/**
 * @todo take in user input as arguments
 */
#include <fstream>
#include <iostream>

=======
>>>>>>> ababcad5ad12177a164f48aa5e80d25974cc21a8:src/shortestpath.cpp
int main(int argc, char *argv[]) {

  if (argc != 3) {
    cout << "Pleaes try again with exactly one start and end page" << endl;
    return 0;
  }

<<<<<<< HEAD:shortestpath.cpp
  WikiGraph g("tests/wikidata.txt");
=======
  WikiGraph g("data/wikidata.txt");
>>>>>>> ababcad5ad12177a164f48aa5e80d25974cc21a8:src/shortestpath.cpp

  vector<string> answer = g.shortestPath(argv[1], argv[2]);

  std::fstream fs;

  for (string x : answer) {
    string url = "https://en.wikipedia.org/wiki/" + x;
    fs.open(url);
    cout << x << endl;
  }
<<<<<<< HEAD:shortestpath.cpp

  fs.close();

=======
>>>>>>> ababcad5ad12177a164f48aa5e80d25974cc21a8:src/shortestpath.cpp
  return 0;
}