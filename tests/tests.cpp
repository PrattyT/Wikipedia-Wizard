#include "../src/wikipediagraph.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "../catch/catch.hpp"
#include "../src/readFromFile.hpp"

bool sortCountValues(pair<string, int> &a, pair<string, int> &b) {
  return a.second < b.second;
}

TEST_CASE("Verify that file_to_string works on a small example") {

  WikiGraph g("tests/simplegraph.txt");

  SECTION("Size check") { REQUIRE(g.getAdjList().size() == 12); }

  SECTION("Check adj lists") {
    vector<string> adjTo3 = g.getLinks("eshaan");
    REQUIRE(adjTo3[0] == "pratyush");
    REQUIRE(adjTo3[1] == "ajit");
  }
}

TEST_CASE("Verify the traversal with iterator works ") {

  WikiGraph g("tests/simplegraph.txt");
  vector<string> output;
  for (auto it : g) {
    output.push_back(it);
  }
  REQUIRE(output[0] == "aadarsh");
  REQUIRE(output[1] == "pratyush");
  REQUIRE(output[2] == "eshaan");
  REQUIRE(output[3] == "sathvik");
}
TEST_CASE("Verify the traversal with BFS method works ") {

  WikiGraph g("tests/simplegraph.txt");
  vector<string> output = g.bfs();
  for (auto it : g) {
    output.push_back(it);
  }
  REQUIRE(output[0] == "aadarsh");
  REQUIRE(output[1] == "pratyush");
  REQUIRE(output[2] == "eshaan");
  REQUIRE(output[3] == "sathvik");
}

TEST_CASE("Test Shortest Path with same element") {
  WikiGraph g("tests/simplegraph.txt");
  vector<string> output = g.shortestPath("pratyush", "pratyush");
  REQUIRE(output.size() == 1);
  REQUIRE(output[0] == "pratyush");
}

TEST_CASE("Test Shortest Path between neighbors") {
  WikiGraph g("tests/simplegraph.txt");
  vector<string> output = g.shortestPath("pratyush", "eshaan");
  REQUIRE(output.size() == 2);
  REQUIRE(output[0] == "pratyush");
  REQUIRE(output[1] == "eshaan");
}

TEST_CASE("Test Shortest Path between nodes more than 1 node apart") {
  WikiGraph g("tests/simplegraph.txt");
  vector<string> output = g.shortestPath("nikil", "ajit");
  REQUIRE(output.size() == 5);
  REQUIRE(output[0] == "nikil");
  REQUIRE(output[1] == "aryan");
  REQUIRE(output[2] == "anish");
  REQUIRE(output[3] == "arsh");
  REQUIRE(output[4] == "ajit");
}
TEST_CASE("Shortest Path from A to B is the same from B to A") {
  WikiGraph g("tests/simplegraph.txt");
  vector<string> output = g.shortestPath("nikil", "ajit");
  vector<string> output2 = g.shortestPath("ajit", "nikil");
  REQUIRE(output.size() == output2.size());
}
TEST_CASE("Test top 5 Super Nodes from test data") {
  // Create vector of pairs to track counts
  vector<pair<string, int>> counts;
  // Import in the counts from txt file
  vector<string> lines = file_to_vector("tests/counts.txt");
  for (string line : lines) {
    vector<string> parsed;
    stringstream input_stringstream(line);
    string token;

    while (getline(input_stringstream, token, ',')) {
      parsed.push_back(token);
    }

    pair<string, int> pair = std::make_pair(parsed[0], stoi(parsed[1]));
    counts.push_back(pair);
  }
  // Sort the counts based on frequency
  sort(counts.begin(), counts.end(), sortCountValues);
  reverse(counts.begin(), counts.end());

  // Display the top 5 most traversed pages.
  REQUIRE(counts[0].first == "arsh");
  REQUIRE(counts[1].first == "ajit");
  REQUIRE(counts[2].first == "anish");
  REQUIRE(counts[3].first == "sathvik");
  REQUIRE(counts[4].first == "aryan");
}

TEST_CASE("Super nodes file lines is equal to number of nodes in dataset") {
  // Create vector of pairs to track counts
  WikiGraph g("tests/simplegraph.txt");
  vector<pair<string, int>> counts;
  // Import in the counts from txt file
  vector<string> lines = file_to_vector("tests/counts.txt");
  for (string line : lines) {
    vector<string> parsed;
    stringstream input_stringstream(line);
    string token;

    while (getline(input_stringstream, token, ',')) {
      parsed.push_back(token);
    }

    pair<string, int> pair = std::make_pair(parsed[0], stoi(parsed[1]));
    counts.push_back(pair);
  }

  REQUIRE(counts.size() == g.getAdjList().size());
}
