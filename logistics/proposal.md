<!-- Output copied to clipboard! -->

<!-- Yay, no errors, warnings, or alerts! -->

<p>
abhakat2, apirani2, jsneh2, shlokm2
</p>
<p>
FINAL PROJECT PROPOSAL
</p>
<p>
<em>HIGH-LEVEL SUMMARY</em>
</p>
<p>
Given any text-based data (books, scripts, transcripts, etc), our program should be able to process the data in such a way that it can “generate” sentences that replicate those of the original text, based on the frequency of predecessor-successor pairs. These sentences may not have any semantic meaning, but are simply representations of the most commonly chained-together words. We will use two different methods to generate sentences of a given length: a deterministic walk based on the highest-frequency next word, and a probabilistic walk, where each word’s frequency weight represents a probability that it will be chosen. Overall, this is an experiment in analyzing vocabulary, and word/phrase usage, along with being a form of naive text prediction.
</p>
<p>
<strong><em>DATA ACQUISITION AND PRE-PROCESSING</em></strong>
</p>
<ul>

<li><strong>Data Format</strong>: We will gather our data as a txt from online resources. We have linked the resources below under the <span style="text-decoration:underline;">Datasets</span> section. They are txt files so they should be easy to work with and process.

<li><strong>Textual Pre-processing</strong>: For our data correction we will exclude all punctuation from our text unless it refers to a period or ending remark of a sentence. (“?”, “!”, “.”). We also plan on removing common frequency words (“the”, “it”, “a”, “and”) from our texts. Our preprocessing will be done in Python. Punctuation removement should be trivial w/ simple search. To remove the filler words, we will store each unique word in the text along with its occurrences and remove a certain percentage of the most commonly occurring words through manual examination. Sophisticated words which occur a small number of times may also be removed depending on our pending result. We may remove uncommon words to reduce the size of our dataset, since texts can be extremely large and contain rarely-used words that we would not regularly encounter.

<li><strong>Data Storage</strong>: Our initial graph will be stored as an adjacency list, making it O(V). Each edge struct will contain a start word, an end word, and a weight (representing the amount of times two words are repeated). For our SSSP algorithm, we’ll also need a dictionary to get all potential outputs. This is also an extra O(V) space for each call.

<li><strong>Example/Primary Datasets</strong>: 
<ul>
 
<li><a href="https://github.com/formcept/whiteboard/tree/master/nbviewer/notebooks/data/harrypotter">Harry Potter</a> (primary dataset)
 
<li><a href="https://raw.githubusercontent.com/mxw/grmr/master/src/finaltests/bible.txt">The King James Bible</a> (secondary goal)
 
<li><a href="https://ocw.mit.edu/ans7870/6/6.006/s08/lecturenotes/files/t8.shakespeare.txt">The Complete Works of William Shakespeare</a> (secondary goal)
</li> 
</ul>

<li><strong>Data Preprocessing</strong> (txt) 
<ul>
 
<li><span style="text-decoration:underline;">Input:</span> .txt file
 
<li><span style="text-decoration:underline;">Output</span>: Graph representation of text in the file
 
<li><span style="text-decoration:underline;">Functionality</span>: After our necessary preprocessing steps, we will construct a directed graph between every pair of subsequent words where the 2 words are nodes and the directed edge between them represents the occurrence of that particular series of subsequent words. 
 
<li>Our end result should be a series of disjoint directed graphs with weighted edges between various word pairings
 
<li>In order to deal with potential issues given the size of our dataset, we’ll initially test our graphs (and subsequently our algorithms) with smaller subsections of the text to determine how our algorithm is performing before running on the entirety.
 
<li><span style="text-decoration:underline;">Efficiency</span>: O(N) time, O(N) space; N = number of words in the text
 
