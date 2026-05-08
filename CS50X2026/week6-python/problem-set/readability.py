import re
from cs50 import get_string


def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha(): 
            count += 1
    return count

def count_words(text):
    return len(text.split())

def count_sentences(text):
    count = 0
    for char in text:
        pattern = "[.!?]"
        result = re.match(pattern, char)
        if result:
            count += 1
    return count

def calculate_index(numberOfLetters, numberOfWords, numberOfSentences):
    L = float( numberOfLetters / numberOfWords ) * 100.0
    S = float (numberOfSentences / numberOfWords ) * 100.0

    colemanLiauIndex = 0.0588 * L - 0.296 * S - 15.8

    return int(round(colemanLiauIndex))

def print_grade(index):
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

text = get_string("Text: ")

numberOfLetters = count_letters(text)
numberOfWords = count_words(text)
numberOfSentences = count_sentences(text)

index = calculate_index(numberOfLetters, numberOfWords, numberOfSentences)
print_grade(index)
