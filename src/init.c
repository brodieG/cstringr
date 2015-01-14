#include "cstringr.h"
#include <R_ext/Rdynload.h>

static const
R_CallMethodDef callMethods[] = {
  {"len_chr_len_ext", (DL_FUNC) &CSR_len_chr_len_ext, 1},
  {"len_as_chr_ext", (DL_FUNC) &CSR_len_as_chr_ext, 1},
  {"strmlen_ext", (DL_FUNC) &CSR_strmlen_ext, 2},
  {"strmtrunc_ext", (DL_FUNC) &CSR_strmtrunc_ext, 2},
  {"smprintf2_ext", (DL_FUNC) &CSR_smprintf2_ext, 4},
  {"ucfirst_ext", (DL_FUNC) &CSR_ucfirst_ext, 2},
  {"lcfirst_ext", (DL_FUNC) &CSR_lcfirst_ext, 2},
  {NULL, NULL, 0}
};

void R_init_cstringr(DllInfo *info)
{
 /* Register the .C and .Call routines.
    No .Fortran() or .External() routines,
    so pass those arrays as NULL.
  */
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);
  R_RegisterCCallable("cstringr", "CSR_len_chr_len", (DL_FUNC) CSR_len_chr_len);
  R_RegisterCCallable("cstringr", "CSR_len_as_chr", (DL_FUNC) CSR_len_as_chr);
  R_RegisterCCallable("cstringr", "CSR_strmlen", (DL_FUNC) CSR_strmlen);
  R_RegisterCCallable("cstringr", "CSR_strmtrunc", (DL_FUNC) CSR_strmtrunc);
  R_RegisterCCallable("cstringr", "CSR_smprintf6", (DL_FUNC) CSR_smprintf6);
  R_RegisterCCallable("cstringr", "CSR_smprintf5", (DL_FUNC) CSR_smprintf5);
  R_RegisterCCallable("cstringr", "CSR_smprintf4", (DL_FUNC) CSR_smprintf4);
  R_RegisterCCallable("cstringr", "CSR_smprintf3", (DL_FUNC) CSR_smprintf3);
  R_RegisterCCallable("cstringr", "CSR_smprintf2", (DL_FUNC) CSR_smprintf2);
  R_RegisterCCallable("cstringr", "CSR_smprintf1", (DL_FUNC) CSR_smprintf1);
}
