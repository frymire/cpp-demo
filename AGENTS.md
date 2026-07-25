# cpp-demo

Collection of ~60 self-contained C++ example programs (one per feature) under `modules/`, plus two library-linking demos, all driven by the single root `CMakeLists.txt`. There is no product/service, database, server, or automated test suite — "running" means compiling the targets and executing the individual console binaries.

## Cursor Cloud specific instructions

- Compiler: build with **g++-14**. The default `/usr/bin/c++` is clang, which fails to link (`cannot find -lstdc++`), and the preinstalled `g++-13` lacks the C++23 `<print>` header used by several modules (`format`, `generators`, `call-location`, `weak-pointers`, `weak-pointers-cyclical`). `g++-14` compiles the whole tree.
- Configure + build (out-of-source):
  - `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14`
  - `cmake --build build -j"$(nproc)"`
- Executables land in `build/bin/`; the two demo libraries in `build/lib/`. Run e.g. `./build/bin/hello`.
- Path gotcha: the `files` and `optional` demos open `../resources/*.txt` with a relative path, so run them from inside the `build/` directory (`cd build && ./bin/files`). Running from the repo root fails with "Error opening file."
- No lint or test tooling is configured; there is nothing to run beyond compiling and executing the example binaries.
