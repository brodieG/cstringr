#' Set Number of Chars after Which To Assume Termination
#'
#' Strings longer than \code{x} will be reported as being \code{x} long.  This
#' sets a global variable that affects several other functions in the package.
#'
#' @seealso \code{\link{strlen}}, \code{\link{strtrunc}}, \code{\link{sprintf2}}
#' @param integer(1L)
#' @return \code{x} on success, errors on failure
#' @export

set_max_strlen <- function(x) .Call(CSR_set_max_strlen_ext, x)

#' Number of Characters Taken By Numeric Representation
#'
#' e.g., for 100, would be 3, for 1324, would be 4.
#'
#' @param integer(1L)
#' @return integer(1L)
#' @export

len_chr_len <- function(x) .Call(CSR_len_chr_len_ext, x)

#' Number Converted To character
#'
#' e.g., \code{100} becomes \code{"100"}
#'
#' @param integer(1L)
#' @return character(1L)
#' @export

len_as_chr <-function(x) .Call(CSR_len_as_chr_ext, x)

#' Character Length of String
#'
#' e.g., \code{"abc"} returns 3
#'
#' @seealso \code{\link{set_max_strlen}}
#' @param x charater(1L)
#' @return integer(1L)
#' @export

strlen <- function(x) .Call(CSR_strlen_ext, x)

#' Truncate String Down to max_strlen If Necessary
#'
#' @seealso \code{\link{set_max_strlen}}
#' @param x character(1L)
#' @return character(1L)
#' @export

strtrunc <- function(x) .Call(CSR_strtrunc_ext, x)

#' Combines Multiple Character Strings Into One
#'
#' Much like \code{\link{sprintf}}, but ensures all arguments are NULL terminated
#' or truncates them if they exceed max_strlen, also only allows two tokens.
#'
#' @seealso \code{\link{set_max_strlen}}, \code{\link{sprintf}}
#' @param x character(1L) the base string to sub the others into
#' @param a character(1L) another string
#' @param b character(1L) another string
#' @return character(1L)
#' @export

sprintf2 <- function(x, a, b) .Call(CSR_rsprintf2_ext, x, a, b)
