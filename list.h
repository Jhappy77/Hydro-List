
#ifndef FLOWLIST_H
#define FLOWLIST_H

#include <iostream>
using namespace std;

//stuff
struct ListItem {
int year;
double flow;
};

struct Node{
  ListItem item;
  Node* next;
};

class FlowList {
private:
  //########  DATA MEMBERS ##########
  Node* head;
  int number_records;

  //###### PRIVATE HELPER FUNCTIONS ########
  void destroy();
  //PROMISES: Deletes all members in linklist, sets head to nullptr
  void copy(const FlowList& source);
  //PROMISES: Dynamically copies ths's link list to this' link list in heap.
  void incr_num_records(int x);
  //PROMISES: Increases the value of number_records by x
  int itemA_is_smaller(const ListItem& link_item, const ListItem& compare_me);
  //PROMISES: Returns 1 if compare_me should appear past link_item in link list.
  //Returns 0 otherwise.
  int list_items_are_equal(const ListItem& a, const ListItem& b) const;
  //PROMISES: Returns 1 if a and b are equal. Returns 0 otherwise.
  void print_this_and_next(const Node * thisNode, ostream& my_stream) const;
  //PROMISES: Prints this node and everything after. Helper to print_all_list_items
  void print_list_item(const ListItem& itemA, ostream& my_stream) const;
  //PROMISES: Prints the given ListItem
  double get_flow_sum() const;
  //PROMISES: Gets the sum of all flow values in the link list. Helper to get_avg()
  Node * find_node(int x) const;
  //PROMISES: Returns the node at the xth position in the link list, w/ head = 0th position
  Node * find_year(int y) const;
  //PROMISES: Will find the first instance of a node with item that has y in the linklist.
  //Returns nullptr if it doesnt exist.
  int node_has_year(Node * n, int y) const;
  //PROMISES: Returns 1 if n has year y, returns 0 0therwise.  returns 0 otherwise
  void remove_node(Node * delete_node, Node * previous);
  //PROMISES: Gets 2 nodes: 1 to delete and the previous node. Removes delete node from linklist.
  //If previous is null, it assumes that delete_node is head.


public:
  void remove_node_with_year(int y);
  int list_has_year(int y) const;
  //PROMISES: Returns 1 if linklist has an item with year y, 0 otherwise.
  double get_flow_avg() const;
  //PROMISES: Returns the average flow value of all the values in the link list.
  double get_flow_median() const;
  //PROMISES: Returns the median flow value of the linklist.
  void print_all_list_items(ostream& my_stream = cout) const;
  /*PROMISES: Prints the contents of each item in the linklist in the order they
  are found, to my_stream which is by default cout but can be another location. */
  void insert(const ListItem& insert_item);
  //PROMISES: Inserts a node with insert_item into the link list in appropriate location
  void remove(const ListItem& remove_item);
  //PROMISES: Removes the first node with remove_item as its item in the linklist.

  //######### CONSTRUCTORS & BIG 3 ############
  FlowList();
  ~FlowList();
  FlowList(const FlowList& src);
  FlowList& operator =(const FlowList& rhs);

};

#endif
