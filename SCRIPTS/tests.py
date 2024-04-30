"""
SECTION A): LIBRARIES
"""

import pandas as pd
from nltk.corpus import stopwords
import unicodedata
from collections import Counter
import re
import nltk
nltk.download('stopwords')


"""
SECTION B): AUXILIAR FUNCTIONS
"""

### Reading function
def read_and_clean(file_name):
   
   # Get English stop words
    stop_words = set(stopwords.words('english'))
   
   # opening the file
    with open(file_name, 'r', encoding='utf-8') as file:

    # Reading the whole file and split by comas
        contents = file.read().lower().replace('\n', '').split(',')
    
    # Filtering out stop words
    words_filtered = [word for word in contents if word not in stop_words]

    # Returning words
    return words_filtered


### Counting words function
def count_words(file_name):
  
  # Using our read function implemented above
  text = read_and_clean(file_name)

  # Counting each word
  word_count = Counter(text)

  # Storing on a dataframe
  df = pd.DataFrame(word_count.items(), columns=['Word', 'Count'])

  # Returning count dataframe
  return df


"""
SECTION C): CODE EXECUTION
"""


