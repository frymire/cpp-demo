
#include "macros.h"
using std::cout;
using std::endl;

// Demonstrate the use of macros.
// See here: https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html
int main() {

    cout << "Let's demonstrate some macros ...\n\n";

    // Standard pre-defined macros
    cout << "Compile date: " << __DATE__ << endl;
    cout << "Source file name: " << __FILE__ << endl;
    cout << "Line number in the source file: " << __LINE__ << endl;
    cout << "The enclosing function name: " << __func__ << endl << endl;

    // Add some specific code depending on the compiler
#if defined (__GNUC__)
    cout << "GNU C compiler version: " << __GNUC__ << "." << __GNUC_MINOR__ << endl;
#endif
#if defined (_MSC_VER)
    cout << "Microsoft Visual Studio compiler version: " << _MSC_VER << endl;
    cout << "Microsoft Visual Studio compiler full version: " << _MSC_FULL_VER << endl << endl;
#endif

    // Add some specific code depending on the platform for which we are compiling.
#if defined (_WIN32)
    cout << "Compiling for at least 32-bit Windows.\n";
#endif
#if defined (_WIN64)
    cout << "Compiling for 64-bit Windows.\n";
#endif
#if defined (__linux__)
    cout << "Compiling for Linux.\n";
#endif
    cout << endl;

    // For the next example, first define a custom compiler symbol under the corresponding target project configuration.
    //   Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions -> {add the name of your symbol, e.g. MY_DEBUG}
    // Here, we'll use the ifdef form of the conditional macro.
#ifdef MY_DEBUG
    cout << "We're in debug mode.\n";
#elif defined(MY_RELEASE)
    cout << "We're in release mode.\n";
#endif

    // You can also set a specific value to a compiler symbol. Do the following for all configurations...
    //   Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions -> { add "MY_VALUE=3" }
    // Or better yet, to set it in CMake put this after the add_executable() line.
    //   target_compile_definitions(macros PUBLIC MY_VALUE=3)
    cout << "MY_VALUE = " << MY_VALUE << endl;

    // You *could* also do this to avoid compiling code, as an alternative to commenting it out.
#if 0
    cout << "This doesn't get compiled.\n" << syntaxError!
#endif

      // You can pass parameters to a macro like this. Also, use backslash *without a trailing space* for multi-line macros. 
      // Don't include the closing semi-colon, so that the macro looks kind of like code when we "call" it.
#define MULTILINE(text) cout << \
text << \
endl

      // Now "call" it (really, paste in the code here).
      MULTILINE("Bye...");

    // You can undefine macros once they're not needed, since macros are generally discouraged anyway.
#undef MULTILINE
    //MULTILINE("Bye..."); // now a compiler error
}
