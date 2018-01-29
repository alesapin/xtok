PYMODULE(_xtok)

PEERDIR(
    xtok/libs
)

BUILDWITH_CYTHON_CPP(
    _xtok.pyx
    --module-name _xtok
)

END()
