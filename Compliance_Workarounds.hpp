#pragma once

// need to include something from the standard library so _LIBCPP_VERSION gets defined, so don't move
// these #includes under that conditional compile
#include <compare>          // strong_oredering
#include <chrono>           // hh_mm_ss<>
#include <iostream>         // ostream
#include <string>


// C++20 Transition Workarounds
//    _LIBCPP_VERSION is set if using LLVM's libc++ library
//    __GLIBCXX__     is set if using GNU's libstdc++ library (set to date of release)
//           (__GLIBC__ * 1'000 + __GLIBC_MINOR__)  gives libstdc++ version
//    __GNUC__        is defined if using GCC, but also sometimes when using Clang
//          (__GNUC__ * 1'000'000 + __GNUC_MINOR__ * 1'000 + __GNUC_PATCHLEVEL__) give gcc version



#if defined( _LIBCPP_VERSION )
  namespace std
  {
    #if _LIBCPP_VERSION < 16'000
       inline strong_ordering operator<=>( const string & lhs, const string & rhs) noexcept
       {
         int result = lhs.compare( rhs );
         return result == 0  ?  strong_ordering::equivalent
              : result  < 0  ?  strong_ordering::less
              :                 strong_ordering::greater;
       }
    #else
      #pragma message ("A potentially obsolete C++20 workaround is present.  Either remove the workaround if no longer needed, or update the version number requiring it")
    #endif
  } // namespace std
#endif // defined( _LIBCPP_VERSION )




#if( ( defined( _LIBCPP_VERSION ) && (_LIBCPP_VERSION                      <   16'000 )) || \
     ( defined( __GLIBCXX__     ) && ( __GLIBC__ * 1'000 + __GLIBC_MINOR__ <=   2'040 )) )      // roughly a little beyond gcc 11.2.1 (run "ldd --version" and "gcc --version" at the command line)
  namespace std::chrono                                                                         // Check lib version and not gcc version, clang may use gnu's libstdc++ library
  {
    template<class Duration>
    inline std::ostream & operator<<( std::ostream & os, const std::chrono::hh_mm_ss<Duration> & t )
    {
      return os << t.hours     ().count() << ':'
                << t.minutes   ().count() << ':'
                << t.seconds   ().count() << "."
                << t.subseconds().count();
    }
  }    // namespace std::chrono
#else
  #pragma message( "A potentially obsolete C++20 workaround is present.  Either remove the workaround if no longer needed, or update the version number requiring it" )
#endif    // ( _LIBCPP_VERSION || __GLIBCXX__ )
