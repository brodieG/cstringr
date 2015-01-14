# cstringr

Pre-release, interface likely to change.

Low level C string manipulation functions.  This is the R interface that is intended solely for testing since R already implements this functionality and more.  The main use of the package is for the C functions therein that are `R_RegisterCCallable`d.  The functions include versions of `strlen` and `sprintf` that stop looking for a NULL terminator if they don't find one after a certain number of characters to avoid undefined behavior.  The functions also use `R_alloc` to allocate memory for strings that need to be copied, and do not use POSIX only functions like `strnlen`.

# Acknolwedgments

* insane coder for [strnlen implementation](http://insanecoding.blogspot.com/2007/03/methods-for-safe-string-handling.html)
* Hadley for name
