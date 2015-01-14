#include <R.h>
#include <Rinternals.h>
#include <ctype.h>

// Testing Functions

SEXP CSR_len_chr_len_ext(SEXP a);
SEXP CSR_len_as_chr_ext(SEXP a);
SEXP CSR_strmlen_ext(SEXP str, SEXP maxlen);
SEXP CSR_strmcpy_ext(SEXP str, SEXP maxlen);
SEXP CSR_smprintf2_ext(SEXP maxlen, SEXP format, SEXP a, SEXP b);
SEXP CSR_ucfirst_ext(SEXP str, SEXP maxlen);
SEXP CSR_lcfirst_ext(SEXP str, SEXP maxlen);

// Internal Functions

size_t CSR_len_chr_len(R_xlen_t a);
char * CSR_len_as_chr(R_xlen_t a);
size_t CSR_strmlen(const char * str, size_t maxlen);
char * CSR_strmcpy(const char * str, size_t maxlen);
char * CSR_smprintf6(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d, const char * e, const char * f
);
char * CSR_smprintf5(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d, const char * e
);
char * CSR_smprintf4(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d
);
char * CSR_smprintf3(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c
);
char * CSR_smprintf2(
  size_t maxlen, const char * format, const char * a, const char * b
);
char * CSR_smprintf1(size_t maxlen, const char * format, const char * a);

char * CSR_ucfirst(const char * str, size_t maxlen);
char * CSR_lcfirst(const char * str, size_t maxlen);
