/*
 * Cracking the coding interview edition 6
 * Problem 2-1 : Remove duplicates from an unsorted linked list.
 * Approach 1 : Naive approach of iterating and remove all further duplicates of current node.
 * 							Space complexity O(1) & time complexity O(n^2)
 * Approach 2: Use a hash table, space complexity O(n), time complexity O(n)
 */

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <random>

using namespace std;

struct Node
{
	int data = 0;
	Node *next = nullptr;
};

/**
 * [insert - insert a node at the head of list]
 * @param head [head of the list]
 * @param data [new node's data]
 */
void insert(Node *&head, int data)
{
	Node *newNode = new Node;
	newNode->data = data;
	newNode->next = head;
	head = newNode;
}

/**
 * [printList Helper routine to print list]
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

// generate a random int between min and max
/**
 * [random_range helper routine to generate a random number between min and max (including)]
 * @param  min [min of range]
 * @param  max [max of range]
 * @return     [A random number between min and max]
 */
static inline int random_range(const int min, const int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(mt);
}

// Method 2
// space complexity - O(n)
// time complexity - O(n)
/**
 * [removeDuplicates1 - Remove duplicates from the list using hash table]
 * @param head [head of list]
 */
void removeDuplicates1(Node *head)
{
	if (head == nullptr || (head && (head->next == nullptr)))
	{
		return;
	}
	std::unordered_map<int, int> node_map;
	Node *prev = head;
	Node *curr = head->next;
	node_map[head->data] = 1;
	while (curr != nullptr)
	{
		while (curr && node_map.find(curr->data) != node_map.end())
		{
			curr = curr->next;
		}
		prev->next = curr;
		prev = curr;
		if (curr)
		{
			node_map[curr->data] = 1;
			curr = curr->next;
		}
	}
}

void removeDuplicatesSet(Node *&head)
{
	unordered_set<int> elementSet;

	if (head == nullptr || head->next == nullptr)
		return;

	// dla każdego elementu w liście
	Node *prev, *current;
	prev = head;
	current = head->next;
	elementSet.insert(head->data);

	while (current)
	{
		if (elementSet.find(current->data) == elementSet.end())
		{
			elementSet.insert(current->data);
			prev = prev->next;
			current = current->next;
		}
		else
		{
			prev->next = current->next;
			Node *duplicate = current;
			current = current->next;
			delete (duplicate);
		}
	}
}

int main()
{
	std::cout << "Method 2 : \n";
	Node *head1 = nullptr;
	for (int i = 0; i < 10; ++i)
	{
		insert(head1, random_range(1, 7));
	}
	printList(head1);
	removeDuplicates1(head1);
	printList(head1);

	std::cout << "Method Set : \n";
	Node *head2 = nullptr;
	for (int i = 0; i < 10; ++i)
	{
		insert(head2, random_range(1, 7));
	}
	printList(head2);
	removeDuplicatesSet(head2);
	printList(head2);
	return 0;
}
