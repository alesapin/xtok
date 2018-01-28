UNITTEST()

PEERDIR(
    library/json
)

SRCS(
    ../token.cpp
    tokenizer_ut.cpp
)

GENERATE_ENUM_SERIALIZATION(../enums.h)

END()
