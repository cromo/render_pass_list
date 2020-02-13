#ifndef RENDER_PASS_LIST_H
#define RENDER_PASS_LIST_H

#include <cstddef>
#include <algorithm>
#include <array>

template<typename T, std::size_t N>
class RenderPassList
{
public:
  RenderPassList() {}

  bool push(int value) {
    if (heap_size_ < list_.size())
    {
      list_[heap_size_++] = value;
      return true;
    }
    return false;
  }

  size_t heap_size() const {
    return heap_size_;
  }

  T const& heap(size_t index) const {
    return list_[index];
  }

  void heapify() {
    for (size_t i = (heap_size_ - 1) >> 1; 0 < i; --i) {
      sift_down(i);
    }
    sift_down(0);
  }

  T const& sort_one() {
    T const root = list_[0];
    list_[0] = list_[--heap_size_];
    sift_down(0);
    list_[N - 1 - pass_size_] = root;
    fully_rendered_[pass_size_] = false;
    return list_[N - 1 - pass_size_++];
  }

  size_t pass_list_size() const {
    return pass_size_;
  }

  T const& pass_list(size_t const index) const {
    return list_[N - 1 - index];
  }

  void mark_as_rendered(size_t const index) {
    fully_rendered_[index] = true;
  }

  void sweep() {
    size_t new_size{0};
    for (size_t i = 0; i < pass_size_; ++i) {
      if (!fully_rendered_[i]) {
        if (i != new_size) {
          list_[N - 1 - new_size++] = list_[N - 1 - i];
        }
      }
    }
    for (size_t i = 0; i < new_size; ++i) {
      fully_rendered_[i] = false;
    }
    pass_size_ = new_size;
  }

  void clear() {
    heap_size_ = 0;
    pass_size_ = 0;
  }

private:
  void sift_down(size_t const root) {
    size_t const left = 2 * root + 1;
    size_t const right = left + 1;
    size_t smallest = root;

    if (left < heap_size_ && list_[left] < list_[smallest]) {
      smallest = left;
    }
    if (right < heap_size_ && list_[right] < list_[smallest]) {
      smallest = right;
    }
    if (smallest != root) {
      std::swap(list_[root], list_[smallest]);
      sift_down(smallest);
    }
  }

  std::array<T, N> list_{};
  size_t heap_size_{0};
  size_t pass_size_{0};
  std::array<bool, N> fully_rendered_{};
};

#endif  // RENDER_PASS_LIST_H
