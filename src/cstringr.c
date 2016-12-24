#include "cstringr.h"

/* Estimate how many characters a R_xlen_t number can be represented with*/

size_t CSR_len_chr_len(R_xlen_t a) {
  if(a < 0)
    error("Logic Error: unexpected negative length value; contact maintainer");
  size_t log_len = (size_t) ceil(log10(a + 1.00001));  // + 1.00001 to account for 0
  return log_len;
}
/*
Returns a character pointer to the string representation of the integer; allocates
with R_alloc so in theory don't need to worry about freeing memory
*/

char * CSR_len_as_chr(R_xlen_t a) {
  char * res;
  res = R_alloc(CSR_len_chr_len(a) + 1, sizeof(char));
  if(!sprintf(res, "%zd", a))    // used to be %td, but doesn't work on windows?
    error("Logic Error: r_xlen_to_char conversion failed");
  return res;
}
/*
A safe strmlen, errors if exceeds `maxlen`

If success, returns size of string excluding the NULL terminator.  If the NULL
terminator is not found prior to `maxlen`, then errors.

See CSR_strmlen_x for a version of this function that does not error, but
careful using it with strcpy as you could get an overflow.  CSR_strmcpy will
stop copying upon hitting `maxlen` and will add a NULL terminator so it is safe
to use CSR_strmlen with that.

partly from insane blogger
*/
size_t CSR_strmlen(const char * str, size_t maxlen) {
  size_t res = CSR_strmlen_x(str, maxlen);
  if(res == maxlen && *(str + res)) {
    // reached max len and next charcter is not NULL terminator
    error("%s %s %d %s",
      "Internal Error (CSR_strmlen): failed to find string terminator prior",
      "to maxlen", maxlen, "characters"
    );
  }
  return res;
}
/*
IMPORTANT: only use with CSR_strmcpy since that will not try to copy past maxlen
*/
size_t CSR_strmlen_x(const char * str, size_t maxlen) {
  const char *p = (const char *) memchr(str, 0, maxlen);
  size_t res;
  if(!p) {
    res = maxlen;
  } else {
    res = p - str;
  }
  return res;
}
/*
If str has more than size characters, returns a copy of str truncated to size
characters with a null character appended such that strmlen() str == size,
otherwise returns a copy of str.

Note, final string size could be up to maxlen + 1 including the NULL terminator.
A NULL terminator is always added at the end of the string.
*/
char * CSR_strmcpy(const char * str, size_t maxlen) {
  if(!maxlen) return("");
  if(!(maxlen + 1))
    error("%s%s",
      "Argument `maxlen` must be at least one smaller than max possible ",
      "size_t value."
    );

  size_t len = CSR_strmlen_x(str, maxlen);
  if(len == maxlen && str[len])
    warning("CSR_strmcopy: truncated string longer than %d", maxlen);

  char * str_new = R_alloc(len + 1, sizeof(char));

  if(!strncpy(str_new, str, len))
    error("%s%s",
      "Internal Error (CSR_strmcopy): failed making copy of string for  ",
      "truncation; contact maintainer."
    );
  // Ensure null terminated if last character is not NULL; this happens when
  // truncating to `maxlen`, also if zero len make sure that is a NULL

  if(!len) {
    str_new[0] = '\0';
  } else if(str_new[len - 1]) str_new[len] = '\0';

  return str_new;
}
/*
 * Like CSR_strmcpy, but copies to a presupplied pointer (`target`).  In this
 * way it is much closer to strncpy, except that it truncates everything at
 * `maxlen`.
 *
 * Note this requires that you pre-compute and allocate `str` properly.
 */
void CSR_strappend(char * target, const char * str, size_t maxlen) {
  if(maxlen) {
    if(!(maxlen + 1))
      error("%s%s",
        "Argument `maxlen` must be at least one smaller than max possible ",
        "size_t value."
      );
    if(!strncpy(target, str, maxlen))
      error("%s%s",
        "Internal Error (CSR_strmcopy): failed making copy of string for  ",
        "truncation; contact maintainer."
      );

    size_t len = CSR_strmlen_x(str, maxlen);
    if(len == maxlen && str[len])
      warning("CSR_strappend: truncated string longer than %d", maxlen);

    // Ensure null terminated if last character is not NULL; this happens when
    // truncating to `maxlen`, also if zero len make sure that is a NULL

    if(!len) {
      target[0] = '\0';
    } else if(target[len - 1]) target[len] = '\0';
  }
}

/* Add two size_t if possible, error otherwise */

static size_t add_szt(size_t a, size_t b) {
  size_t full_len = a + b;
  if(full_len < a || full_len < b)
    error("%s%s",
      "size_t overflow: you tried to add two size_t numbers that together ",
      "overflow size_t"
    );
  return full_len;
}
/*
Returns a character pointer containing the results of using `a` as the parent
string and all the others a substrings with `sprintf`

note:
- will over-allocate by the amount of formatting characters
- maxlen limits the length of individual components and the formatting string,
not the output
*/

