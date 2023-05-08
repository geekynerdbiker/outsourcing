Python 3.7.6 (tags/v3.7.6:43364a7ae0, Dec 19 2019, 00:42:30) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> import random
import os

def is_valid_length(name: str) -> bool:
    if 1<=len(name)<=9:
        return True
    else:
        return False
    
def is_valid_start(name: str) -> bool:
    if name[0].isalpha():
        return True
    else:
        return False

def is_one_word(name: str) -> bool:
    if len(name.split(' '))==1:
        return True
    else:
        return False

def is_valid_name(name: str) -> bool:
    if (1<=len(name)<=9)==name[0].isalpha()==len(name.split(' '))==1:
        return True
    else:
        return False