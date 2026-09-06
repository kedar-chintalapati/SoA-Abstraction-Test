### Basic library using C++26 reflection to provide an AoS-like interface over SoA storage. Only the happy path is currently supported.

## Example

```cpp
#include <soa/soa_vector.hpp>

struct TestStruct {
    int f1;
    int f2;
};

soa::vector<TestStruct> test_structs;

test_structs.push_back({1, 2});

test_structs[0].f1 = 3;

// AoS-like access with SoA storage under the hood
```

## Requirements

* GCC 16
* CMake
* Ninja

## Build

```sh
cmake --preset debug
cmake --build --preset debug
```

## Run

```sh
./build/debug/soa_test
```
