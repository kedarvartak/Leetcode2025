// Definition for singly-linked list (assuming it's not provided elsewhere)
#include <iostream>
#include <vector>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
Detecting a Cycle in a Linked List (Floyd's Tortoise and Hare Algorithm)

Concept:
This algorithm uses two pointers, often called `slow` (tortoise) and `fast` (hare),
which move through the linked list at different speeds.
- `slow` pointer moves one step at a time.
- `fast` pointer moves two steps at a time.

If there is a cycle in the linked list, the `fast` pointer will eventually catch up to
the `slow` pointer. This is because the `fast` pointer gains one node on the `slow` pointer
per iteration within the cycle. If there is no cycle, the `fast` pointer (or `fast->next`)
will reach the end of the list (nullptr).

How it Works:
1. Initialization: Both `slow` and `fast` pointers are initialized to the head of the list.
2. Traversal: The pointers traverse the list. In each step:
   - `slow` moves to `slow->next`.
   - `fast` moves to `fast->next->next`.
3. Collision Check: After each move, check if `slow == fast`.
   - If they meet, a cycle is detected.
4. End Condition: The loop continues as long as `fast` and `fast->next` are not `nullptr`.
   If `fast` or `fast->next` becomes `nullptr`, it means the end of the list has been reached
   without the pointers meeting, so there is no cycle.

Visual Example:
List: 1 -> 2 -> 3 -> 4 -> 5 -> 3 (cycle starts at node 3, 5 points back to 3)
Head = 1

Initial: slow = 1, fast = 1

Step 1:
  slow = 2 (1->next)
  fast = 3 (1->next->next)
  slow != fast

Step 2:
  slow = 3 (2->next)
  fast = 5 (3->next->next)
  slow != fast

Step 3:
  slow = 4 (3->next)
  fast = 4 (5->next->next, which is 3->next)
  slow == fast! Cycle detected.

Why they meet if there's a cycle:
- Think of a circular track. If one runner is twice as fast as another, the faster runner
  will eventually lap the slower runner.
- The distance between `slow` and `fast` decreases by one node (relative to their positions
  within the cycle) each time `fast` moves two steps and `slow` moves one.

Time Complexity:
- O(N), where N is the number of nodes in the list.
  - If no cycle: `fast` pointer traverses the list once.
  - If cycle: Let k be the number of nodes before the cycle starts, and C be the length of the cycle.
    The `slow` pointer enters the cycle after k steps. The `fast` pointer is 2k steps from the head.
    The distance of `fast` from `slow` within the cycle is (2k - k) % C = k % C.
    `fast` gains one node on `slow` per step. They will meet after C - (k % C) steps within the cycle.
    Total steps for `slow` is k + C - (k % C), which is O(N).

Space Complexity:
- O(1) - The algorithm uses only a constant amount of extra space for the two pointers.

Edge Cases:
- Empty list (head == nullptr): No cycle.
- Single node list (head->next == nullptr): No cycle.
- List with two nodes, no cycle.
- List with two nodes, forming a cycle.

Alternative Approach (Using Hash Set):
1. Traverse the list, adding each node's memory address to a hash set.
2. If a node is encountered that is already in the hash set, a cycle is detected.
3. If the end of the list is reached (nullptr), there is no cycle.
   - Time Complexity: O(N) on average (due to hash set operations).
   - Space Complexity: O(N) in the worst case (to store all nodes if no cycle or cycle is at the end).
   Floyd's algorithm is generally preferred due to its O(1) space complexity.
*/

class Solution {
public:
    bool hasCycle(ListNode *head) {
        // Handle edge cases: empty list or single node list
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        // Traverse the list with two pointers
        // The loop condition `fast != nullptr && fast->next != nullptr` is crucial:
        // - `fast != nullptr`: Ensures `fast` itself is valid before trying to access `fast->next`.
        // - `fast->next != nullptr`: Ensures `fast->next` is valid before trying to access `fast->next->next`.
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;         // Tortoise moves one step
            fast = fast->next->next;   // Hare moves two steps

            // If the pointers meet, a cycle is detected
            if (slow == fast) {
                return true;
            }
        }

        // If the loop finishes, it means `fast` (or `fast->next`) reached nullptr,
        // so no cycle was found.
        return false;
    }

    // Alternative solution using a Hash Set
    // Time Complexity: O(N)
    // Space Complexity: O(N)
    bool hasCycleHashSet(ListNode *head) {
        unordered_set<ListNode*> visited_nodes;
        ListNode* current = head;
        while (current != nullptr) {
            if (visited_nodes.count(current)) {
                // Node already visited, cycle detected
                return true;
            }
            visited_nodes.insert(current);
            current = current->next;
        }
        return false; // Reached end of list, no cycle
    }
};

