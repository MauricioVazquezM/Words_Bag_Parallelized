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

## Functions

### Function Read Vocabulary

- Designed to read words from a specified text file and store them in a vector. This function exemplifies basic file I/O operations, string manipulation, and vector handling in C++.

```cpp

```

### Function Count Words

- Designed to read multiple text files, count how often each word from a provided vocabulary appears in each file, and record these counts in a matrix for further analysis or reporting.

```cpp

```

### Function Write Matrix to a CSV

- Designed to export data stored in a matrix format into a CSV file. This is useful for saving structured data that can be easily viewed and analyzed in spreadsheet software or processed by other programs.

```cpp

```

### Function Calculate Average Time

- Designed to compute the average time taken for a series of operations (such as file processing or computation tasks) and report this time in seconds. It also logs this data to a CSV file, which can be used for further analysis or visualization (e.g., plotting execution times).

```cpp

```

### Function Read Files Names List

- Designed to read a list of filenames from a text file, where each filename is expected to be on a separate line. This function is particularly useful when you need to process multiple files dynamically, based on a list provided in a configuration file or a directory listing saved to a file. 

```cpp

```

### Main

- Executing program on main.

```cpp

```