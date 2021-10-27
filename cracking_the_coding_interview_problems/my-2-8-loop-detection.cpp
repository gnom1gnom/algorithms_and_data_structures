/**
 *  Cracking the coding interview, edition 6
 *  Problem 2.8 Loop Detection
 *  Problem : Determine if a linkedlist has a loop. If it has a loop, find the start of loop.
 *  NOTE: I have followed the approach provided in book, however, once I find start of loop,
 *  I remove the loop. So that we can test our solution. Read comment at line 25.
 */

#include <iostream>

using namespace std;

struct Node
{
  int data;
  Node *next;
  Node(int d) : data{d}, next{nullptr} {}
};

void removeLoop(Node *loopNode, Node *prevNode, Node *head)
{
  if (loopNode == head)
  {
    // this list was a circle
    prevNode->next = nullptr;
    cout << "Intersection at " << prevNode->data << std::endl;
    return;
  }

  while (loopNode->next != head->next)
  {
    loopNode = loopNode->next;
    head = head->next;
  }

  loopNode->next = nullptr;

  cout << "Intersection at " << head->next->data << std::endl;
}

bool detectAndRemoveCycle(Node *head)
{
  if (!head || !head->next || !head->next->next)
    return false;

  Node *slow{head};
  Node *prev{head};
  Node *fast{head};

  do
  {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast)
    {
      removeLoop(fast, prev, head);
      return true;
    }
    prev = prev->next;

  } while (fast || slow);

  return false;
}

void insert(Node *&head, int data)
{
  Node *newNode = new Node(data);
  if (head == nullptr)
  {
    head = newNode;
  }
  else
  {
    Node *temp = head;
    while (temp->next != nullptr)
    {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void printList(Node *head)
{
  while (head)
  {
    std::cout << head->data << "-->";
    head = head->next;
  }
  std::cout << "NULL" << std::endl;
}

int main()
{
  Node *head = nullptr;
  insert(head, 1);
  insert(head, 2);
  insert(head, 3);
  insert(head, 4);
  insert(head, 5);
  insert(head, 6);
  std::cout << "Current List:\n";
  printList(head);
  std::cout << "Inserting loop, connecting 6 to 1 \n";
  head->next->next->next->next->next->next = head;
  std::cout << "Detecting and deleting loop\n";
  detectAndRemoveCycle(head);
  std::cout << "Back to the same old list\n";
  printList(head);

  std::cout << "-----------------------" << std::endl;
  std::cout << "Inserting loop, connecting 6 to 2 \n";
  head->next->next->next->next->next->next = head->next;
  std::cout << "Detecting and deleting loop\n";
  detectAndRemoveCycle(head);
  std::cout << "Back to the same old list\n";
  printList(head);

  std::cout << "-----------------------" << std::endl;
  std::cout << "Inserting loop, connecting 6 to 3 \n";
  head->next->next->next->next->next->next = head->next->next;
  std::cout << "Detecting and deleting loop\n";
  detectAndRemoveCycle(head);
  std::cout << "Back to the same old list\n";
  printList(head);

  std::cout << "-----------------------" << std::endl;
  std::cout << "Inserting loop, connecting 6 to 4 \n";
  head->next->next->next->next->next->next = head->next->next->next;
  std::cout << "Detecting and deleting loop\n";
  detectAndRemoveCycle(head);
  std::cout << "Back to the same old list\n";
  printList(head);

  std::cout << "-----------------------" << std::endl;
  std::cout << "Inserting loop, connecting 6 to 5 \n";
  head->next->next->next->next->next->next = head->next->next->next->next;
  std::cout << "Detecting and deleting loop\n";
  detectAndRemoveCycle(head);
  std::cout << "Back to the same old list\n";
  printList(head);

  std::cout << "-----------------------" << std::endl;
  std::cout << "Inserting loop, connecting 6 to 6 \n";
  head->next->next->next->next->next->next = head->next->next->next->next->next;
  std::cout << "Detecting and deleting loop\n";
  detectAndRemoveCycle(head);
  std::cout << "Back to the same old list\n";
  printList(head);

  return 0;
}
