#!/usr/bin/env bash
#
# Script file to compile all C++ source files in or under the
# current directory.  This has been used in the OpenSUSE and Ubuntu
# environments with the GCC and Clang compilers and linkers
executableFileName="${1:-project}"
versionID="23.01.08"
echo "${0##*/} version ${versionID}"


### Check GCC and Clang versions on Tuffix, and upgrade if needed - Usually a one-time occurrence
###  The procedure should be removed once Tuffix is configured out-of-the-box with correct versions
CheckVersion()
{
  #  See Parameter Expansion section of Bash man page for "%%"'s' Remove matching suffix pattern
  #  behavior (https://linux.die.net/man/1/bash)
  #
  #  ${parameter,,}     ==> lower case
  #  ${parameter^^}     ==> upper case
  #  ${parameter%word}  ==> Remove matching suffix pattern (shortest matching pattern)
  #  ${parameter%%word} ==> Remove matching suffix pattern (longest matching pattern)

  buffer=( $(g++ --version ) )
  gccVersion="${buffer[3]%%.*}"

  # This is pretty fragile, but version 10 and 12+ display the version slightly differently
  buffer=( $(clang++ --version ) )
  if   [[ ${buffer[1],,} = "version" ]]; then  clangVersion="${buffer[2]%%.*}"
  elif [[ ${buffer[2],,} = "version" ]]; then  clangVersion="${buffer[3]%%.*}"
  fi

  RequiredGccVersion=12
  RequiredClangVersion=14



  ## Check minimum compiler versions
  if [[ "${gccVersion,,}" -lt "${RequiredGccVersion,,}"  ||  "${clangVersion,,}" -lt "${RequiredClangVersion,,}" ]]; then
    ## Minimum compiler versions not found, let's see if we can install them
    echo -e "\nGCC version ${RequiredGccVersion} and Clang version ${RequiredClangVersion} are required, but you're using GCC version ${gccVersion} and Clang version ${clangVersion}"

    ## Get distribution
    buffer=( $(lsb_release -d ) )
    Distribution="${buffer[1]}"


    if [[ "${Distribution,,}" = "ubuntu" ]]; then

      buffer=( $(lsb_release -r ) )
      Release="${buffer[1]}"

      ## Ubuntu 22.04 support
      if [[ "${Release,,}" = "22.04" ]]; then
        echo -e "\nWould like to upgrade now?  This may require a system reboot. (yes or no)"
        read shall_I_upgrade

        if [[ "${shall_I_upgrade,,}x" = "yesx"  ||  "${shall_I_upgrade,,}x" = "yx" ]]; then
          echo -e "\nUpgrading could be a long and extensive process.\n\n ****  Make sure you have backups of all your data!\n\n Are you really sure?"
          read shall_I_upgrade
          if [[ "${shall_I_upgrade,,}x" = "yesx"  ||  "${shall_I_upgrade,,}x" = "yx" ]]; then

            echo -e "Yes.  Okay, attempting to upgrade now.  The upgrade requires super user privileges and you may be prompted for your password.\n"

            sudo /bin/bash -svx -- <<-EOF   # the "-" after the "<<" allows leading tabs (but not spaces), a quoted EOF would mean literal input, i.e., do not substitute parameters

				# Move gcc 11 and clang 13 to gcc ${RequiredGccVersion} and clang ${RequiredClangVersion} on Ubuntu 22.04 LTS

				apt -y update
				apt -y full-upgrade

				apt -y install build-essential manpages-dev gdb ddd											# in case "Tuffix" is not installed (e.g. WSL)

				apt -y install gcc-${RequiredGccVersion} g++-${RequiredGccVersion}
				update-alternatives  --install /usr/bin/gcc gcc /usr/bin/gcc-${RequiredGccVersion} ${RequiredGccVersion}  --slave /usr/bin/g++         g++         /usr/bin/g++-${RequiredGccVersion}        \
				                                                                                                          --slave /usr/bin/gcc-ar      gcc-ar      /usr/bin/gcc-ar-${RequiredGccVersion}     \
				                                                                                                          --slave /usr/bin/gcc-nm      gcc-nm      /usr/bin/gcc-nm-${RequiredGccVersion}     \
				                                                                                                          --slave /usr/bin/gcc-ranlib  gcc-ranlib  /usr/bin/gcc-ranlib-${RequiredGccVersion} \
				                                                                                                          --slave /usr/bin/gcov        gcov        /usr/bin/gcov-${RequiredGccVersion}       \
				                                                                                                          --slave /usr/bin/gcov-dump   gcov-dump   /usr/bin/gcov-dump-${RequiredGccVersion}  \
				                                                                                                          --slave /usr/bin/gcov-tool   gcov-tool   /usr/bin/gcov-tool-${RequiredGccVersion}

				update-alternatives  --install /usr/bin/gcc gcc /usr/bin/gcc-11  11                                       --slave /usr/bin/g++         g++         /usr/bin/g++-11                   \
				                                                                                                          --slave /usr/bin/gcc-ar      gcc-ar      /usr/bin/gcc-ar-11                \
				                                                                                                          --slave /usr/bin/gcc-nm      gcc-nm      /usr/bin/gcc-nm-11                \
				                                                                                                          --slave /usr/bin/gcc-ranlib  gcc-ranlib  /usr/bin/gcc-ranlib-11            \
				                                                                                                          --slave /usr/bin/gcov        gcov        /usr/bin/gcov-11                  \
				                                                                                                          --slave /usr/bin/gcov-dump   gcov-dump   /usr/bin/gcov-dump-11             \
				                                                                                                          --slave /usr/bin/gcov-tool   gcov-tool   /usr/bin/gcov-tool-11

				apt -y install clang-${RequiredClangVersion} clang-tools-${RequiredClangVersion} clang-${RequiredClangVersion}-doc libclang-common-${RequiredClangVersion}-dev libclang-${RequiredClangVersion}-dev libclang1-${RequiredClangVersion} clang-format-${RequiredClangVersion} clang-tidy-${RequiredClangVersion} python3-clang-${RequiredClangVersion} clangd-${RequiredClangVersion}
				apt -y install lldb-${RequiredClangVersion} lld-${RequiredClangVersion}
				apt -y install libc++-${RequiredClangVersion}-dev libc++abi-${RequiredClangVersion}-dev

				apt -y autoremove

				update-alternatives  --install /usr/bin/clang clang /usr/bin/clang-${RequiredClangVersion} ${RequiredClangVersion}  --slave /usr/bin/clang++            clang++            /usr/bin/clang++-${RequiredClangVersion}              \
				                                                                                                                    --slave /usr/bin/clang-format       clang-format       /usr/bin/clang-format-${RequiredClangVersion}         \
				                                                                                                                    --slave /usr/bin/clang-format-diff  clang-format-diff  /usr/bin/clang-format-diff-${RequiredClangVersion}    \
				                                                                                                                    --slave /usr/bin/clang-tidy         clang-tidy         /usr/bin/clang-tidy-${RequiredClangVersion}           \
				                                                                                                                    --slave /usr/bin/clang-tidy-diff    clang-tidy-diff    /usr/bin/clang-tidy-diff-${RequiredClangVersion}.py

				update-alternatives  --install /usr/bin/clang clang /usr/bin/clang-13 13                                            --slave /usr/bin/clang++            clang++            /usr/bin/clang++-13              \
				                                                                                                                    --slave /usr/bin/clang-format       clang-format       /usr/bin/clang-format-13         \
				                                                                                                                    --slave /usr/bin/clang-format-diff  clang-format-diff  /usr/bin/clang-format-diff-13    \
				                                                                                                                    --slave /usr/bin/clang-tidy         clang-tidy         /usr/bin/clang-tidy-13           \
				                                                                                                                    --slave /usr/bin/clang-tidy-diff    clang-tidy-diff    /usr/bin/clang-tidy-diff-13.py
				sudo update-alternatives --auto gcc
				sudo update-alternatives --auto clang

				###################
				# To remove:
				# sudo update-alternatives --set gcc   /usr/bin/gcc-9
				# sudo update-alternatives --set clang /usr/bin/clang-10

				###################
				# To select which version interactively:
				# sudo update-alternatives --config gcc
				# sudo update-alternatives --config clang

				###################
				# References:
				# https://apt.llvm.org/
				# https://stackoverflow.com/questions/67298443/when-gcc-11-will-appear-in-ubuntu-repositories/67406788#67406788

				EOF

          exit

          fi # upgrade? 2
        fi  # upgrade? 1

      else ## Ubuntu, but not 22.04
        echo -e "These required GCC and/or Clang versions are not available on Ubuntu ${Release}\n"
        echo -e "Please consider upgrading to Ubuntu 22.04 or better.  See https://youtu.be/2Mwo4BfJuvA"
        echo -e "    sudo do-release-upgrade"
      fi  ## Ubuntu 22.04 support

    fi

    echo -e "Build process aborted.  Please install GCC version ${RequiredGccVersion} or better and Clang version ${RequiredClangVersion} or better for your platform"
    echo -e "\n\nPlatform Information:\n====================="
    cat  /etc/*-release
    exit
  fi  # gccVersion || clangVersion
}


BuildWorkaroundHeader()
{
	cat - > "${complianceHelperFile_path}" <<-"EOF"   # the "-" after the "<<" allow leading tabs (but not spaces), the quoted EOF means literal input, i.e., do not substitute parameters
		/******************************************************************************
		** Auto generated from Build.sh
		******************************************************************************/

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
	EOF
}




