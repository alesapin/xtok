LIBRARY()

LICENSE(
    PD
)



NO_COMPILER_WARNINGS()

ENABLE(SQLITE_OS_YANDEX)

IF (SQLITE_OS_YANDEX)
    CFLAGS(-DSQLITE_OS_YANDEX)
ELSE()
    IF (OS_WINDOWS)
        CFLAGS(-DSQLITE_OS_WIN)
    ELSE()
        CFLAGS(-DSQLITE_OS_UNIX)
    ENDIF()
ENDIF()

CFLAGS(-DSQLITE_THREADSAFE)
CFLAGS(-DSQLITE_SYSTEM_MALLOC)
CFLAGS(-DHAVE_USLEEP)

CFLAGS(-DSQLITE_INT64_TYPE=i64)
CFLAGS(-DSQLITE_UINT64_TYPE=ui64)
CFLAGS(-DUINT32_TYPE=ui32)
CFLAGS(-DUINT16_TYPE=ui16)
CFLAGS(-DINT16_TYPE=i16)
CFLAGS(-DUINT8_TYPE=ui8)
CFLAGS(-DINT8_TYPE=i8)

SRCS(
    sqlite3.c
)

IF (SQLITE_OS_YANDEX)
    SRCS(
        os_yandex.cpp
        mutex_yandex.cpp
    )
ENDIF()

END()