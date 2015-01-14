#include "cstringr.h"

/*
External interface to internal string functions, mostly for testing, note these
aren't very careful about potential overflows from input so user should ensure
inputs don't overflow int
*/

void is_scalar_pos_int(SEXP obj) {
  if(TYPEOF(obj) != INTSXP || XLENGTH(obj) != 1L || asInteger(obj) < 0)
    error("Argument `maxlen` must be a positive scalar integer");
}
void is_scalar_chr(SEXP obj) {
  if(TYPEOF(obj) != STRSXP || XLENGTH(obj) != 1L)
    error("Argument `str` must be a scalar character");
}
SEXP CSR_len_chr_len_ext(SEXP a) {
  is_scalar_pos_int(a);
  return ScalarInteger(CSR_len_chr_len((R_xlen_t) asInteger(a)));
}
SEXP CSR_len_as_chr_ext(SEXP a) {
  is_scalar_pos_int(a);
  return mkString(CSR_len_as_chr((R_xlen_t) asInteger(a)));
}
SEXP CSR_strmlen_ext(SEXP str, SEXP maxlen) {
  is_scalar_chr(str);
  is_scalar_pos_int(maxlen);
  return(ScalarInteger(CSR_strmlen(CHAR(asChar(str)), asInteger(maxlen))));
}
SEXP CSR_strmcpy_ext(SEXP str, SEXP maxlen) {
  is_scalar_chr(str);
  is_scalar_pos_int(maxlen);
  return(mkString(CSR_strmcpy(CHAR(asChar(str)), asInteger(maxlen))));
}
SEXP CSR_smprintf2_ext(SEXP maxlen, SEXP format, SEXP a, SEXP b) {
  is_scalar_chr(format);
  is_scalar_chr(a);
  is_scalar_chr(b);
  is_scalar_pos_int(maxlen);
  char * res = CSR_smprintf2(
    asInteger(maxlen), CHAR(asChar(format)), CHAR(asChar(a)), CHAR(asChar(b))
  );
  return mkString(res);
}
SEXP CSR_ucfirst_ext(SEXP str, SEXP maxlen) {
  is_scalar_chr(str);
  is_scalar_pos_int(maxlen);
  return(mkString(CSR_ucfirst(CHAR(asChar(str)), asInteger(maxlen))));
}
SEXP CSR_lcfirst_ext(SEXP str, SEXP maxlen) {
  is_scalar_chr(str);
  is_scalar_pos_int(maxlen);
  return(mkString(CSR_lcfirst(CHAR(asChar(str)), asInteger(maxlen))));
}
