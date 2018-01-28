PY_LIBRARY()
SRCDIR(tokenizer/python-package/tokenizer)

PEERDIR(
    tokenizer/libs
)

PY_SRCS(
    NAMESPACE tokenizer
    __init__.py
    _tokenizer.pyx
)

END()
