PYMODULE(_tokenizer)

PEERDIR(
    tokenizer/libs
)

BUILDWITH_CYTHON_CPP(
    _tokenizer.pyx
    --module-name _tokenizer
)

END()
