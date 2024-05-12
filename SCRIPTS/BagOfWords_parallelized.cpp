/*
    SECTION A): LIBRARIES
*/
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iterator>
#include <cctype>
#include <mpi.h>

using namespace std;

/* 
    SECTION B) FUNCTIONS
*/

/*
    FUNCTION: Read Vocabulary
*/
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

/*
    FUNCTION: Count words
*/
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

/*
    FUNCTION: Write Matrix to a CSV
*/
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

/*
    FUNCTION: Calculate average time
*/
void calculateAverageTime(double total_time, int ejecuciones) {

    // Calculating average time
    double avg_time = (total_time / ejecuciones) / 1000;

    // Displaying the average time on console
    cout << "Promedio de tiempo de ejecucion: " << avg_time << " segundos" << endl;

    // Writing the average time on a CSV for plotting purposes
    ofstream csv_file("tiempo_paralelo.csv");

    // Checking that the file stream is open
    if (csv_file.is_open()){

        // Writing on the file
        csv_file << avg_time;

        // Closing the file stream
        csv_file.close();

    }

}

/*
    FUNCTION: Read files names list function
*/
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


/* 
    SECTION C) MAIN
*/

int main(int argc, char *argv[]) {

    // Initializing MPI
    MPI_Init(&argc, &argv);

    // Initializing the total number of processes and each process_id
    int num_processes = 6;
    int process_id;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    // Checking if the necessary arguments are passed
    if (argc < 5) {

        if (process_id == 0) {

            cerr << "Usage: " << argv[0] << " <listado_nombres_archivos.txt> <archivo_vocabulario.txt> <tamanio_vocabulario> <output_file.csv>\n";
        }

        // If the arguments are incomplete, MPI is finalized so no processes are left running
        MPI_Finalize();
        
        return 1;
    }

    // Getting command line arguments
    const string files_names = argv[1];
    const string arch_vocabulario = argv[2];
    const int tamanio_voc = atoi(argv[3]);
    const string output_file_name = argv[4];

    // Number of iterations for counting
    const int ejecuciones = 10;
    double total_time = 0.0;

    vector<string> vocabulary;
    vector<string> files;

    // Master reads the vocabulary and the file names
    if (process_id == 0) {
        readVocabulary(arch_vocabulario, vocabulary);
        files = readFileNames(files_names);
    }

    int vocab_size = vocabulary.size();

    // Broadcasting the size of the vocabulary to all processes
    MPI_Bcast(&vocab_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_id != 0) {

        // All processes resize the vocabulary vector to match the size
        vocabulary.resize(vocab_size);

    }

    // For loop to broadcast vocabulary words
    for (int i = 0; i < vocab_size; i++) {
        int len;

        if (process_id == 0) {
            len = vocabulary[i].length();
        }

        // Broadcasting the word length as well
        MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (process_id != 0) {
            vocabulary[i].resize(len);
        }

        // Broadcasting a word from the vocabulary
        MPI_Bcast(const_cast<char *>(vocabulary[i].data()), len, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    // Here the word counts are stored: 7 rows for 7 books,
    // columns contain the word and the count of how many times it appears
    vector<vector<string>> matriz(7, vector<string>(tamanio_voc));

    if (process_id == 0) {
        // copying the vocabulary
        copy(vocabulary.begin(), vocabulary.end(), matriz[0].begin());
    }

    // MPI_Gather to collect the counted words from each process
    vector<vector<string>> all(matriz);
    MPI_Gather(matriz.data() + 1, 6, MPI_DOUBLE, all.data() + 1, 6, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Writing the matrix to a .csv
    if (process_id == 0) {
        writeMatrixToCSV(output_file_name, all, 7, tamanio_voc);
    }

    double start_time;
    double end_time;

    // Calculating the execution time for each iteration
    for (int i = 0; i < ejecuciones; i++) {

        // Start
        start_time = MPI_Wtime();

        countWords(files, vocabulary, matriz);

        // End
        end_time = MPI_Wtime();

        double iteration_time = end_time - start_time;
        double total_iteration_time = 0.0;

        // Displaying the time execution
        cout << "Tiempo de ejecucion: "<< iteration_time/1000 << " segundos \n";

        // Using the reduce operation, we get the total time of all iterations.
        MPI_Reduce(&iteration_time, &total_iteration_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        
        if (process_id == 0) {
            total_time += total_iteration_time;
        }

    }

    // Calculating the avarge time 
    calculateAverageTime(total_time, ejecuciones);

    MPI_Finalize();
    return 0;
}
