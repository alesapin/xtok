PROGRAM()

SRCS(
    enums.cpp
    token.cpp
    main.cpp
)

GENERATE_ENUM_SERIALIZATION(enums.h)

END()
