# coding: utf-8
# cython: wraparound=False

from util.generic.string cimport TString
from util.generic.vector cimport TVector

cdef extern from "xtok/libs/rawtoken.h" namespace "NTokenizer":
    cdef cppclass TRawToken:
        TString Data
        TString TokenType
        TVector[TString] GraphemTags

    cdef TVector[TRawToken] RawTokensFromText(const TString& text) nogil


def _tokenize(const TString& rawtext):
    tmpres = RawTokensFromText(rawtext)
    result = []
    for tmp in tmpres:
        tags = []
        for tag in tmp.GraphemTags:
            tags.append(tag)
        result.append({
            "data": tmp.Data,
            "type": tmp.TokenType,
            "info": tags
        })
    return result

