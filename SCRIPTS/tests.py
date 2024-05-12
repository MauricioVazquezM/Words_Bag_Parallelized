"""
SECTION A): LIBRARIES
"""
import pandas as pd
import numpy as np
import re
from nltk import stopwords
import matplotlib.pyplot as plt
from sklearn.feature_extraction.text import CountVectorizer


"""
SECTION B): CODE EXECUTION
"""

# Download the stopwords dataset from NLTK if not already done
nltk.download('stopwords')

# Loop for reading files and removing stopwords
stop_words = set(stopwords.words('english'))

# Defining etiquetas 
etiquetas = ["libro1", "libro2", "libro3", "libro4", "libro5", "libro6"]

# Declaring a list
corpus = []

# Loop for reading files
for etiqueta in etiquetas:

  # Opening files
  archivo = open("../DATA/" + etiqueta + ".txt", "r")

  # Reading book content
  content = archivo.read()

  # reading the content and appending  to corpus list
  corpus.append(content)

  # Closing archive
  archivo.close()

# Printing message of job finished
print("Reading files done")

# Updating labels
# etiquetas = ["dicke..", "sha...", "libro3", "libro4", "libro5", "libro6"]

# Converting Corpus to a NumPy Array
corpus = np.array(corpus)

# Creating data frame
df_corpus = pd.DataFrame({"documento": corpus, "categoria": etiquetas})

# Displaying the dataframe
print(df_corpus)

# Initializing CountVectorizer
count_vectorizer = CountVectorizer(min_df=0.0, max_df=1.0, stop_words='english')

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
np.savetxt("../DATA/vocab.txt", vocabulario, fmt="%s", delimiter=",")