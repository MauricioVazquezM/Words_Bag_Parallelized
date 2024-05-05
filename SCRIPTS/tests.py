"""
SECTION A): LIBRARIES
"""
import pandas as pd
import numpy as np
import re
import nltk
import matplotlib.pyplot as plt
from sklearn.feature_extraction.text import CountVectorizer


"""
SECTION B): CODE EXECUTION
"""
# Defining etiquetas 
etiquetas = ["libro1", "libro2", "libro3", "libro4", "libro5", "libro6"]

# Declaring a list
corpus = []

# Loop for reading files
for etiqueta in etiquetas:

  # Opening files
  archivo = open(etiqueta + ".txt", "r")

  # reading the content and appending  to corpus list
  corpus.append(archivo.read())

  # Closing archive
  archivo.close()

# Printing message of job finished
print("Reading files done")

# Updating labels
etiquetas = ["dicke..", "sha...", "libro3", "libro4", "libro5", "libro6"]

# Converting Corpus to a NumPy Array
corpus = np.array(corpus)

# Creating data frame
df_corpus = pd.DataFrame({"documento": corpus, "categoria": etiquetas})

# Displaying the dataframe
print(df_corpus)

# Initializing CountVectorizer
count_vectorizer = CountVectorizer(min_df=0.0, max_df=1.0)

# Tranforming the corpus
matriz_conteo = count_vectorizer.fit_transform(corpus)

# Printing the transformed corpus
print(matriz_conteo)

# Printing the aprese matrix
print(matriz_conteo)

# Converting to Dense Matrix
matriz_conteo = matriz_conteo.toarray()

# Printing dense matrix
print(matriz_conteo)

# Extracting vocabulary
vocabulario = count_vectorizer.get_feature_names_out()

# Creating pandas dataframe
pd.DataFrame(matriz_conteo, columns=vocabulario)

# Printing vocabulary information
print(len(vocabulario), vocabulario)

# Saving vocabulary to a Text File
np.savetxt("vocab.txt", vocabulario, fmt="%s", delimiter=",")