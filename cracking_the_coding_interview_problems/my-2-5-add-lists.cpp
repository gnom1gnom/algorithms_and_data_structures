/**
 * Cracking the coding interview edition 6
 * Problem 2.5 Sum lists
 * You have two numbers represented by linked list, where each node contains
 * a single digit. Digits are stored in reverse order.(1's digit is at the head)
 * Write a function that adds two such numbers and returns a number in similar
 * list format.
 * example:
 * 7-->1-->6 + 5-->9-->2 = 2-->1-->9
 * which is (617 + 295  = 912)
 * What if digits are not stored in reverse order(i.e 1's digit is at tail)
 * (6--1-->7) + (2-->9-->5) = (9-->1-->2)
 *
 * Approach:
 * We will solve the problem recursively and iteratively.
 * Add numbers at same digits place, store the 1's digit of the output in new list
 * and add carry in next place's addition.
 *
 * Finally, we will solve the follow up.
 */

#define FMT_HEADER_ONLY

#include <bits/stdc++.h>
#include <fmt/core.h>

using namespace std;

struct Node
{
  int data;
  Node *next;
  Node(int d) : data{d}, next{nullptr} {}
};

/**
 * [insert - insert a new node at head of the list]
 * @param head [head of the list]
 * @param data [new node's data]
 */
void insert(Node *&head, int data)
{
  Node *newNode = new Node(data);
  newNode->next = head;
  head = newNode;
}

void my_insert(Node *&current, int data)
{
  Node *newNode = new Node(data);
  current->next = newNode;
  current = newNode;
}

/**
 * [printList - print the list]
 * @param head [head of the list]
 */
void printList(Node *head)
{
  while (head)
  {
    std::cout << head->data << "-->";
    head = head->next;
  }
  std::cout << "nullptr" << std::endl;
}

/**
 * [add_iterative iterative approach to add two given lists]
 * @param  list1
 * @param  list2
 * @return list3
 */
Node *add_iterative(Node *list1, Node *list2)
{
  if (list1 == nullptr)
  {
    return list2;
  }
  if (list2 == nullptr)
  {
    return list1;
  }

  // list3 will store result
  Node *list3 = nullptr;
  // for adding new nodes to tail of list3
  Node *list3Tail = nullptr;

  int value = 0, carry = 0;

  while (list1 || list2)
  {
    // add the values, if one of the list has already been traversed, add 0
    value = carry + (list1 ? list1->data : 0) + (list2 ? list2->data : 0);

    // get the new value and carry
    if (value > 9)
    {
      carry = 1;
      value = value % 10;
    }
    else
    {
      carry = 0;
    }

    // new node
    Node *temp = new Node(value);

    // if this is the first node, populate the result, else add to the tail
    if (list3 == nullptr)
    {
      list3 = temp;
    }
    else
    {
      list3Tail->next = temp;
    }

    // make new tail
    list3Tail = temp;

    if (list1)
    {
      list1 = list1->next;
    }

    if (list2)
    {
      list2 = list2->next;
    }
  }

  if (carry > 0)
  {
    list3Tail->next = new Node(carry);
  }
  return list3;
}

/**
 * [add_recursive - recursive addititon of two lists
 * @param  list1
 * @param  list2
 * @param  carry
 * @return list3
 */
Node *add_recursive(Node *list1, Node *list2, int carry)
{
  if (list1 == nullptr && list2 == nullptr && carry == 0)
  {
    return nullptr;
  }
  int value = carry;
  if (list1)
  {
    value += list1->data;
  }
  if (list2)
  {
    value += list2->data;
  }

  Node *resultNode = new Node(value % 10);

  resultNode->next = add_recursive(list1 ? (list1->next) : nullptr,
                                   list2 ? (list2->next) : nullptr,
                                   value > 9 ? 1 : 0);
  return resultNode;
}

/**
 *  Follow up part:
 *  Lists are stored such that 1's digit is at the tail of list.
 *  617 ==> 6 --> 1 --> 7
 *  295 ==> 2 --> 9 --> 5
 */

/**
 * [padList - Helper routine for padding the shorter list]
 * @param list    [Current list]
 * @param padding [number of padding required]
 */
void padList(Node *&list, int padding)
{
  for (int i = 0; i < padding; ++i)
  {
    insert(list, 0);
  }
}

/**
 * [length - helper routine to return length of list]
 * @param  head [list's head]
 * @return length of the list
 */
int length(Node *head)
{
  int len = 0;
  while (head)
  {
    len++;
    head = head->next;
  }
  return len;
}

Node *add_followup_helper(Node *list1, Node *list2, int &carry)
{
  if (list1 == nullptr && list2 == nullptr && carry == 0)
  {
    return nullptr;
  }

  Node *result = add_followup_helper(list1 ? (list1->next) : nullptr,
                                     list2 ? (list2->next) : nullptr,
                                     carry);

  int value = carry + (list1 ? list1->data : 0) + (list2 ? list2->data : 0);
  insert(result, value % 10);
  carry = (value > 9) ? 1 : 0;
  return result;
}

/**
 * [add_followup - adding list such that 1's digit is at tail( follow up part of question)
 * @param  list1
 * @param  list2
 * @return list3 representing sum of list1 and list2
 */
