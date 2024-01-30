from cs50 import get_string
import re


text = get_string("Text: ")

letras = 0
palavras = 1
frases = 0

for i in text:
    if i.isalpha():
        letras += 1
    elif i == " ":
        palavras += 1
    elif i in ["!", "?", "."]:
        frases += 1


grade = 0.0588 * (letras/palavras*100) - 0.296 * (frases/palavras*100) - 15.8

if grade < 1:
    print('Before Grade 1')

elif grade >= 16:
    print('Grade 16+')

else:
    print(f"Grade {round(grade)}")
