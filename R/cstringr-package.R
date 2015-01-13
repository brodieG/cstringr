#' cstringr
#'
#' Low level C string manipulation functions.  This is the R interface that is
#' intended solely for testing since R already implements this functionality
#' and more.  The main use of the package is for the C functions that are
#' \code{R_RegisterCCallable}'d.
#'
#' @useDynLib cstringr, .registration=TRUE, .fixes="CSR_"
#' @name cstringr-package
#' @docType package

NULL
