#include <R.h>
#include <Rinternals.h>

// Testing Functions

SEXP CSR_set_max_strlen_ext(SEXP size);
SEXP CSR_len_chr_len_ext(SEXP a);
SEXP CSR_len_as_chr_ext(SEXP a);
SEXP CSR_strlen_ext(SEXP str);
SEXP CSR_strtrunc_ext(SEXP str);
SEXP CSR_sprintf2_ext(SEXP base, SEXP a, SEXP b);

// Internal Functions

void CSR_set_max_strlen(size_t size);
size_t CSR_len_chr_len(R_xlen_t a);
const char * CSR_len_as_chr(R_xlen_t a);
size_t CSR_strlen(const char * str);
const char * CSR_strtrunc(const char * str);
const char * CSR_sprintf2(const char * base, const char * a, const char * b);
