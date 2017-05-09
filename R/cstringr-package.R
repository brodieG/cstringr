#' cstringr
#'
#' Low level C string manipulation functions intended for use from C code in
#' other R packages.  Some functions are exposed via R for testing purposes, but
#' there is no point in using those since base R already implements all of the
#' functionality in this package.
#'
#' @useDynLib cstringr, .registration=TRUE, .fixes="CSR_"
#' @name cstringr-package
#' @docType package

NULL
