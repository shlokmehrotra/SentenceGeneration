# Development Log

### 04/03/2022
1. We initially wanted to get our proposal approved and find datasets + create an initial commit with the structure of our codebase. Unfortunately, our proposal needed significant revision, so we met and really got into the nitty-gritty of what we wanted to accomplish. We found our datasets as well, which puts us pretty neatly on schedule if we work significantly in the next week.
2. We all worked on revising/editing/brainstorming for our proposal this week.
3. It was hard to schedule a time and also our proposal wasn't approved, so we had to work on that instead of moving forward.
4. We plan to actually write some code — more organizational is likely (function decomposition, making a small sample text, picking data structures, etc.) We may also do some text pre-processing in Python to strip "garbage".

### 4/10/2022
1. Our proposal wasn't approved, so we spent more time going over what we had to do.
2. We found a lot of minutae that was bogging our project down, and attempted to resolve these issues on paper.

### 4/17/2022
1. We finalized our proposal and coded up some barebones test cases in python to see if our algorithm would work.
2. Started designing our program. 

### 4/24/2022
We made significant progress this week for our assignment:
1. We designed the object that stores vertex information and created the method of graph storage.
2. Wrote the constructor that takes in a cleaned file and creates a graph.
3. Worked on our backtracking algorithm, which we realized is very very slow (like, exponentially slow for small numbers even). We're attempting to develop heuristics, but may move to greedy algorithm for speed + results.
4. We started brainstorming and planning for "buckets" with probability.
5. We wrote some tests

### 5/1/2022
We continued making progress, and are nearly complete with the project:
1. We cleaned up our Word object, and replaced the adjacency map with a sorted adjacency list - this allowed us to optimally generate most/least common words in our backtracking algorithm.
2. We generated graphs of the most common words, through which we were able to visualize the power law at play.
3. We updated the prepreprocessing to eliminate stop words, which mitigaes the impact of the power law within words.
4. We added our buckets for the probabilistic algorithm and had discussions on where we want to generate random behavior.