CheckVersion



### Vendors are releasing version of their C++ compilers and libraries with ever more C++20 compliant features, but
### they're not fully compliant yet.  And Linux vendors are slow to make these new versions available.  As a result,
### we see in practice various degrees of compliance which we can compensate for by providing the missing pieces in a
### header file that is added to each translation unit.  We search for such a header file first in the current working
### it on the fly.  This search order allows such a (potentially updated) header file to be provided with each project.
### directory, then in the same directory as this build script, and if not found in either of those locations we create
complianceHelperFile_filename="Compliance_Workarounds.hpp"

complianceHelperFile_path="./${complianceHelperFile_filename}"
if [[ ! -f "${complianceHelperFile_path}" ]]; then                                   # Is the helper file in the current directory?
  complianceHelperFile_path="${0%/*}/${complianceHelperFile_filename}"
  if [[ ! -f "${complianceHelperFile_path}" ]]; then                                 # Is the helper file in the same directory as this script (Build.sh)
    complianceHelperFile_path="$( mktemp -p /tmp ${complianceHelperFile_filename}.XXXXXXXX || exit 3 )"
    trap 'rm -f "${complianceHelperFile_path}"' EXIT                                 # clean up after my self
    BuildWorkaroundHeader
  fi
fi



# Find and display all the C++ source files to be compiled ...
# temporarily ignore spaces when globing words into file names
temp=$IFS
  IFS=$'\n'
  sourceFiles=( $(find ./ -path ./.\* -prune -o -name "*.cpp" -print) )              # create array of source files skipping hidden folders (folders that start with a dot)
