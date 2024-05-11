# Documentation


## Libraries

- ***map***: used for storing and retrieving data based on keys. Useful for associative arrays where you want to quickly look up data based on a key.
- ***string***: used for all operations involving standard strings, like concatenation, searching, reading, and modifying text.
- ***iostream***: used for all input and output operations. For example, reading from the keyboard and writing to the console.
- ***fstream***: used to read from and write to files stored on disk.
- ***sstream***: used for parsing data from strings or assembling strings from multiple pieces of data.
- ***vector***: used whenever an array-like structure is needed that can change in size during runtime.
- ***algorithm***: used for common operations like sorting and searching containers.
- ***mpi.h***: interface for MPI (Message Passing Interface), which supports parallel programming in C++. This header provides functions for communicating data between processes in a distributed computing environment.
- ***iterator***: used to navigate through container classes (like vectors, lists, and maps) and to read or modify their elements.
- ***cctype***: used for character handling and manipulation, useful in parsing and text processing.
- ***chrono***: used for measuring time intervals in applications, timing operations, and building time-dependent functionalities.

```cpp
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <mpi.h>
#include <iterator>
#include <cctype>
#include <chrono>
using namespace std;
```