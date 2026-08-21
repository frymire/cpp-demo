
#pragma once

// Include things here that are probably included in most of the files across your
// project, so that you don't have to recompile them each time they are included.
// Instead, just have all of your files include this header and set up the project
// settings so that they use the precompiled header generated one time for this code.

#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <utility>

#include <string>
#include <stack>
#include <deque>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// Remove Windows-specific headers for Linux.
#ifdef _WIN32
  #include <Windows.h>
#else
  // If needed, add POSIX or Linux-specific includes here.
#endif

// You can also include non-C-standard libraries here, provided you aren't going
// to change them.

// Do NOT put "using namespace ..." commands here. It would pollute your namespace
// across all of the code that includes this header.
