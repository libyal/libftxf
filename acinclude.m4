dnl Checks for required headers and functions
dnl
dnl Version: 20240413

dnl Function to detect if libftxf dependencies are available
AC_DEFUN([AX_LIBFTXF_CHECK_LOCAL],
  [dnl No additional checks.
  ])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBFTXF_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBFTXF_DLL_EXPORT],
        ["-DLIBFTXF_DLL_EXPORT"])

      AC_SUBST(
        [LIBFTXF_DLL_IMPORT],
        ["-DLIBFTXF_DLL_IMPORT"])
      ])
    ])
  ])

