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
A safe strmlen, stops counting at number of characters specified by maxlen

from insane blogger
*/
size_t CSR_strmlen(const char * str, size_t maxlen) {
  const char *p = (const char *) memchr(str, 0, maxlen);
  return (p ? p - str : maxlen);
}
/*
If str has more than size characters, returns a copy of str truncated to size
characters with a null character appended such that strmlen() str == size,
otherwise returns a copy of str.

Note, final string size could be up to maxlen + 1 including the NULL terminator.
*/
char * CSR_strmcpy(const char * str, size_t maxlen) {
  if(!maxlen) return("");
  if(!(maxlen + 1))
    error("Argument `maxlen` must be at least one smaller than max possible size_t value.");

  size_t len = CSR_strmlen(str, maxlen);
  char * str_new = R_alloc(len + 1, sizeof(char));

  if(len == maxlen) {  // Need to truncate
    if(!strncpy(str_new, str, maxlen))
      error("Logic Error: failed making copy of string for truncation; contact maintainer.");
    str_new[maxlen] = '\0';
    return str_new;
  } else if (len < maxlen) {
    strcpy(str_new, str);
    return str_new;
  }
  error("Logic Error: should never get here 46; contact maintainer.");
}

/* Add two size_t if possible, error otherwise */

static size_t add_szt(size_t a, size_t b) {
  size_t full_len = a + b;
  if(full_len < a || full_len < b)
    error("size_t overflow: you are likely attempting to construct a string with more than size_t characters");
  return full_len;
}
/* Returns a character pointer containing the results of using `a` as the parent
string and all the others a substrings with `sprintf`

note:
- will over-allocate by the amount of formatting characters, could fix, but meh
*/

char * CSR_smprintf6(
  size_t maxlen, const char * format, const char * a, const char * b,
  const char * c, const char * d, const char * e, const char * f
) {
  // Make sure we don't exceed size_t

  size_t full_len;
  full_len = add_szt(CSR_strmlen(format, maxlen), CSR_strmlen(a, maxlen));
  full_len = add_szt(full_len, CSR_strmlen(b, maxlen));
  full_len = add_szt(full_len, CSR_strmlen(c, maxlen));
  full_len = add_szt(full_len, CSR_strmlen(d, maxlen));
  full_len = add_szt(full_len, CSR_strmlen(e, maxlen));
  full_len = add_szt(full_len, CSR_strmlen(f, maxlen));

  char * res;
  res = R_alloc(full_len, sizeof(char));
  sprintf(
    res, CSR_strmcpy(format, maxlen), CSR_strmcpy(a, maxlen),
    CSR_strmcpy(b, maxlen), CSR_strmcpy(c, maxlen),
    CSR_strmcpy(d, maxlen), CSR_strmcpy(e, maxlen), CSR_strmcpy(f, maxlen)
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



