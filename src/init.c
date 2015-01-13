#include "cstringr.h"
#include <R_ext/Rdynload.h>

// Testing Functions

SEXP CSR_set_max_strlen_ext(SEXP size);
SEXP CSR_len_chr_len_ext(SEXP a);
SEXP CSR_len_as_chr_ext(SEXP a);
SEXP CSR_strlen_ext(SEXP str);
SEXP CSR_strtrunc_ext(SEXP str);
SEXP CSR_sprintf2_ext(SEXP base, SEXP a, SEXP b);

// C versions

void CSR_set_max_strlen(size_t len);
size_t CSR_len_chr_len(R_xlen_t a);
const char * CSR_len_as_chr(R_xlen_t a);
size_t CSR_strlen(const char * str);
const char * CSR_strtrunc(const char * str);
static size_t add_szt(size_t a, size_t b);
const char * CSR_sprintf6(
  const char * base, const char * a, const char * b, const char * c,
  const char * d, const char * e, const char * f
);
const char * CSR_sprintf5(
  const char * base, const char * a, const char * b, const char * c,
  const char * d, const char * e
);
const char * CSR_sprintf4(
  const char * base, const char * a, const char * b, const char * c,
  const char * d
);
const char * CSR_sprintf3(
  const char * base, const char * a, const char * b, const char * c
);
const char * CSR_sprintf2(const char * base, const char * a, const char * b);
const char * CSR_sprintf1(const char * base, const char * a);

static const
R_CallMethodDef callMethods[] = {
  {"set_max_strlen", (DL_FUNC) &CSR_set_max_strlen_ext, 1},
  {"len_chr_len_ext", (DL_FUNC) &CSR_len_chr_len_ext, 1},
  {"len_as_chr_ext", (DL_FUNC) &CSR_len_as_chr_ext, 1},
  {"strlen_ext", (DL_FUNC) &CSR_strlen_ext, 1},
  {"rstrtrunc_ext", (DL_FUNC) &CSR_strtrunc_ext, 1},
  {"CSR_sprintf2_ext", (DL_FUNC) &CSR_sprintf2_ext, 3},
  {NULL, NULL, 0}
};

void R_init_cstringr(DllInfo *info)
{
 /* Register the .C and .Call routines.
    No .Fortran() or .External() routines,
    so pass those arrays as NULL.
  */
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);
  R_RegisterCCallable("cstringr", "CSR_set_max_strlen", (DL_FUNC) CSR_set_max_strlen);
  R_RegisterCCallable("cstringr", "CSR_len_chr_len", (DL_FUNC) CSR_len_chr_len);
  R_RegisterCCallable("cstringr", "CSR_len_as_chr", (DL_FUNC) CSR_len_as_chr);
  R_RegisterCCallable("cstringr", "CSR_strlen", (DL_FUNC) CSR_strlen);
  R_RegisterCCallable("cstringr", "CSR_strtrunc", (DL_FUNC) CSR_strtrunc);
  R_RegisterCCallable("cstringr", "CSR_sprintf5", (DL_FUNC) CSR_sprintf5);
  R_RegisterCCallable("cstringr", "CSR_sprintf4", (DL_FUNC) CSR_sprintf4);
  R_RegisterCCallable("cstringr", "CSR_sprintf3", (DL_FUNC) CSR_sprintf3);
  R_RegisterCCallable("cstringr", "CSR_sprintf2", (DL_FUNC) CSR_sprintf2);
  R_RegisterCCallable("cstringr", "CSR_sprintf1", (DL_FUNC) CSR_sprintf1);
}
