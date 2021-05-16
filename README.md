# Wikipedia Wizard 
## Link to Presentation
You can find the presentation [here](https://drive.google.com/file/d/135HYk1zwtoyB0YfTo6Puc29CujxBheqt/view?usp=sharing).
## Setting up the environment
After you clone this repository, please open a bash terminal window and find and  the directory in the terminal window. 

Once you are in the correct directory, type in the commmand: 
```
$ make
```
After that command is finished running, type in the command:
```
$ make test
```
This will create all the executables that you will need to run our program.

## Methods 

By default, all the methods will be running using our full target dataset which can be found [here](http://snap.stanford.edu/data/wikispeedia.html).
### Instructions

To display instructions for the project, you can run the program: 
```
$ ./wikipediawizard
```

### Shortest Path between 2 Wikipedia Articles

We created an algorithm to find the shortest path between 2 articles in our graph. First, go to the following location and open the file 
```
$ counts/complete_bfs.txt
```
This file contains a list of all the articles in our graph and dataset. From here, you can choose 2 articles to run the shortest path method on. Once you have your articles, run the following command: 
```
$ ./shortestpath {article1} {article2}
```
Keep in mind the articles must be typed in exact as it is case sensitive. 

#### Example
```
$ ./shortestpath Emacs United_States_House_of_Representatives
```
```
> Emacs
> Unix
> Ubuntu_%28Linux_distribution%29
> Zulu
> Zambia
> Zimbabwe
> Yugoslavia
> World_War_I
> Woodrow_Wilson
> United_States_House_of_Representatives
```

### Finding the most connecting articles
 
Our driving question was:
 **What are some of the articles on Wikipedia that bridge many other articles?**

In order to answer this question, we created a method that would find these "super articles" by counting how many times articles within all of the shortest paths in our dataset. 

We have a method that will print out a leaderboard from high to low of the articles that are in the most shortest paths. In order to find out the results that we found, type in the following command with an argument for the top Nth articles:

    $ ./supernodes {integer}

#### Example
```
$ ./supernodes 5
```
```
> 1. ------
> 2. ------
> 3. ------
> 4. ------
> 5. ------
```
We have hidden the results as to not ruin the surprise.


## Tests

We have created a test suite that relies on a smaller test dataset we have created. We have maintained the same format of our dataset but instead of using names of Wikipedia articles, we chose to use the names of our friends to reduce confusion and create some edge cases and oddities in our dataset. In order to run our tests, run the following command:
```
$ ./test
```
Additionally, our project does not leak any memory which can be tested by running:
```
$ valgrind ./test
```

## Codebase 

In the outermost directory, the following are the relevant folders:

- src
- data
- counts
- tests

We will start with the src folder. This folder contains all of our methods and implementations of graphs. The following files are the most relevant:
- readFromFile.hpp/cpp
- wikipediagraph.h/cpp

readFromFile contains the code that allows us to easily parse our dataset and create a WikiGraph object from our datasets. wikipediagraph contains the code and structure of our graph implementation. Because our graph is an undirected and unweighted graph, we did not really see the need to create a Node/Edge struct. Instead, we implemented an adjancency list. We also created an iterator which would traverse our adjacency list using a BFS. Our methods for our algorithms are also housed within the WikiGraph object. 

The data folder contains the raw .csv file of our dataset of Wikipedia articles. This was sourced from [SNAP Datasets](http://snap.stanford.edu/data/wikispeedia.html).

The counts folder contains .txt files of outputs of our code. One of these is a complete BFS of our dataset. We have this saved as an output so that someone can browse through all the articles in one place in order to find articles to utilize for the Shortest Path method we implemented. We also have a file for titled the shortest_path_counts.txt. This file contains the number of times an article is in a shortest path between any 2 other articles. We created this .txt file from the findSuperNodes() method in the WikiGraph object. It took around 45 minutes to generate it from our dataset so we chose to write the output to a file we can read from instead of running the code each time. 

The final folder is the tests folder. This contains our tests as well as testing dataset. For our testing dataset, we copied the format of the main dataset and chose to put the names of our friends in place of articles for simplicity. We have included a visual representation of how our test graph looks like. 


## Acknowledgements

Project created by Pratyush Tulsian(tulsian3), Ajit Singh(ajitps2), Eshaan Bhattad(eshaan2) and Sathvik Daaram(sdaaram2). 

This project was created for CS225: Data Structures Introduction to Data Structures and Algorithms with C++.
