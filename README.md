# cstringr

Pre-release.

Low level C string manipulation functions.  This is the R interface that is intended solely for testing since R already implements this functionality and more.  The main use of the package is for the C functions that therein that are \code{R_RegisterCCallable}'d.  The functions include versions of `strlen` and `sprintf` that stop looking for a NULL terminator if they don't find one after a certain number of characters to avoid undefined behavior.
