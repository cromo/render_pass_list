#include "render_pass_list.h"

#include <cstdio>

bool new_render_pass_lists_are_empty() {
  RenderPassList<int, 16> list{};
  return list.heap_size() == 0 && list.pass_list_size() == 0;
}

bool push_adds_to_heap() {
  RenderPassList<int, 16> list{};
  list.push(8);
  return list.heap_size() == 1;
}

bool heapify_of_one_element_leaves_it_in_place() {
  RenderPassList<int, 16> list{};
  list.push(8);
  list.heapify();
  return list.heap_size() == 1 && list.heap(0) == 8;
}

bool heapify_of_two_heaped_elements_leaves_it_in_place() {
  RenderPassList<int, 16> list{};
  list.push(3);
  list.push(7);
  list.heapify();
  return list.heap(0) == 3 && list.heap(1) == 7;
}

bool heapify_of_two_unheaped_elements_makes_a_heap() {
  RenderPassList<int, 16> list{};
  list.push(7);
  list.push(3);
  list.heapify();
  return list.heap(0) == 3 && list.heap(1) == 7;
}

bool heapify_of_three_unheaped_elements_with_smallest_left_child_makes_it_the_root() {
  RenderPassList<int, 16> list{};
  list.push(9);
  list.push(5);
  list.push(8);
  list.heapify();
  return list.heap(0) == 5;
}

bool heapify_of_three_unheaped_elements_with_smallest_right_child_makes_it_the_root() {
  RenderPassList<int, 16> list{};
  list.push(9);
  list.push(8);
  list.push(5);
  list.heapify();
  return list.heap(0) == 5;
}

bool sort_one_removes_an_element_from_the_heap() {
  RenderPassList<int, 16> list{};
  list.push(8);
  list.sort_one();
  return list.heap_size() == 0;
}

bool sort_one_moves_an_element_to_the_pass_list() {
  RenderPassList<int, 16> list{};
  list.push(8);
  list.sort_one();
  return list.pass_list_size() == 1 && list.pass_list(0) == 8;
}

bool calling_sort_one_multiple_times_moves_multiple_items_from_the_heap_to_the_pass_list() {
  RenderPassList<int, 16> list{};
  list.push(9);
  list.push(8);
  list.push(5);
  list.heapify();
  list.sort_one();
  list.sort_one();
  list.sort_one();
  return list.heap_size() == 0 &&
      list.pass_list_size() == 3 &&
      list.pass_list(0) == 5 &&
      list.pass_list(1) == 8 &&
      list.pass_list(2) == 9;
}

bool marked_entries_are_removed_after_sweeping() {
  RenderPassList<int, 16> list{};
  list.push(9);
  list.push(8);
  list.push(5);
  list.heapify();
  list.sort_one();
  list.sort_one();
  list.sort_one();
  list.mark_as_rendered(0);
  list.mark_as_rendered(2);
  list.sweep();
  return list.pass_list_size() == 1 &&
      list.pass_list(0) == 8;
}

#define TEST(test) do { \
    bool result = test(); \
    std::printf("%s %s\n", result ? "ok" : "not ok", #test); \
  } while(false);

int main() {
  TEST(new_render_pass_lists_are_empty);
  TEST(push_adds_to_heap);
  TEST(heapify_of_one_element_leaves_it_in_place);
  TEST(heapify_of_two_heaped_elements_leaves_it_in_place);
  TEST(heapify_of_two_unheaped_elements_makes_a_heap);
  TEST(heapify_of_three_unheaped_elements_with_smallest_left_child_makes_it_the_root);
  TEST(heapify_of_three_unheaped_elements_with_smallest_right_child_makes_it_the_root);
  TEST(sort_one_removes_an_element_from_the_heap);
  TEST(sort_one_moves_an_element_to_the_pass_list);
  TEST(calling_sort_one_multiple_times_moves_multiple_items_from_the_heap_to_the_pass_list);
  TEST(marked_entries_are_removed_after_sweeping);
  return 0;
}