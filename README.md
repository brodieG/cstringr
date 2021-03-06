#  cstringr - C String Manipulation Functions for R

[![](https://travis-ci.org/brodieG/cstringr.svg?branch=master)](https://travis-ci.org/brodieG/cstringr)
[![](https://codecov.io/github/brodieG/cstringr/coverage.svg?branch=master)](https://codecov.io/github/brodieG/cstringr?branch=master)
[![Project Status: Unsupported – The project has reached a stable, usable state but the author(s) have ceased all work on it.](http://www.repostatus.org/badges/latest/unsupported.svg)](http://www.repostatus.org/#unsupported)

## Overview

**DO NOT USE THESE FUNCTIONS WITH STRINGS NOT KNOWN TO BE NULL TERMINATED**.

Low level C string manipulation functions intended for use from C code in other
R packages.  Some functions are exposed via R for testing purposes, but there is
no point in using those since base R already implements all of the functionality
in this package.

The main use of the package is for the C functions therein that are
`R_RegisterCCallable`d.  The functions include versions of `strlen` and
`sprintf` that stop looking for a NULL terminator if they don't find one after a
certain number of characters to avoid undefined behavior.  Note however that
this is of limited value if you do not know the buffer size as you can still
read past the end of the buffer.

The functions also use `R_alloc` to allocate memory for strings that need to be
copied, and do not use POSIX only functions like `strnlen`.

> The contents of this package have been partly integrated into
> [vetr](https://github.com/brodieG/vetr).  Some day we might resume development
> of this package on a stand alone basis, but don't hold your breath.

## Installation

This package is only available on github:
```
devtools::install_github('brodieG/cstringr')
```

## Acknolwedgments

* insane coder for [strnlen implementation](http://insanecoding.blogspot.com/2007/03/methods-for-safe-string-handling.html)
