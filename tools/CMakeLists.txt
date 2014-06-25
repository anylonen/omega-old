set(CRYPT_SOURCES
    crypt.c
    bwt.c)

set(DECRYPT_SOURCES
    decrypt.c)

set(MAKEDATE_SOURCES
    makedate.c)

add_executable(crypt ${CRYPT_SOURCES})
add_executable(decrypt ${DECRYPT_SOURCES})
add_executable(makedate ${MAKEDATE_SOURCES})