char * CSR_smprintf6(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d, const char * e, const char * f
) {
  size_t full_len;
  full_len = add_szt(CSR_strmlen_x(format, maxlen), CSR_strmlen_x(a, maxlen));
  full_len = add_szt(full_len, CSR_strmlen_x(b, maxlen));
  full_len = add_szt(full_len, CSR_strmlen_x(c, maxlen));
  full_len = add_szt(full_len, CSR_strmlen_x(d, maxlen));
  full_len = add_szt(full_len, CSR_strmlen_x(e, maxlen));
  full_len = add_szt(full_len, CSR_strmlen_x(f, maxlen));


  char * res;
  res = R_alloc(full_len + 1, sizeof(char));
  int res_len = sprintf(
    res, CSR_strmcpy(format, maxlen), CSR_strmcpy(a, maxlen),
    CSR_strmcpy(b, maxlen), CSR_strmcpy(c, maxlen),
    CSR_strmcpy(d, maxlen), CSR_strmcpy(e, maxlen), CSR_strmcpy(f, maxlen)
  );
  if(res_len < 0)
    error("%s%s",
      "Internal Error (CSR_smprintf): `sprintf` returned -1 when generating ",
      "new string"
    );
  return res;
}
char * CSR_smprintf5(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d, const char * e
) {
  return(CSR_smprintf6(maxlen, format, a, b, c, d, e, ""));
}
char * CSR_smprintf4(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d
) {
  return(CSR_smprintf6(maxlen, format, a, b, c, d, "", ""));
}
char * CSR_smprintf3(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c
) {
  return(CSR_smprintf6(maxlen, format, a, b, c, "", "", ""));
}
char * CSR_smprintf2(
  size_t maxlen, const char * format, const char * a, const char * b
) {
  return(CSR_smprintf6(maxlen, format, a, b, "", "", "", ""));
}
char * CSR_smprintf1(size_t maxlen, const char * format, const char * a) {
  return(CSR_smprintf6(maxlen, format, a, "", "", "", "", ""));
}

// - Capitalization functions --------------------------------------------------

/* Make copy and capitalize first letter */

char * CSR_ucfirst(const char * str, size_t maxlen) {
  char * str_new = (char *) CSR_strmcpy(str, maxlen);
  str_new[0] = toupper(str_new[0]);
  return str_new;
}
char * CSR_lcfirst(const char * str, size_t maxlen) {
  char * str_new = (char *) CSR_strmcpy(str, maxlen);
  str_new[0] = tolower(str_new[0]);
  return str_new;
}
/*
 * Makes a copy of string, and adds `bullet` at the beginning, and `ctd` after
 * each newline
 *
 * Remember we could end up allocating 1 more than max_len
 */

const char * CSR_bullet(
  const char * string, const char * bullet, const char * ctd, size_t max_len
) {
  size_t newlines=0;
  const char * string_copy = string;

  while(*string_copy) {
    if(*string_copy == '\n' && *(string_copy + 1)) ++newlines;
    ++string_copy;
    if(string_copy - string + 1 > max_len)
      error("Exceeded `max_len` when trying to bullet `string`");
  }
  size_t ctd_size = CSR_strmlen(ctd, max_len);
  size_t bullet_size = CSR_strmlen(bullet, max_len);

  // Add all numbers together in a way that checks for overflows

  size_t size_all = add_szt(string_copy - string, 1);
  size_all = add_szt(size_all, bullet_size);
  for(size_t i = 0; i < newlines; ++i) size_all = add_szt(size_all, ctd_size);

  if(size_all > max_len)
    error("Exceeded `max_len` when trying to bullet `string` (2)");

  // Now allocate

  char * res = R_alloc(size_all + 1, sizeof(char));
  char * res_cpy  = res;

  // Second pass, copy stuff to our result string, start by adding the bullet

  strcpy(res_cpy, bullet);
  res_cpy += bullet_size;

  string_copy = string;
  while(*string_copy) {
    int add_ctd = 0;
    *res_cpy = *string_copy;
    if(*res_cpy == '\n') {
      add_ctd = 1;
    }
    ++res_cpy;
    ++string_copy;
    if(add_ctd) {
      strcpy(res_cpy, ctd);
      res_cpy += ctd_size;
    }
    // *(res_cpy + 1) = '\0';  // so we can Rprintf
  }
  *(res_cpy) = '\0';

  return res;
}
/*
 * Collapse STRSXP into one chr *
 *
 * Strings will get truncate dat `max_len` if they are longer than that
 */

const char * CSR_collapse(SEXP str, const char * sep, size_t max_len) {
  if(TYPEOF(str) != STRSXP) error("Argument `str` must be a character vector");

  R_xlen_t str_len = XLENGTH(str);
  if(!str_len) {
    return "";
  } else {
    // Compute sizes

    size_t size_all = 0;
    size_t sep_len = CSR_strmlen_x(sep, max_len);
    R_xlen_t i;

    for(i = 0; i < str_len; i++) {
      size_all =
        add_szt(size_all, CSR_strmlen_x(CHAR(STRING_ELT(str, i)), max_len));
      if(i < str_len - 1) {
        size_all = add_szt(size_all, sep_len);
      }
    }
    // Allocate and generate string

    char * str_new = R_alloc(size_all + 1, sizeof(char));
    char * str_cpy = str_new;
    Rprintf("Allocated %zu\n", size_all + 1);

    for(i = 0; i < str_len; i++) {
      const char * to_copy = CHAR(STRING_ELT(str, i));
      CSR_strappend(str_cpy, to_copy, max_len);
      str_cpy += CSR_strmlen_x(to_copy, max_len);
      if(i < str_len - 1) {
        CSR_strappend(str_cpy, sep, max_len);
        str_cpy += sep_len;
      }
      Rprintf("%s: %zu\n", str_new, str_cpy - str_new);
    }
    *str_cpy = '\0';
    return (const char *) str_new;
  }
  error("Internal error: should never get here 2123; contact maintainer.");
}
SEXP CSR_collapse_ext(SEXP str, SEXP sep, SEXP max_len) {
  return mkString(CSR_collapse(str, CHAR(asChar(sep)), INTEGER(max_len)[0]));
}
