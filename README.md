# csci163b_algorithms2
Coding assignments for Advanced Theory of Algorithms

All of the graphs that are read from the program are in the following format:
The first line contains two numbers-- the number of verticies, the number of edges.
The second line contains the name of each vertex (usually numbers for simplicity, but flexible to support longer strings)
Then each following line contains two vertecies that share an edge

each file looks like:

number_of_verticies number_of_edges /n
vertex_1 vertex_2 ..... vertex_m /n
vertex1_in_edge_1 vertex2_in_edge_1 /n
...
vertex1_in_edge_n vertex2_in_edge_n /n


so the file containing:

3 2 /n
a b c /n
a b /n
a c /n
b c /n

looks like a triangle with verticies a, b, and c.


Digraphs are input the same way, with directed edge going from the first listed vertex to the second listed one

Weighted graphs keep everything the same except they have another numerical value after each edge list that corresponds to the weight of the edge
So the previous example would look like 

3 2 /
a b c /
a b 3 / 
a c 5 /
b c 2 /

Where the graph would look the same but edge ab would have a weight of 3, etc.
