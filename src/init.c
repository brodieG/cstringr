#include "cstringr.h"
#include <R_ext/Rdynload.h>

static const
R_CallMethodDef callMethods[] = {
  {"len_chr_len_ext", (DL_FUNC) &CSR_len_chr_len_ext, 1},
  {"len_as_chr_ext", (DL_FUNC) &CSR_len_as_chr_ext, 1},
  {"strmlen_ext", (DL_FUNC) &CSR_strmlen_ext, 2},
  {"strmcpy_ext", (DL_FUNC) &CSR_strmcpy_ext, 2},
  {"collapse_ext", (DL_FUNC) &CSR_collapse_ext, 3},
  {"bullet_ext", (DL_FUNC) &CSR_bullet_ext, 4},
  {"smprintf2_ext", (DL_FUNC) &CSR_smprintf2_ext, 4},
  {"ucfirst_ext", (DL_FUNC) &CSR_ucfirst_ext, 2},
  {"lcfirst_ext", (DL_FUNC) &CSR_lcfirst_ext, 2},
  {"test_strmcpy", (DL_FUNC) &CSR_test_strmcpy, 0},
  {"test_strappend", (DL_FUNC) &CSR_test_strappend, 0},
  {"test_add_szt", (DL_FUNC) &CSR_test_add_szt, 0},
  {"test_smprintfx", (DL_FUNC) &CSR_test_smprintfx, 0},
  {"test_strappend2", (DL_FUNC) &CSR_test_strappend2, 0},
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
  R_RegisterCCallable("cstringr", "CSR_bullet", (DL_FUNC) CSR_bullet);
  R_RegisterCCallable("cstringr", "CSR_collapse", (DL_FUNC) CSR_collapse);
  R_RegisterCCallable("cstringr", "CSR_strmcpy", (DL_FUNC) CSR_strmcpy);
  R_RegisterCCallable("cstringr", "CSR_smprintf6", (DL_FUNC) CSR_smprintf6);
  R_RegisterCCallable("cstringr", "CSR_smprintf5", (DL_FUNC) CSR_smprintf5);
  R_RegisterCCallable("cstringr", "CSR_smprintf4", (DL_FUNC) CSR_smprintf4);
  R_RegisterCCallable("cstringr", "CSR_smprintf3", (DL_FUNC) CSR_smprintf3);
  R_RegisterCCallable("cstringr", "CSR_smprintf2", (DL_FUNC) CSR_smprintf2);
  R_RegisterCCallable("cstringr", "CSR_smprintf1", (DL_FUNC) CSR_smprintf1);
}
