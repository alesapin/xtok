# coding: utf-8
from ._tokenizer import _tokenize

def tokenize(text):
    if isinstance(text, bytes):
       result = _tokenize(text)
    elif isinstance(text, str):
        result = _tokenize(text.encode('utf-8'))

    for elem in result:
        elem['data'] = elem['data'].decode('utf-8')

    return result




