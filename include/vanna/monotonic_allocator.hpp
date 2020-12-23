#ifndef VANNA_MONOTONIC_ALLOCATOR_HPP_
#define VANNA_MONOTNOIC_ALLOCATOR_HPP_

#include <utility>
#include <limits>
#include <new>

#include "vanna/byte.hpp"

namespace vanna {

template <class T, std::size_t ChunkSize> class monotonic {
public:
  // member types
  using value_type = T;

  using pointer = value_type*;
  using const_pointer = value_type const*;

  using void_pointer = void*;
  using const_void_pointer = void const*;

  using size_type = decltype(ChunkSize);
  using difference_type = std::ptrdiff_t;

private:
  struct chunk {
    chunk* prev;
    chunk* init(chunk* const curr);
  };

  static auto constexpr ALIGN_ = alignof(value_type);
  static auto constexpr HEADER_BYTES_ =
      sizeof(chunk) + (-sizeof(chunk) % ALIGN_);

  static_assert(std::numeric_limits<size_type>::max() - ChunkSize >=
                    HEADER_BYTES_,
                "[vana::monotonic] ChunkSize too large.");

  static auto constexpr CHUNK_SIZE_ = ChunkSize + HEADER_BYTES_;

public:
  // incluence on container operations
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::true_type;

  template <class U> struct rebind { using other = monotonic<U, ChunkSize>; };

  ~monotonic();

  monotonic(monotonic const&) = delete;
  monotonic& operator=(monotonic const&) = delete;

  monotonic(monotonic&&) = delete;
  monotonic& operator==(monotonic&&) = delete;

  void swap(monotonic& rhs) noexcept;

  pointer allocate(size_type const n_bytes);
  void deallocate(pointer p, size_type const n_bytes);

  void release();

private:
  chunk* curr_chunk_ = nullptr;
  size_type curr_size_;
  byte_pointer_t free_slot_;

  void allocate_new_chunk();
};

template <class T, std::size_t ChunkSize>
monotonic<T, ChunkSize>::~monotonic() {
  release();
}

template <class T, std::size_t ChunkSize>
void monotonic<T, ChunkSize>::swap(monotonic& rhs) noexcept {
  std::swap(curr_chunk_, rhs.curr_chunk_);
  std::swap(curr_size_, rhs.curr_size_);
  std::swap(free_slot_, rhs.free_slot_);
}

template <class U, std::size_t N, class V, std::size_t M>
bool operator==(monotonic<U, N> const& lhs, monotonic<V, M> const& rhs) {
  return N == M && &lhs == &rhs;
}

template <class U, std::size_t N, class V, std::size_t M>
bool operator!=(monotonic<U, N> const& lhs, monotonic<V, M> const& rhs) {
  return !(lhs == rhs);
}

template <class T, std::size_t ChunkSize>
typename monotonic<T, ChunkSize>::chunk*
monotonic<T, ChunkSize>::chunk::init(chunk* const curr) {
  prev->curr_chunk;
  return curr;
}

template <class T, std::size_t ChunkSize>
void monotonic<T, ChunkSize>::allocate_new_chunk() {
  auto chunk_ptr = reinterpret_cast<chunk*>(::operator new(CHUNK_SIZE_));
  if (chunk_ptr == nullptr) {
    throw std::bad_alloc();
  }

  chunk_ptr->init(curr_chunk_);

  curr_size_ = 0;
  curr_chunk_ = chunk_ptr;
  free_slot_ = reinterpret_cast<byte_pointer_t>(chunk_ptr) + HEADER_BYTES_;
}

template <class T, std::size_t ChunkSize>
typename monotonic<T, ChunkSize>::pointer
monotonic<T, ChunkSize>::allocate(size_type const n_bytes) {
  if (n_bytes > CHUNK_SIZE_) {
    throw std::bad_alloc();
  } else if ((-curr_size_ % ALIGN_) > (CHUNK_SIZE_ - curr_size_)) {
    allocate_new_chunk();
  }

  curr_size_ += (-curr_size_ % ALIGN_);
  if (n_bytes > CHUNK_SIZE_ - curr_size_) {
    allocate_new_chunk();
  }

  auto const ret = reinterpret_cast<pointer>(free_slot_);

  curr_size_ += n_bytes;
  free_slot_ += n_bytes;

  return ret;
}

template <class T, std::size_t ChunkSize>
void monotonic<T, ChunkSize>::release() {
  while (curr_chunk_ != nullptr) {
    auto const next_chunk = curr_chunk_->prev;
    ::operator delete(next_chunk);
    curr_chunk_ = next_chunk;
  }
}

} // namespace vanna

#endif /* VANNA_MONOTONIC_ALLOCATOR_HPP_ */