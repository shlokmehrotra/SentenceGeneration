<h1> Sentence Generation with Predecessor-Successor Word Pairs </h1>
<p>Final Project for apirani2-shlokm2-abhakat2-jsneh2 <p>

<br>
<h2> Running the Code </h2>
Compile the program with <code>make</code> in the root directory. 

The program should be run on a text file that only contains words and numbers and is space-delimited, with the following command: <code>./bin/exec [arg1]</code>, where <code>[arg1]</code> represents the filepath of the text file to be run on. If there is no argument, then the text defaults to <code>parsed_book1.txt</code>, which is the first Harry Potter book.

(Note that most of the examples reference the first book of the Harry Potter series, Harry Potter and the Sorcerer's Stone.)

<h2> Development Process </h2>

<h3> Preprocessing </h3>
Our preprocessor written in <code>processing/file_cleaner.py</code> is applied in the source available at this url <code> https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%201%20-%20The%20Philosopher's%20Stone.txt </code>, but it can be applied to any text file. Our post-processed version of the first book is available at <code>processing/parsed_book.txt</code>.

<br>

<h3> The Code</h3>
Given a text without any punctuation, our code compiles the file as a single connected component. The graph is created as a adjacency list, where each node represents a word and has directed weighted edges to any word that succeeds it in the text. In this case, the weight of any edge is defined as the number of times that the particular predecessor-successor pair occurs.


<h2> Algorithms </h2>
We explored various methods of generating phrases/sentences of a given path length using differing techniques. The traversals we used can be summarized below: <br> <br>


<li>  <b>HighestWeightSentence:</b> 
    Takes a given length and returns most likely sentence for said given length.
    
<li> <b> ProbabilisticSentence: </b>
    Takes a given length and uses a random to dictate which word to go to next in a phrase using weighted probability.
    
<li> <b> HighestGreedySentence: </b>
    For each word, this algorithm takes the word with the highest edge weight and chooses that as the next word until it creates a sentence of the given length. In case of a tie with edge weights, the word that appears in the text first is chosen.
    
<li><b>LowestGreedySentence:</b>
    For each word, this algorithm takes the word with the least edge weight and chooses the next word until it creates a sentence of the given length. In case of a tie with edge weights, the word that appears in the text last is chosen.
    
<li><b>Random Sentence:</b>
    Choses words andomly from the adjacency list disregarding the given edge weights until a sentence of the given length is created.
    
<li><b>WriteToCSV:</b>
    Creates a CSV that displays each word in the form of "element: " and below each word displays its respective adjancency list sorted from larger to lower frequency. 
    
<li><b>WriteAsBFS:</b>
    Uses a BFS to display the entire graph.

The above descriptions are also documented in our <code>graph.h</code> file.

<h3> Tests </h3>
Custom test cases that we wrote to test our implementation can be found on <code>tests/non_greedy1.txt</code> and <code>tests/non_greedy2.txt</code>.
The test cases are available on <code>tests/tests.cc</code> and can be tested by typing <code>make tests</code> followed by <code>./bin/tests</code> in the terminal in the root folder.

Current Maintainers of the project.
* Shlok Mehrotra (shlokm2)
* Aydan Pirani (apirani2)
* Jonathan Sneh (jsneh2)
* Anay Bhakat (abhakat2)
