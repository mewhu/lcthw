#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

void swap_list_node_with_its_next(List *list, ListNode *cur) {
  if(!cur->prev) {
    // this case means that the current node is the 1st node in the list
    list->first = cur->next;

    cur->next = list->first->next;
    cur->prev = list->first;
    cur->next->prev = cur;

    list->first->next = cur;
    list->first->prev = NULL;
  } else if (!(cur->next)) {
    // this case means that the current node is the last node in the list
    // [Mew] note that this else-if is not practical! Because before enter this condition, for-loop would be "contine;" due to a former "if(!(cur->next))" check
    list->last = cur->prev;

    cur->next = list->last;
    cur->prev = list->last->prev;

    list->last->next = NULL;
    list->last->prev = cur;
  } else {
    ListNode *orig_cur_prev = cur->prev;
    ListNode *orig_cur = cur;
    ListNode *orig_cur_next = cur->next;
    ListNode *orig_cur_next_next = cur->next->next;
    debug("orig_cur_prev : %s", (char *)orig_cur_prev->value);
    debug("orig_cur : %s", (char *)orig_cur->value);
    debug("orig_cur_next : %s", (char *)orig_cur_next->value);
    if(orig_cur_next_next)  debug("orig_cur_next_next : %s", (char *)orig_cur_next_next->value);

    orig_cur_prev->next = orig_cur_next;
    orig_cur_next->prev = orig_cur_prev;

    orig_cur_next->next = orig_cur;
    orig_cur->prev = orig_cur_next;

    if(orig_cur_next_next) {
      orig_cur->next = orig_cur_next_next;
      orig_cur_next_next->prev = orig_cur;
    } else {
      orig_cur->next = NULL;
      list->last = orig_cur;
    }
  }
}

int List_bubble_sort(List *list, List_compare cmp) {
  if(list->count < 2) {
    return 0;
  }

  int is_sorted;
  do {
    is_sorted = 1;
    LIST_FOREACH(list, first, next, cur) {
      if(cur->next) {
        if(cmp(cur->value, cur->next->value) > 0) {
          swap_list_node_with_its_next(list, cur);
          _node = cur->prev;
          is_sorted = 0;
        }
      }
    }
  } while (!is_sorted);

  return 0;
  check(1==1, "system crash");
error:
  return -1;
}

/*
int List_bubble_sort(List *list, List_compare cmp) {
  LIST_FOREACH(list, first, next, cur) {
    debug("cur->value: %s , with node position:%p\n", (char *)cur->value, cur);
  }
  if(list->count == 0) {
    return 0;
  }
  int tmp_final_processed_target_index, tmp_cnt;
  for(int i = 0; i < list->count - 1; i++) {
    debug("---- new iteration round i : %d ----", i);
    ListNode *ptr_for_show = list->first;
    debug("list->last : %s @ %p", (char *)list->last->value, list->last);
    while(ptr_for_show) {
      debug("%s, with node position: %p", (char *)ptr_for_show->value, ptr_for_show);
      ptr_for_show = ptr_for_show->next;
    }
    tmp_final_processed_target_index = list->count - 1 + i;
    tmp_cnt = 0;
    LIST_FOREACH(list, first, next, cur) {
      debug("current node value : %s", (char *)cur->value);
      if(!cur->next) {
        continue;
      } else {
        if(cmp(cur->value, cur->next->value) > 0) {
          swap_list_node_with_its_next(list, cur);
          _node = cur->prev;
          //cur = cur->prev;

          ptr_for_show = list->first;
          debug("after swap");
          while(ptr_for_show) {
            debug("%s", (char *)ptr_for_show->value);
            ptr_for_show = ptr_for_show->next;
          }
          debug("---");
          tmp_cnt++;
          if(tmp_cnt == tmp_final_processed_target_index) {
            continue;
          }
        } else {
          debug("no need to swap");
          ptr_for_show = list->first;
          while(ptr_for_show) {
            debug("%s", (char *)ptr_for_show->value);
            ptr_for_show = ptr_for_show->next;
          }
          debug("---");
        }
      }
    }
    debug("-------");
  }
  check( 1==1, "system crash");
  return 0;
error:;
  return -1;
}
*/


List *List_merge(List *list_left, List *list_right, List_compare cmp) {
  List *res = List_create();
  ListNode *left_one = list_left->first;
  ListNode *right_one = list_right->first;
  int target_size = list_left->count + list_right->count;
  while( res->count < target_size ) {
    if(!left_one) {
      List_push(res, right_one->value);
      right_one = right_one->next;
    } else if (!right_one) {
      List_push(res, left_one->value);
      left_one = left_one->next;
    } else {
      if(cmp(left_one->value,right_one->value) <= 0) {
        List_push(res, left_one->value);
        left_one = left_one->next;
      } else {
        List_push(res, right_one->value);
        right_one = right_one->next;
      }
    }
  }

  return res;
}

List *List_merge_sort(List *list, List_compare cmp) {
  int target_count = list->count;
  List* res = NULL;
  if(target_count < 2) {
    return list;
  }

  List *list_left = List_create();
  List *list_right = List_create();
  int middle = target_count / 2;
  LIST_FOREACH(list, first, next, cur) {
    if(list_left->count < middle) {
      List_push(list_left, cur->value);
    } else {
      List_push(list_right, cur->value);
    }
  }

  List *sorted_left = List_merge_sort(list_left, cmp);
  List *sorted_right = List_merge_sort(list_right, cmp);
  if(sorted_left != list_left)  List_destroy(list_left);
  if(sorted_right != list_right)  List_destroy(list_right);

  res = List_merge(sorted_left, sorted_right, cmp);
  List_destroy(sorted_left);
  List_destroy(sorted_right);

  check(res != NULL, "failed to merge sort");
  return res;
error:
  return NULL;
}