<li><span style="text-decoration:underline;">Potential Issues</span>: non-supported characters, cyclic graphs, massive datasets. 
</li> 
</ul>
</li> 
</ul>
<p>
<strong><em>ALGORITHMS</em></strong>
</p>
<p>
We plan on using a series of algorithms for our project in order to deliver our end result. 
</p>
<p>
The Backtracking algorithm will be used to determine the most “likely” sentence from a word. By using this algorithm, we’ll search through all possible paths and return the highest-weight sentence. It will run recursively, store the current highest-weight path, and backtrack to search all nodes. This algorithm is deterministic - running it multiple times will give us the same output.
</p>
<p>
The Probabilistic weighted sentence generation will enable us to sample commonly occurring sentences based on weighted probabilities from each node. With this, more commonly occurring sentences will appear more often so we will be able to get an accurate distribution of sentences if we run multiple times.
</p>
<p>
We’ll use BFS to display our graph.
</p>
<ol>

<li>Backtracking (Graph)  
<ul>
 
<li>Input: Starting word, Length of sentence
 
<li>Output: Most likely phrase given a particular path length
 
<li>Functionality: Returns the sentence of the given length with the highest frequency weight starting from the given word. In order to do this we will pass 3 parameters  (Node, current weight sum, word number) and find the sentence with the maximum “length”/frequency weight, through recursive calls and backtracking.
 
<li>Efficiency: O(VE) time, O(V+E) space; V = vertices, E = edges; (on a subgraph of all nodes N steps away; N = sentence length)
</li> 
</ul>

<li>Probabilistic weighted sentence generation (Graph)  
<ul>
 
<li>Input: Target word, Length of sentence
 
<li>Output: A sentence based on a probabilistic path using the weights connected to a given word
 
<li>Functionality: Using a starting word, the traversal will walk through a series of nodes determined randomly based on the edge weights. In this way, more frequently used words would have a larger probability of being chosen next, though the whole sentence would be randomly constructed.
 
<li>Efficiency: O(N) time for approach, O(N) space; N = length of sentence. 
</li> 
</ul>

<li>Breadth-First Traversal (Graph)  
<ul>
 
<li>Input: Starting Word
 
<li>Output: Representation of Graph by printing out the word and its corresponding edges.
 
<li>Functionality: The traversal starts at the starting word, which it displays, and also displays its children along with the weight leading to it. Using a queue, we will add the unvisited nodes to the graph and follow the same algorithm of processing it and then adding its children. We will do this for each of the connected components in order to display our entire word set.
 
<li>O(V + E) time with V = vertices and E = edges, O(V) space (queue).
</li> 
</ul>

<li>Connected Components <em><span style="text-decoration:underline;">(This is a stretch goal which we may not achieve)</span></em> 
<ul>
 
<li>Input: Graph
 
<li>Output: Set of connected components, Relative Strength of Each Component
 
<li>Purpose: Determine which words appear together in sentences, and which do not. We will also determine the “strength” of each connected component by summing up the weights of all the edges in a connected component and dividing it by the number of nodes. 
 
<li><strong>Note: </strong>we may not implement this if we end up removing uncommon words, and thus, weaker connected components.
 
<li>Efficiency: O(V+E) time for naive approach, O(V) space; V = words/vertices, E = edges  
<ul>
  
<li>Kosaraju’s algorithm. 
</li>  
</ul>
</li>  
</ul>
</li>  
</ol>
<p>
<em>TIMELINE:</em>
</p>
<ul>

<li>March 25: Proposal submission.

<li>March 26 to April 1: Proposal confirmation + finding example datasets.

<li>April 2 to April 8: Rudimentary data processing algorithm.
</li>
</ul>
<p>
<strong>— NEW TIMELINE —</strong>
</p>
<ul>

<li>April 17 to April 20: Data Preprocessing + Set Up of Classes

<li>April 20 to April 25: Write backtracking algorithm + start probabilistic

<li>April 25 to April 30: Finish probabilistic algorithm + BFS

<li>May 1 - May 6: Touch up testing, presentation, and everything else
</li>
</ul>
