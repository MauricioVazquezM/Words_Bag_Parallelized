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
void readVocabulary(const string& filename, vector<string>& vocabulary) {

    // Creating an input file stream object used to read data
    ifstream vocabStream(filename);

    // Declaring an string variable called line
    string line;

    // While-loop to read lines from a File
    while (getline(vocabStream, line)) {

        // Creating input string stream from line variable
        istringstream ss(line);

        // Declaring an string variable called word 
        string word;

        // While-loop to extract words
        while (getline(ss, word, ',')) {

            // Storing words in the vector
            vocabulary.push_back(word);

        }

    }

}
```

### Function Count Words

- Designed to read multiple text files, count how often each word from a provided vocabulary appears in each file, and record these counts in a matrix for further analysis or reporting.

```cpp
void countWords(const vector<string>& files, const vector<string>& vocabulary, vector<vector<string>>& matriz) {

    // For-loop to iterate over all files names vector 
    for (int i = 0; i < files.size(); i++) {

        // Declaring a dictionary that will hold the word counts
        map<string, int> dictionary;

        // For-loop that initializes the dictionary of each word count to zero
        for (const string& word : vocabulary) {

            // Setting each word count to zero
            dictionary[word] = 0;

        }

        // Opening a file used to read data from the file
        ifstream fileStream(files[i]);

        // Declaring a string auxiliar variable to read
        string line;

        // While-loop that iterates over each line from the file
        while (getline(fileStream, line)) {

            // Initializing an string stream with the content of line
            istringstream ss(line);

            // Declaring a string auxiliar variable for word
            string word;

            // While-loop to read characters until a comma is encountered
            while (getline(ss, word, ',')) {

                // Checking if the word extracted from the line is found
                if (dictionary.find(word) != dictionary.end()) {

                    // If the word is found in the dictonary, increment its associaed
                    dictionary[word]++;

                }

            }

        }

        // For-loop to iterate over each element in the vocabulary vector
        for (int j = 0; j < vocabulary.size(); j++) {

            // Storing the counts in the matrix  
            matriz[1+i][j] = to_string(dictionary[vocabulary[j]]);

        }

    }

}
```

### Function Write Matrix to a CSV

- Designed to export data stored in a matrix format into a CSV file. This is useful for saving structured data that can be easily viewed and analyzed in spreadsheet software or processed by other programs.

```cpp
void writeMatrixToCSV(const std::string& filename, std::vector<std::vector<std::string>> matriz, int rows, int cols) {

    // Opening an output file stream for writing the CSV file
    std::ofstream csvFile(filename);

    // Checking if the file stream was successfully opened
    if (!csvFile.is_open()) {

        // Printing error message and closing
        std::cerr << "Failed to open file: " << filename << std::endl;

        // Exiting
        return;

    }

    // For-Loop to use through each row of the matrix
    for (int i = 0; i < rows; i++) {

        // For-Loop to use through each column of the matrix
        for (int j = 0; j < cols; j++) {

            // Writing the current element to the file
            csvFile << matriz[i][j];

            // Adding a comma unless it's the last element in the row
            if (j != cols - 1) {

                // Adding comma
                csvFile << ",";
                
            }

        }

        // End the current row
        csvFile << std::endl;

    }

    // Closing the file stream
    csvFile.close();

}
```

### Function Calculate Average Time

- Designed to compute the average time taken for a series of operations (such as file processing or computation tasks) and report this time in seconds. It also logs this data to a CSV file, which can be used for further analysis or visualization (e.g., plotting execution times).

```cpp
void calculateAverageTime(double total_time, int ejecuciones) {

    // Calculating average time
    double avg_time = (total_time / ejecuciones) / 1000;

    // Displaying the average time on console
    cout << "Promedio de tiempo de ejecucion: " << avg_time << " segundos" << endl;

    // Writing the average time on a CSV for plotting purposes
    ofstream csv_file("tiempo_serial.csv");

    // Checking that the file stream is open
    if (csv_file.is_open()){

        // Writing on the file
        csv_file << avg_time;

        // Closing the file stream
        csv_file.close();

    }

}
```

### Function Read Files Names List

- Designed to read a list of filenames from a text file, where each filename is expected to be on a separate line. This function is particularly useful when you need to process multiple files dynamically, based on a list provided in a configuration file or a directory listing saved to a file. 

```cpp
std::vector<std::string> readFileNames(const std::string& filename) {

    // Initializing variable lines
    std::vector<std::string> lines;

    // Opening the files names
    std::ifstream fileStream(filename);

    // Check if the file is open
    if (!fileStream.is_open()) {

        // Printing  opening error
        std::cerr << "Failed to open file: " << filename << std::endl;

        // Return an empty vector if file cannot be opened
        return lines; 

    }

    // Initializing string auxiliar variable
    std::string line;

    // Read file line by line
    while (getline(fileStream, line)) {

        // Appending on the vector
        lines.push_back(line);

    }

    // Close the file after reading
    fileStream.close();

    // Returning vector
    return lines;

}
```

### Main

- Executing program on main.

```cpp

```
