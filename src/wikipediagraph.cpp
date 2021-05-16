#include "wikipediagraph.h"
#include "readFromFile.hpp"
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::string;
using std::stringstream;
using std::vector;

WikiGraph::WikiGraph(string fileName) {

  vector<string> lines = file_to_vector(fileName);

  for (string line : lines) {
    vector<string> parsed;
    stringstream input_stringstream(line);
    string token;

    while (getline(input_stringstream, token, ',')) {
      parsed.push_back(token);
    }

    insertEdge(parsed[0], parsed[1]);
  }

  traversal = bfs();
}

void WikiGraph::insertEdge(string page, string linkedPage) {

  // find page in graph and create new adj list if needed
  auto it = adjList.find(page);
  if (it == adjList.end())
    adjList[page] = vector<string>();

  // add the edge to the edge list
  vector<string> &edgeList = adjList[page];
  edgeList.push_back(linkedPage);
}

void WikiGraph::print() {

  cout << "Adjacency List form:" << endl;
  for (auto &it : adjList) {
    cout << it.first;
    cout << ": ";
    for (string link : getLinks(it.first)) {
      cout << link;
      cout << " ";
    }
    cout << endl;
  }
}

void WikiGraph::printAdj(string page) {
  cout << "Adjacency List for " << page << endl;

  vector<string> adj = getLinks(page);
  cout << "size:" << adj.size() << endl;

  for (string link : getLinks(page)) {
    cout << link;
    cout << " ";
  }
  cout << endl;
}

vector<string> WikiGraph::getLinks(string page) { return adjList[page]; }

WikiGraph::GraphIterator::GraphIterator(map<string, vector<string>> &adjList_,
                                        bool end_)
    : adjList(adjList_) {
  end = end_;
  current = "";
}

WikiGraph::GraphIterator::GraphIterator(map<string, vector<string>> &adjList_)
    : adjList(adjList_) {
  adjList = adjList_;

  for (auto &it : adjList) {
    marked[it.first] = false;
  }

  source = adjList.begin()->first;
  current = source;

  marked[current] = true;
  bfs.push(current);
}

WikiGraph::GraphIterator WikiGraph::begin() { return GraphIterator(adjList); }

WikiGraph::GraphIterator WikiGraph::end() {
  return GraphIterator(adjList, true);
}

map<string, vector<string>> WikiGraph::findAllShortestPaths(string source) {
  priority_queue<string> queue;
  map<string, string> pred;
  map<string, int> dist;
  map<string, bool> visited;
  map<string, vector<string>>::iterator it;
  for (it = adjList.begin(); it != adjList.end(); it++) {
    visited.insert(pair<string, bool>(it->first, false));
    dist.insert(pair<string, int>(it->first, INT_MAX));
    pred.insert(pair<string, string>(it->first, ""));
  }

  visited[source] = true;
  dist[source] = 0;
  queue.push(source);

  while (!queue.empty()) {
    string u = queue.top();
    queue.pop();

    for (size_t i = 0; i < adjList[u].size(); i++) {
      if (!visited[adjList[u][i]]) {
        visited[adjList[u][i]] = true;
        dist[adjList[u][i]] = dist[u] + 1;
        pred[adjList[u][i]] = u;
        queue.push(adjList[u][i]);
      }
    }
  }

  map<string, vector<string>> paths;
  for (auto it = visited.begin(); it != visited.end(); it++) {
    vector<string> path;
    string crawl = it->first;
    path.push_back(crawl);
    while (!pred[crawl].empty()) {
      path.push_back(pred[crawl]);
      crawl = pred[crawl];
    }
    std::reverse(path.begin(), path.end());
    paths[it->first] = path;
  }
  return paths;
}
vector<string> WikiGraph::shortestPath(string source, string target) {
  priority_queue<string> queue;
  map<string, string> pred;
  map<string, int> dist;
  map<string, bool> visited;
  map<string, vector<string>>::iterator it;
  for (it = adjList.begin(); it != adjList.end(); it++) {
    visited.insert(pair<string, bool>(it->first, false));
    dist.insert(pair<string, int>(it->first, INT_MAX));
    pred.insert(pair<string, string>(it->first, ""));
  }

  visited[source] = true;
  dist[source] = 0;
  queue.push(source);
  bool breakLoop = false;

  while (!queue.empty()) {
    string u = queue.top();
    queue.pop();

    for (size_t i = 0; i < adjList[u].size(); i++) {
      if (!visited[adjList[u][i]]) {
        visited[adjList[u][i]] = true;
        dist[adjList[u][i]] = dist[u] + 1;
        pred[adjList[u][i]] = u;
        queue.push(adjList[u][i]);
        if (adjList[u][i] == target) {
          breakLoop = true;
          break;
        }
      }
    }
    if (breakLoop) {
      break;
    }
  }

  vector<string> path;
  string crawl = target;
  path.push_back(crawl);
  while (!pred[crawl].empty()) {
    path.push_back(pred[crawl]);
    crawl = pred[crawl];
  }
  std::reverse(path.begin(), path.end());
  return path;
}

