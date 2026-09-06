Basic library using C++26 reflection to make AoS-like abstraction over SoA layout. Only happy path supported.

#Example Usage:

struct TestStruct {
  int f1;
  int f2;
};


soa::vector<TestStruct> test_structs;

test_structs.push_back({1, 2});

test_structs[0].x = 3;

// Reflection allows us to write AoS-like code like this, while 
// under the hood using an SoA layout.

#Requirements:

- gcc 16
- CMake
- Ninja


#Build:

cmake --preset debug

cmake --build --preset debug


#Run example:

./build/debug/soa_test
