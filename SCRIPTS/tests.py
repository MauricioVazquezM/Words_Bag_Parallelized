"""
SECTION A): LIBRARIES
"""
import pandas as pd
import numpy as np
import re
import nltk
import matplotlib.pyplot as plt

"""
SECTION B): AUXILIAR FUNCTIONS
"""

etiquetas = ["libro1",
             "libro2",
             "libro3",
             "libro4",
             "libro5",
             "libro6"]
corpus = []

for etiqueta in etiquetas:
  archivo = open(etiqueta + ".txt", "r")
  corpus.append(archivo.read())
  archivo.close()

etiquetas = ["dicke..",
             "sha...",
             "libro3",
             "libro4",
             "libro5",
             "libro6"]

corpus = np.array(corpus)
df_corpus = pd.DataFrame({"documento": corpus,
                          "categoria": etiquetas})
df_corpus


"""
SECTION C): CODE EXECUTION
"""

from sklearn.feature_extraction.text import CountVectorizer
# bolsa de palabras en matriz dispersa
count_vectorizer = CountVectorizer(min_df=0.0, max_df=1.0)
matriz_conteo = count_vectorizer.fit_transform(corpus)
matriz_conteo

# ver valores diferentes de cero en la matriz dispersa
print(matriz_conteo)

# ver la representación densa
matriz_conteo = matriz_conteo.toarray()
matriz_conteo


# obten todas las palabras únicas del corpus
vocabulario = count_vectorizer.get_feature_names_out()
# muestra los vectores de características del documento
pd.DataFrame(matriz_conteo, columns=vocabulario)

print(len(vocabulario), vocabulario)

np.savetxt("vocab.txt", vocabulario, fmt="%s", delimiter=",")