string WikiGraph::GraphIterator::operator*() {
  if (end)
    return "";
  else
    return current;
}
bool WikiGraph::GraphIterator::operator!=(const GraphIterator &other) {
  string otherCurrent = other.current;

  bool thisEmpty = false;
  bool otherEmpty = false;

  if (current.empty()) {
    thisEmpty = true;
  }
  if (other.current.empty()) {
    otherEmpty = true;
  }

  if (!bfs.empty()) {
    thisEmpty = bfs.empty();
  }
  if (!other.bfs.empty()) {
    otherEmpty = other.bfs.empty();
  }

  if (thisEmpty && otherEmpty)
    return false;
  else if ((!thisEmpty) && (!otherEmpty))
    return (current != otherCurrent);
  else
    return true;
}

WikiGraph::GraphIterator WikiGraph::GraphIterator::operator++() {

  marked[current] = true;

  // get relevent links

  for (string link : adjList[current]) {
    if (isMarked(link)) {
      continue;
    } else {
      bfs.push(link);
    }
  }

  // get next link
  while (!bfs.empty() && isMarked(bfs.front())) {
    bfs.pop();
    if (bfs.empty()) {
      current = "";
      return *this;
    }
  }
  if (!bfs.empty()) {
    current = bfs.front();
    return *this;
  } else {
    return *this;
  }

  bfs.push(current);

  return *this;
}

bool WikiGraph::GraphIterator::isMarked(string p) { return marked[p]; }

vector<string> WikiGraph::bfs() {
  map<string, bool> marked;
  for (auto s : adjList) {
    marked[s.first] = false;
  }
  string source = adjList.begin()->first;
  string current = source;
  queue<string> bfs;
  marked[current] = true;
  bfs.push(current);

  marked[current] = true;

  vector<string> traversal;

  // get relevent links

  while (!bfs.empty()) {
    // dequeue the vertex
    current = bfs.front();
    bfs.pop();
    traversal.push_back(current);

    // get all adjacent vertices of popped vertex and process each if not
    // already visited
    for (auto it = adjList[current].begin(); it != adjList[current].end();
         ++it) {
      if (!marked[*it]) {
        marked[*it] = true;
        bfs.push(*it);
      }
    }
  }
  return traversal;
}

void WikiGraph::findSuperNodes() {
  map<string, int> counts;
  // Initialize all counts to be 2n
  for (unsigned int i = 0; i < traversal.size(); i++) {
    counts[traversal[i]] = 2 * (traversal.size() - 1);
  }
  // Get all pages alphabetically
  sort(traversal.begin(), traversal.end());
  // Loop through all the pages and run Djikstras
  for (unsigned int i = 0; i < traversal.size() - 1; i++) {
    map<string, vector<string>> paths = findAllShortestPaths(traversal[i]);
    for (auto it = paths.begin(); it != paths.end(); ++it) {
      vector<string> path = it->second;
      shortenPath(path);
      for (unsigned int i = 0; i < path.size(); i++) {
        // Increment the pages in the path
        counts[path[i]] += 1;
      }
    }
  }

  // Write the counts to a txt file to avoid running each time
  std::ofstream myfile;
  myfile.open("counts.txt");
  for (auto const &pair : counts) {
    myfile << pair.first << "," << pair.second - 2 * (traversal.size() - 1)
           << "\n";
  }
  myfile.close();
}

bool WikiGraph::sortCountValues(pair<string, int> &a, pair<string, int> &b) {
  return a.second < b.second;
}

void WikiGraph::displaySuperNodes(unsigned int n) {
  // Create vector of pairs to track counts
  vector<pair<string, int>> counts;
  // Import in the counts from txt file
  vector<string> lines = file_to_vector("counts/shortest_path_counts.txt");
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
  for (unsigned int i = 0; i < n; i++) {
    cout << i + 1 << ".\t" << counts[i].first << ": " << counts[i].second
         << " paths" << endl;
  }
}

void WikiGraph::shortenPath(vector<string> &path) {
  // Remove first and last element
  path.pop_back();
  if (path.size() > 0) {
    path.erase(path.begin());
  }
}

map<string, vector<string>> WikiGraph::getAdjList() { return adjList; }
