#include "util/prelude.hpp"

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    // If either list is empty, then there's nothing to do
    if (!list1)
      return list2;
    if (!list2)
      return list1;

    auto popMin = [&]() -> ListNode * {
      ListNode *ret;
      if (list1->val > list2->val) {
        ret = list2;
        list2 = list2->next;
      } else {
        ret = list1;
        list1 = list1->next;
      }
      return ret;
    };

    ListNode *head = popMin();
    ListNode *tail = head;

    while (list1 && list2) {
      tail->next = popMin();
      tail = tail->next;
    }

    // Splice the remaining elements of the last list
    if (list1)
      tail->next = list1;
    else if (list2)
      tail->next = list2;

    return head;
  }
};
