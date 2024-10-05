#include <iostream>
#include <memory>
#include <cassert>

#include "src.hpp"

int main() {
  auto allocator = std::make_unique<sjtu::BuddyAllocator>(64, 4);

  // Step 1
  assert(allocator->malloc_at(0x20, 32) != -1);
  assert(allocator->malloc_at(0x30, 8) == -1);
  std::cout<<1<<std::endl;

  // Step 2
  assert(allocator->malloc_at(0x10, 8) != -1);
  assert(allocator->malloc_at(0x14, 4) == -1);
  std::cout<<1<<std::endl;

  // Step 3
  assert(allocator->malloc_at(0x1c, 4) != -1);
  std::cout<<1<<std::endl;

  // An unimportant step
  assert(allocator->malloc(4) == 0x00);
  allocator->free_at(0x00, 4);
  std::cout<<1<<std::endl;

  // Step 5
  allocator->free_at(0x10, 8);
  std::cout<<1<<std::endl;

  // Step 5
  allocator->free_at(0x1c, 4);
  assert(allocator->malloc_at(0x00, 32) != -1);
  std::cout<<1<<std::endl;

  std::cout << "All tests passed.\n";
  return 0;
}