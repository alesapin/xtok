PY_LIBRARY()
SRCDIR(xtok/python-package/xtok)

PEERDIR(
    xtok/libs
)

PY_SRCS(
    NAMESPACE xtok
    __init__.py
    wrapper.py
    _xtok.pyx
)

END()