// Helper function to create a list with a possible cycle for testing
// `nodes_val`: vector of values for nodes
// `cycle_pos`: 0-based index of the node where the tail connects to, or -1 for no cycle.
ListNode* createListWithCycle(const std::vector<int>& nodes_val, int cycle_pos) {
    if (nodes_val.empty()) {
        return nullptr;
    }
    ListNode* head = new ListNode(nodes_val[0]);
    ListNode* current = head;
    std::vector<ListNode*> node_refs;
    node_refs.push_back(head);

    for (size_t i = 1; i < nodes_val.size(); ++i) {
        current->next = new ListNode(nodes_val[i]);
        current = current->next;
        node_refs.push_back(current);
    }

    if (cycle_pos != -1 && cycle_pos < (int)nodes_val.size()) {
        if (current != nullptr) { // current is the tail
             current->next = node_refs[cycle_pos];
        }
    }
    return head;
}

// Helper function to print list (beware of infinite loops with cycles if not handled)
// void printList(ListNode* head, int limit = 20) {
//     ListNode* current = head;
//     int count = 0;
//     while (current != nullptr && count < limit) {
//         std::cout << current->val << " -> ";
//         current = current->next;
//         count++;
//     }
//     if (current != nullptr && count == limit) {
//         std::cout << "... (list may be longer or cyclic)";
//     }
//     std::cout << "nullptr" << std::endl;
// }

// int main() {
//     Solution sol;

//     // Test Case 1: No cycle
//     ListNode* list1 = createListWithCycle({1, 2, 3, 4, 5}, -1);
//     std::cout << "List 1 (1->2->3->4->5->nullptr):\n";
//     // printList(list1);
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list1) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list1) ? "Yes" : "No") << std::endl << std::endl;

//     // Test Case 2: Cycle present
//     // 1 -> 2 -> 3 -> 4 -> 5
//     //           ^         |
//     //           |_________|
//     ListNode* list2 = createListWithCycle({1, 2, 3, 4, 5}, 2); // Tail (5) points to index 2 (node with value 3)
//     std::cout << "List 2 (1->2->3->4->5->3...):\n";
//     // printList(list2);
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list2) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list2) ? "Yes" : "No") << std::endl << std::endl;

//     // Test Case 3: Empty list
//     ListNode* list3 = createListWithCycle({}, -1);
//     std::cout << "List 3 (empty):\n";
//     // printList(list3);
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list3) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list3) ? "Yes" : "No") << std::endl << std::endl;

//     // Test Case 4: Single node, no cycle
//     ListNode* list4 = createListWithCycle({1}, -1);
//     std::cout << "List 4 (1->nullptr):\n";
//     // printList(list4);
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list4) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list4) ? "Yes" : "No") << std::endl << std::endl;

//     // Test Case 5: Single node, cycle to itself
//     ListNode* list5 = createListWithCycle({1}, 0);
//     std::cout << "List 5 (1->1...):\n";
//     // printList(list5);
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list5) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list5) ? "Yes" : "No") << std::endl << std::endl;
    
//     // Test Case 6: Two nodes, no cycle
//     ListNode* list6 = createListWithCycle({1, 2}, -1);
//     std::cout << "List 6 (1->2->nullptr):\n";
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list6) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list6) ? "Yes" : "No") << std::endl << std::endl;

//     // Test Case 7: Two nodes, fast pointer starts on slow pointer
//     ListNode* list7_node2 = new ListNode(2);
//     ListNode* list7_node1 = new ListNode(1, list7_node2);
//     list7_node2->next = list7_node1; // 2 points back to 1
//     std::cout << "List 7 (1->2->1...):\n";
//     std::cout << "Has cycle (Floyd's): " << (sol.hasCycle(list7_node1) ? "Yes" : "No") << std::endl;
//     std::cout << "Has cycle (HashSet): " << (sol.hasCycleHashSet(list7_node1) ? "Yes" : "No") << std::endl << std::endl;

//     // Clean up memory (important for non-trivial tests, but complex with cycles)
//     // For simple tests like above, a full cleanup might be omitted for brevity in examples.
//     // Proper cleanup would require breaking the cycle first, then deleting nodes.
//     // delete list1; // requires iterating and deleting if no cycle
//     // ... and so on for other lists, being careful with cycles.

//     return 0;
// }
