# Words_Bag_Parallelized

<p align="center">
  <img width="800" height="500" src="https://hoctructuyen123.net/wp-content/uploads/2019/07/Untitled.png">
</p>

## Team

- [Mariana Luna Rocha](https://github.com/MarianaMoons), Data Science Bachelor student at ITAM.
- [Mauricio Vázquez Moran](https://github.com/MauricioVazquezM), Data Science and Actuarial Science Double Bachelor Program student at ITAM.
  
</br>

## Problem Definition

Given a list of filenames containing texts, a filename containing the vocabulary and its size, and the number of processes to be used (equal to the number of input files), the task is to implement a bag-of-words algorithm. The algorithm counts the occurrences of words in the texts and produces an output file with a Bag of Words matrix in CSV format.

 - Input:
    - List of filenames where the texts to be analyzed are located (files are in the same location as the executable).
    - Filename containing the vocabulary and its size.
    - Number of processes to be used (equal to the number of input files).
- Output:
    - file containing the Bag of Words matrix in CSV format.

</br>

## Algorithm Overview

1. Read the vocabulary file to create a dictionary where the keys are words, and the values are indices.
2. Initialize a Bag of Words matrix with rows for each text file and columns for each word in the vocabulary.
3. Assign a process to each text file to count the occurrences of words in parallel.
  - For each text file:
    - Read the text file.
    - Tokenize the text into words.
    - Count the occurrences of each word in the vocabulary.
    - Update the corresponding row in the Bag of Words matrix.
4. Write the Bag of Words matrix to a CSV file.
