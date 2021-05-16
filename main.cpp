#include "src/readFromFile.hpp"
#include "src/wikipediagraph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cout << "\nHi, Welcome to the Wikipedia Wizard 9000!" << endl;
  cout << "\nThis project was designed to help find the shortest path between "
          "Wikipedia Pages as well as identify pages that help connect many "
          "other pages."
       << endl;
  cout << "\nTo start, you can browse the different articles in our dataset by "
          "looking through the counts/complete_bfs.txt file."
       << endl;
  cout << "\nFrom here, if you want to find the shortest path between any two "
          "articles, simply run the command: ./shortestpath {article1} "
          "{article2}\n\nThe user input is case-sensitive so keep that in mind "
          "as "
          "you "
          "type in your article.\n"
       << endl;
  cout << "You can also see which articles are in the most shortest paths. You "
          "can see a leaderboard of N size by entering the command: "
          "./supernodes {integer}\n"
       << endl;
  cout << "Finally, if you want to run our tests, simple run: make test\n"
          "After that has ran, run the command: ./test\n"
       << endl;
  cout << "Thank you for using the Wikipedia Wizard 9000!\n" << endl;
}