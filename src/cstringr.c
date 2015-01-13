#include "cstringr.h"

/*
what length to assume string is unterminated, run purely for the side effect of
setting the value of global variable MAX_STR_LEN
*/

static size_t MAX_STR_LEN = 20000;

void CSR_set_max_strlen(size_t len) {
  if(!len + 1)
    error("Argument `len` must be at least one smaller than max possible size_t value.");
  MAX_STR_LEN = len;
}

// - Helper Functions ----------------------------------------------------------

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

const char * CSR_len_as_chr(R_xlen_t a) {
  char * res;
  res = R_alloc(CSR_len_chr_len(a) + 1, sizeof(char));
  if(!sprintf(res, "%zd", a))    // used to be %td, but doesn't work on windows?
    error("Logic Error: r_xlen_to_char conversion failed");
  return (const char *) res;
}
/*
A safe strlen, stops counting at number of characters specified by MAX_STR_LEN
*/
size_t CSR_strlen(const char * str) {
  size_t i;
  for(i = 0; i < MAX_STR_LEN && str[i]; i++);
  return i;
}
/*
If str has more than size characters, returns a copy of str truncated to size
characters with a null character appended such that strlen() str == size,
otherwise returns str.

This should eliminate the risk of unterminated strings.
*/
const char * CSR_strtrunc(const char * str) {
  if(!MAX_STR_LEN) return("");
  size_t len = CSR_strlen(str);
  if(len == MAX_STR_LEN) {  // Need to truncate
    char * str_new = R_alloc(MAX_STR_LEN + 1, sizeof(char));
    if(!strncpy(str_new, str, MAX_STR_LEN))
      error("Logic Error: failed making copy of string for truncation; contact maintainer.");
    str_new[MAX_STR_LEN] = '\0';
    return (const char *) str_new;
  } else if (len < MAX_STR_LEN) return(str);
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

const char * CSR_sprintf6(
  const char * base, const char * a, const char * b, const char * c,
  const char * d, const char * e, const char * f
) {
  // Make sure we don't exceed size_t

  size_t full_len;
  full_len = add_szt(CSR_strlen(base), CSR_strlen(a));
  full_len = add_szt(full_len, CSR_strlen(b));
  full_len = add_szt(full_len, CSR_strlen(c));
  full_len = add_szt(full_len, CSR_strlen(d));
  full_len = add_szt(full_len, CSR_strlen(e));
  full_len = add_szt(full_len, CSR_strlen(f));

  char * res;
  res = R_alloc(full_len, sizeof(char));
  sprintf(res, base, a, b, c, d, e, f);
  return (const char *) res;
}
const char * CSR_sprintf5(
  const char * base, const char * a, const char * b, const char * c,
  const char * d, const char * e
) {
  return(CSR_sprintf6(base, a, b, c, d, e, ""));
}
const char * CSR_sprintf4(
  const char * base, const char * a, const char * b, const char * c,
  const char * d
) {
  return(CSR_sprintf6(base, a, b, c, d, "", ""));
}
const char * CSR_sprintf3(
  const char * base, const char * a, const char * b, const char * c
) {
  return(CSR_sprintf6(base, a, b, c, "", "", ""));
}
const char * CSR_sprintf2(const char * base, const char * a, const char * b) {
  return(CSR_sprintf6(base, a, b, "", "", "", ""));
}
const char * CSR_sprintf1(const char * base, const char * a) {
  return(CSR_sprintf6(base, a, "", "", "", "", ""));
}