Node *add_followup(Node *list1, Node *list2)
{
  int len1 = length(list1);
  int len2 = length(list2);

  // pad the smaller list
  if (len1 > len2)
  {
    padList(list2, len1 - len2);
  }
  else
  {
    padList(list1, len2 - len1);
  }
  int carry = 0;
  Node *list3 = add_followup_helper(list1, list2, carry);
  if (carry)
  {
    insert(list3, carry);
  }
  return list3;
}

/**
 * [deleteList Helper routine to delete list]
 * @param head [head of the list]
 */
void deleteList(Node *&head)
{
  Node *nextNode;
  while (head)
  {
    nextNode = head->next;
    delete (head);
    head = nextNode;
  }
}

Node *my_add(Node *list1, Node *list2)
{
  long nbone{0}, nbtwo{0}, sum{0}, firstDig{0};
  Node *head = new Node(0);
  Node *current = head;
  bool mt9 = false; // true jeśli z poprzedniego dodawanie przekroczyliśmy 9

  while (list1 || list2)
  {
    nbone = 0, nbtwo = 0;
    if (list1)
    {
      nbone = list1->data;
      list1 = list1->next;
    }
    if (list2)
    {
      nbtwo = list2->data;
      list2 = list2->next;
    }
    if (mt9)
      sum = current->data + nbone + nbtwo;
    else
      sum = nbone + nbtwo;

    if (sum > 9)
    {
      firstDig = sum % 10;
      current->data = firstDig;
      mt9 = true;
      my_insert(current, 1);
    }
    else
    {
      current->data = sum;
      mt9 = false;

      // jeśli będziemy jeszcze dodawać
      if (list1 || list2)
        my_insert(current, 0);
    }
  }

  return head;
}

Node *my_add2(Node *list1, Node *list2)
{
  long nbone{0}, nbtwo{0}, dec{0};

  while (list1 || list2)
  {
    if (list1)
    {
      nbone += list1->data * pow(10, dec);
      list1 = list1->next;
    }
    if (list2)
    {
      nbtwo += list2->data * pow(10, dec);
      list2 = list2->next;
    }
    dec++;
  }

  int sum = nbone + nbtwo;
  dec--;

  Node *head = nullptr;
  while (dec >= 0)
  {
    Node *temp = new Node(sum / pow(10, dec));
    sum -= temp->data * pow(10, dec);

    if (head)
      temp->next = head;
    head = temp;

    dec--;
  }

  return head;
}

pair<int, int> getNumberRecur(Node *list)
{
  if (!list)
    return make_pair(0, 0);

  // decimal, sum
  pair<int, int> result;
  if (list->next)
    result = getNumberRecur(list->next);

  int num = list->data * pow(10, result.first);
  return make_pair(result.first + 1, result.second + num);
}

Node *my_add_recursive2(Node *list1, Node *list2)
{
  // decimal, number
  pair<int, int> nbone = getNumberRecur(list1);
  pair<int, int> nbtwo = getNumberRecur(list2);

  int sum = nbone.second + nbtwo.second;
  int dec = max(nbone.first, nbtwo.first);

  Node *head = nullptr;
  Node *prev = nullptr;
  while (dec >= 0)
  {
    Node *temp = new Node(sum / pow(10, dec));
    sum -= temp->data * pow(10, dec);

    if (!head)
    {
      head = temp;
      prev = temp;
    }

    prev->next = temp;
    prev = temp;

    dec--;
  }

  return head;
}

int main()
{
  // making list 1 for number 617
  Node *list1 = nullptr;
  insert(list1, 6);
  insert(list1, 1);
  insert(list1, 7);
  std::cout << "List1:  ";
  printList(list1);

  // making list2 for number 295
  Node *list2 = nullptr;
  insert(list2, 3);
  insert(list2, 9);
  insert(list2, 5);
  std::cout << "List2:  ";
  printList(list2);

  Node *list3 = add_iterative(list1, list2);
  std::cout << "Iterative Solution: \n";
  std::cout << "List3:  ";
  printList(list3);

  Node *list4 = add_recursive(list1, list2, 0);
  std::cout << "Recursive Solution: \n";
  std::cout << "List4:  ";
  printList(list4);

  Node *list5 = my_add(list1, list2);
  std::cout << "My Solution: \n";
  std::cout << "List5:  ";
  printList(list5);

  deleteList(list1);
  deleteList(list2);
  deleteList(list3);
  deleteList(list4);
  deleteList(list5);

  std::cout << "\n\nNow follow up case, lists are stored such that 1's digit is at the tail of list\n";
  // Node * listx = nullptr;
  insert(list1, 4);
  insert(list1, 3);
  insert(list1, 2);
  insert(list1, 9);
  std::cout << "List1:  ";
  printList(list1);

  insert(list2, 9);
  insert(list2, 9);
  insert(list2, 8);
  std::cout << "List2:  ";
  printList(list2);

  list3 = add_followup(list1, list2);
  std::cout << "Adding two above lists\n";
  std::cout << "List3:  ";
  printList(list3);

  list5 = add_followup(list1, list2);
  std::cout << "My solution\n";
  std::cout << "List5:  ";
  list5 = my_add_recursive2(list1, list2);
  printList(list5);

  deleteList(list1);
  deleteList(list2);
  deleteList(list3);

  return 0;
}