IFS=$temp

echo "Compiling in \"$PWD\" ..."
for fileName in "${sourceFiles[@]}"; do
  echo "  $fileName"
done
echo ""


#define options
GccOptions="  -Wall -Wextra -pedantic        \
              -Wdelete-non-virtual-dtor      \
              -Wduplicated-branches          \
              -Wduplicated-cond              \
              -Wextra-semi                   \
              -Wfloat-equal                  \
              -Winit-self                    \
              -Wlogical-op                   \
              -Wnoexcept                     \
              -Wshadow                       \
              -Wnon-virtual-dtor             \
              -Wold-style-cast               \
              -Wstrict-null-sentinel         \
              -Wsuggest-override             \
              -Wswitch-default               \
              -Wswitch-enum                  \
              -Woverloaded-virtual           \
              -Wuseless-cast                 "

#             -Wzero-as-null-pointer-constant"


ClangOptions=" -stdlib=libc++ -Weverything        \
               -Wno-comma                         \
               -Wno-unused-template               \
               -Wno-sign-conversion               \
               -Wno-exit-time-destructors         \
               -Wno-global-constructors           \
               -Wno-missing-prototypes            \
               -Wno-weak-vtables                  \
               -Wno-padded                        \
               -Wno-double-promotion              \
               -Wno-c++98-compat-pedantic         \
               -Wno-c++11-compat-pedantic         \
               -Wno-c++14-compat-pedantic         \
               -Wno-c++17-compat-pedantic         \
               -Wno-c++20-compat-pedantic         \
               -fdiagnostics-show-category=name   \
                                                  \
               -Wno-zero-as-null-pointer-constant \
               -Wno-ctad-maybe-unsupported        "

CommonOptions="-g0 -O3 -DNDEBUG -pthread -std=c++20 -I./ -DUSING_TOMS_SUGGESTIONS -D__func__=__PRETTY_FUNCTION__"




ClangCommand="clang++ $CommonOptions $ClangOptions"
echo $ClangCommand -include \"${complianceHelperFile_path}\"
clang++ --version
if $ClangCommand -include "${complianceHelperFile_path}" -o "${executableFileName}_clang++"  "${sourceFiles[@]}"; then
  echo -e "\nSuccessfully created  \"${executableFileName}_clang++\""
else
  exit 1
fi

echo ""

GccCommand="g++ $CommonOptions $GccOptions"
echo $GccCommand -include \"${complianceHelperFile_path}\"
g++ --version
if $GccCommand -include "${complianceHelperFile_path}" -o "${executableFileName}_g++"  "${sourceFiles[@]}"; then
   echo -e "\nSuccessfully created  \"${executableFileName}_g++\""
else
   exit 1
fi
