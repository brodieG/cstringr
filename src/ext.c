#include "cstringr.h"

/*
External interface to internal string functions, mostly for testing, note these
aren't very careful about potential overflows from input so user should ensure
inputs don't overflow int
*/

void is_scalar_pos_int(SEXP obj) {
  if(TYPEOF(obj) != INTSXP || XLENGTH(obj) != 1L || asInteger(obj) < 0)
    error("Argument `size` must be a positive scalar integer");
}
void is_scalar_chr(SEXP obj) {
  if(TYPEOF(obj) != STRSXP || XLENGTH(obj) != 1L)
    error("Argument `size` must be a positive scalar integer");
}
SEXP CSR_set_max_strlen_ext(SEXP size) {
  is_scalar_pos_int(size);
  CSR_set_max_strlen((R_xlen_t) asInteger(size));
  return size;
}
SEXP CSR_len_chr_len_ext(SEXP a) {
  is_scalar_pos_int(a);
  return ScalarInteger(CSR_len_chr_len((R_xlen_t) asInteger(a)));
}
SEXP CSR_len_as_chr_ext(SEXP a) {
  is_scalar_pos_int(a);
  return mkString(CSR_len_as_chr((R_xlen_t) asInteger(a)));
}
SEXP CSR_strlen_ext(SEXP str) {
  is_scalar_chr(str);
  return(ScalarInteger(CSR_strlen(CHAR(asChar(str)))));
}
SEXP CSR_strtrunc_ext(SEXP str) {
  is_scalar_chr(str);
  return(mkString(CSR_strtrunc(CHAR(asChar(str)))));
}
SEXP CSR_sprintf2_ext(SEXP base, SEXP a, SEXP b) {
  is_scalar_chr(base);
  is_scalar_chr(a);
  is_scalar_chr(b);
  return(mkString(CSR_sprintf2(CHAR(asChar(base)), CHAR(asChar(a)), CHAR(asChar(b)))));
}
