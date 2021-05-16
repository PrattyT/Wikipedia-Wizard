#pragma once
// #include "graphtraversal.h"
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using std::map;
using std::pair;
using std::queue;
using std::string;
using std::vector;

class WikiGraph {

  /**
   * An iterator to traverse through a WikiGraph
   */
public:
  class GraphIterator
      : public std::iterator<std::forward_iterator_tag, string> {

  public:
    /**
     * Create a new Iterator for a WikiGraph
     */
    GraphIterator(map<string, vector<string>> &adjList_);
    GraphIterator(map<string, vector<string>> &adjList_, bool end);

    GraphIterator operator++();

    string operator*();
    bool operator!=(const GraphIterator &other);

  private:
    /**
     * Used for iteration
     */
    void pushNeighbor(string p);

    /**
     * Check to see if a string is marked
     */
    bool isMarked(string p);

    void add(const string &t);

    string pop();

    string peek();

    bool empty();

    // track visted pages
    map<string, bool> marked;

    // graph to traverse
    map<string, vector<string>> &adjList;

    // pointer to the current page
    string current;

    // starting page
    string source;

    // breadth first search
    queue<string> bfs;
    bool end;
  };

  WikiGraph();

  /**
   * Create a new graph from a file
   */
  WikiGraph(string fileName);

  /**
   * Print adj list view of graph
   */
  void print();

  /**
   * Print adj list for a page
   */
  void printAdj(string page);

  /**
   * Returns the BFS of the graph ordered in a vector
   */
  vector<string> bfs();
  /**
   * Returns the shortest paths of the graph from one node to all
   */
  map<string, vector<string>> findAllShortestPaths(string source);
  /**
   * get the pages that have a link to them on this page.
   */
  vector<string> getLinks(string page);

  /**
   * Return an iterator to the start of a graph
   * */
  GraphIterator begin();

  /**
   * Return an iterator to one past the end of the graph
   * */
  GraphIterator end();

  /**
   * Return a vector of strings containing the titles of pages that link from a
   * source to a target
   */
  vector<string> shortestPath(string source, string target);

  /**
   * Generates a txt file where each line contains a node and the # of smallest
   * paths that go through that node
   */
  void findSuperNodes();
  /**
   * Displays the Supernodes based on the top N nodes
   */
  void displaySuperNodes(unsigned int n);

  map<string, vector<string>> getAdjList();

private:
  /**
   * Adj list representation where each page (node) has a vector of pages that
   * it points to (edges).
   */
  map<string, vector<string>> adjList;

  vector<string> traversal;

  /**
   * Insert a new edge into the graph
   */
  void insertEdge(string page, string linkedPage);

  /**
   * This removes the first and last element from a path since those are just
   * the start and end articles
   */
  void shortenPath(vector<string> &path);

  /**
   * This method will sort a vector of pairs based on the integer value of the
   * pair
   */
  static bool sortCountValues(pair<string, int> &a, pair<string, int> &b);
};
