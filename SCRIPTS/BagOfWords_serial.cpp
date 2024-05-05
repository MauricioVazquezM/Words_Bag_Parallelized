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
    for (int i = 0; i < files.size(); i++) {
        map<string, int> dictionary;
        for (const string& word : vocabulary) {
            dictionary[word] = 0;
        }
        ifstream fileStream(files[i]);
        string line;
        while (getline(fileStream, line)) {
            istringstream ss(line);
            string word;
            while (getline(ss, word, ',')) {
                if (dictionary.find(word) != dictionary.end()) {
                    dictionary[word]++;
                }
            }
        }
        for (int j = 0; j < vocabulary.size(); j++) {
            matriz[1+i][j] = to_string(dictionary[vocabulary[j]]);
        }
    }
}

/*
    FUNCTION: Write Matrix to a CSV
*/
void writeMatrixToCSV(const std::string& filename, int** matriz, int rows, int cols) {

    // Opening an output file stream for writing the CSV file
    std::ofstream csvFile(filename);

    // Checking if the file stream was successfully opened
    if (!csvFile.is_open()) {

        // Printing error message and closing
        std::cerr << "Failed to open file: " << filename << std::endl;
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
    ofstream csv_file("data/tiempo_serial.csv");

    // Checking that the file stream is open
    if (csv_file.is_open()){

        // Writing on the file
        csv_file << avg_time;

        // Closing the file stream
        csv_file.close();

    }
    
}


/* 
    SECTION B) MAIN
*/

int main(int argc, char *argv[]) {
    const int ejecuciones = 10;
    double total_time = 0.0;

    vector<string> vocabulary;
    readVocabulary("data/palabras.csv", vocabulary);
    if (vocabulary.empty()) {
        cerr << "El archivo de palabras está vacío" << endl;
        return 1;
    }
    int tamanio = vocabulary.size();
    vector<vector<string>> matriz(7, vector<string>(tamanio));
    copy(vocabulary.begin(), vocabulary.end(), matriz[0].begin());

    vector<string> files = {
        "data/libro1.csv", "data/libro2.csv", "data/libro3.csv",
        "data/libro4.csv", "data/libro5.csv", "data/libro6.csv"
    };

    for (int i = 0; i < ejecuciones; i++) {
        auto start_time = chrono::high_resolution_clock::now();
        countWords(files, vocabulary, matriz);
        writeMatrixToCSV("data/resultados_serial.csv", matriz, tamanio);
        auto end_time = chrono::high_resolution_clock::now();
        double iteration_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
        total_time += iteration_time;
    }

    calculateAverageTime(total_time, ejecuciones);
    return 0;
}