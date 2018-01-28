LIBRARY()

PEERDIR(
    library/json
)

SRCS(
    enums.cpp
    token.cpp
    rawtoken.cpp
)

GENERATE_ENUM_SERIALIZATION(enums.h)

END()
