# Longest cycles
This repository contains code and data related to the paper: "Improved asymptotic upper bounds for the minimum number of pairwise distinct longest cycles in regular graphs" (available on arXiv [here](https://arxiv.org/pdf/2310.17469.pdf)). People interested in the current repository might also be interested in [this repository](https://github.com/JorikJooken/hamiltonian_cycles) about counting hamiltonian cycles.

The files "18VertexGraph.g6", "24VertexGraph.g6" and "60VertexGraph.g6" each contain a graph that is described in that paper, represented in graph6 format.


### countLongestCycles.cpp
The program can be compiled by the following command:
```bash
g++ -g -std=c++11 -O3 countLongestCycles.cpp -o countLongestCyclesExecutable
```

The program reads a list of graphs in graph6 format and outputs each graph, followed by a line containing the number of pairwise distinct longest cycles. By default, hamiltonian graphs are skipped. This default setting can be overwritten by passing the parameter "0" to the executable.


Invoking the command

```bash
./countLongestCyclesExecutable < 24VertexGraph.g6
```

will result in the following output:

```
WY??WIG?G??B?ACO_A??D?AG?CWO??A?CC?A?_?]???E??@
4
```

This indicates that the graph is non-hamiltonian and has 4 pairwise distinct longest cycles.

Similarly, invoking the command

```bash
./countLongestCyclesExecutable < 60VertexGraph.g6
```

will result in the following output:

```
{HEHGDH?G?_@?P??_AG?HC?E?HG????????@???G???_??P???H????_??HG???@????C????G???AG????C????P????@G???_?_??O@H??????????????????W?????A_????????????A??????G??????G?????AG???_???G??????????G???@???????A??????CO_??????A????????D???????AG???????CW??????O????????A?C??????C?A???????_?W?????E?????????E??@
1
```

This indicates that this graph has a unique longest cycle.

The 18-vertex graph from the file "18VertexGraph.g6" is a hamiltonian graph. If we want to output the number of pairwise distinct hamiltonian cycles in this graph, we need to overwrite the default setting that hamiltonian graphs are skipped. This can be done by passing "0" as a parameter to the executable.

Invoking the command
```bash
./countLongestCyclesExecutable 0 < 18VertexGraph.g6
```

will result in the following output:

```
QhEHGDH?G?_@?P??_AG?HC?E?HG
1
```

This indicates that this graph has a unique hamiltonian cycle.

### enumerateLongestCycles.cpp
The program can be compiled by the following command:
```bash
g++ -g -std=c++11 -O3 enumerateLongestCycles.cpp -o enumerateLongestCyclesExecutable
```

This program works in a similar way as the previous program, but instead of counting the number of longest cycles, it will enumerate the longest cycles and write them to the output stream. Therefore, this program can expected to be a bit slower than the previous program.

Invoking the command
```bash
./enumerateLongestCyclesExecutable < 24VertexGraph.g6 
```

will result in the following output:

```
WY??WIG?G??B?ACO_A??D?AG?CWO??A?CC?A?_?]???E??@
24
001000001000000000000010
001100000000000000000010
110000000000000000000001
010000000000010000000001
000000101000000000100000
000000110000000000001000
000011000000000000000100
000001000000010000010000
100010000100000000000000
000000001001001000000000
000000000001100010000000
000000000110000001000000
000000000010010100000000
000100010000100000000000
000000000100000110000000
000000000000101001000000
000000000010001001000000
000000000001000110000000
000010000000000000011000
000000010000000000100100
000001000000000000100100
000000100000000000011000
110000000000000000000001
001100000000000000000010
4 18
6 4 8 9 11 17 15 14 16 10 12 13 7 5 20 18 19 21 
6 4 8 9 14 16 10 11 17 15 12 13 7 5 20 18 19 21 
8 4 18 20 5 6 21 19 7 13 12 10 16 14 15 17 11 9 
8 4 18 20 5 6 21 19 7 13 12 15 17 11 10 16 14 9
```

This indicates that this graph is a 24-vertex graph containing 4 longest cycles of length 18, indicated by the last 4 lines.


