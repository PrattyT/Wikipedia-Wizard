 # Results #
 
 ## Goals ##
 
 In our team's project proposal, we had clearly outlined leading prompts that drove our discovery. To directly quote the project proposal, those 2 prompts were: 
 - *"We are hoping to develop a program that can route us through the shortest path between two Wikipedia articles given that they are in the dataset."*
 - *"We also want to see whether there are certain "super-articles" that help route tons of articles between one another"*
 
 We had defined success for our project if it had: 
 - a CLI Interface
 - User input for source and target to find shortest path in a reasonable amount of time
 - User can prompt for a list of "super-articles"
 
 Based on our work and what we have produced over the course of the project, we feel confident that we have adequately accomplished these goals using the tools available to us. 
 
## Shortest Paths between 2 Articles

In order to go about accomplishing this task, we wrote a method called shortestPath, which took in a string for source and a string for target. We then used an implementation of Djikstra's Algorithm to find the shortest path between our two nodes. We return a vector of strings which is the path that you would take from the source to the target, inclusive of the source and target. 

When running the data, it runs in a very reasonable amount of time, taking no longer than around 10 seconds in our testing. The slowest part is more the importing of the data into the format we use it rather than the actual computation but in either case, it is still very fast. 

Something we were exploring as a group was trying to cache the results between a source and target as that would vastly reduce the time for searches that have already been done, but since we are not writing any data to an external database, it would be pretty impractical to save the results to a text file and reading that text file in again. 

Overall, we felt that this was very successful and works well from our testing. To try out the method, check out the README for instructions. 

## Determining Super-Nodes

Our other guiding question was to find which articles on Wikipedia help the most in linking other articles. To do this, we decided that we should write a method which gathers all the possible shortest paths in the graph, and counts how many times each article is present in the graph. We then planned to saves the counts to a .txt file, which we can read in. The methods for this is findSuperNodes() but we use displaySuperNodes() for when a user prompts for the results. 

findSuperNodes() runs a Single Source Shortest Path algorithm in order to get the shortest paths from a source to all other nodes. findSuperNodes() ran this algorithm for each node to collect the paths and tally up the nodes in the paths. Finally, the method wrote the counts to a .txt file. It took around 45 minutes to run this method on our target data and so it was smart that we had written the output to a .txt file once we had tested and ensured it works.

 Whenever a user prompts for the super nodes, displaySuperNodes() is called with an integer as a parameter. The user can choose the top Nth nodes they want to view. displaySuperNodes() then prints the results into the terminal in a very quick interval of time. We could have added summary statistics about the counts, to add some more interesting commentary on the dataset but we felt that we had still derived solid analysis from what we found.  

Now, we would like to share our findings of the our "super nodes". We have included the Top 20 here. 

	1.      World_War_II: 7347232 paths
	2.      United_States: 5141368 paths
	3.      Winston_Churchill: 4860910 paths
	4.      Water: 3510144 paths
	5.      Yugoslavia: 2472567 paths
	6.      World_War_I: 2301180 paths
	7.      Venezuela: 1695391 paths
	8.      Zimbabwe: 1691937 paths
	9.      Westminster_Abbey: 1682308 paths
	10.     Winter: 1672264 paths
	11.     William_Pitt_the_Younger: 1670552 paths
	12.     Weather: 1564021 paths
	13.     World_Health_Organization: 1397491 paths
	14.     United_Kingdom: 1387968 paths
	15.     West_Bank: 1341345 paths
	16.     Zionism: 1309245 paths
	17.     Zeus: 1176964 paths
	18.     Water_purification: 1125558 paths
	19.     Washington%2C_D.C.: 1118163 paths
	20.     Virus: 1007578 paths


While we also have tested our algorithm's accuracy formally, these results do also make a lot of sense from a logical standpoint. A lot of the Top 20 includes countries, international scale events, and nouns that are broad in application to our real life. The most interesting one we found to be "Winston Churchill" while it made sense that World War 2 would be the node being in the greatest number of shortest paths as it probably contains links to tons of countries, historical figures, important inventions, and notable events. Additionally, it is important to keep in mind that the dataset we used only contained around 4600 Wikipedia Articles, which is a very small subset of all the Wikipedia Articles in the world. Therefore, the results could be vastly different with a different dataset of the same size or a larger dataset.

## Conclusion	
We felt very happy and satisfied with the results of our final project. As a group, we felt that each member contributed a significant amount to help move things along and that in the end, we do have something concrete that provides value to us. We do think that we could keep expanding on this project and even translating what we have written to a framework or language that can be easily put on the web to make an interactive tool for users, albeit sourcing from the entirety of Wikipedia might take a hit on runtime.
