#ifndef dplyr_registration_H
#define dplyr_registration_H

namespace dplyr {
  class LazySubsets;
  class Result;
}

typedef dplyr::Result* (*HybridHandler)(SEXP, const dplyr::LazySubsets&, int);

#if defined(COMPILING_DPLYR)

DataFrame build_index_cpp(DataFrame data);
void registerHybridHandler(const char*, HybridHandler);
SEXP get_time_classes();
SEXP get_date_classes();

#else

#define GRAB_CALLABLE(__FUN__) static Fun fun = (Fun)R_GetCCallable( "dplyr", #__FUN__ );

inline DataFrame build_index_cpp(DataFrame data) {
  typedef DataFrame(*Fun)(DataFrame);
  GRAB_CALLABLE(build_index_cpp)
  return fun(data);
}

inline void registerHybridHandler(const char* name, HybridHandler proto) {
  typedef void (*Fun)(const char*, HybridHandler);
  GRAB_CALLABLE(registerHybridHandler)
  return fun(name, proto);
}

inline SEXP get_time_classes() {
  typedef SEXP(*Fun)(void);
  GRAB_CALLABLE(get_time_classes)
  return fun();
}

inline SEXP get_date_classes() {
  typedef SEXP(*Fun)(void);
  GRAB_CALLABLE(get_time_classes)
  return fun();
}

#endif

#endif

