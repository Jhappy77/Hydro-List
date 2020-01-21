#include <iostream>
#include <stdlib.h>
using namespace std;
#include "list.h"

//SECTION 1: Constructors, Copy Constructors, Assignment Operators, Destructors

FlowList& FlowList::operator =(const FlowList& rhs)
{
  if (this != &rhs)
  {
    destroy();
    copy(rhs);
    number_records = rhs.number_records;
  }
  return *this;
}

FlowList::FlowList(const FlowList& src)
{
  number_records = src.number_records;
  copy(src);
}

FlowList::~FlowList()
{
  destroy();
}

FlowList::FlowList():head(0), number_records(0)
{}



//########### SECTION 2: Public helper functions #############################




void FlowList::insert(const ListItem& insert_item)
{
  if (!head || (!itemA_is_smaller(head->item, insert_item))) // If new node should be head
  {
    Node * temp = head;
    head = new Node;
    head -> item = insert_item;
    head -> next = temp;
  }
  else //If head isnt null.
  {
    Node * current = head->next;
    Node * previous = head;

    //Cycles through until first possible location for insert_item is found.
    while(current)
    {
      if(!itemA_is_smaller(current->item, insert_item))
        break;
      previous = current;
      current = current ->next;
    }
    Node * new_node = new Node;
    new_node -> item = insert_item;
    new_node-> next = current;
    previous -> next = new_node;

  }
incr_num_records(1);
return;
}


void FlowList::remove(const ListItem& remove_item)
{
  //REQUIRES: FlowList does not contain the desired item more than once.
  //PROMISES: Deletes the node in the link list that contains this item.
  //Arranges the surrounding pointers to preserve the remainder of the Link list.
  // if list is empty, do nothing
    Node * current_node = head;
    Node * previous_node = nullptr;
    while(current_node)
    {
      if(list_items_are_equal(remove_item, current_node->item))
      {
        remove_node(current_node, previous_node);
        break;
      }
      previous_node = current_node;
      current_node = current_node->next;
    }
}

void FlowList::incr_num_records(int x)
{
  number_records += x;
}

void FlowList::print_all_list_items(ostream& my_stream) const
{
  print_this_and_next(head, my_stream);
}

double FlowList::get_flow_avg() const
{
  return get_flow_sum()/((double)number_records);
}

double FlowList::get_flow_median() const
{
  if(number_records%2) // If number_records is an odd number
  {
    return find_node(number_records/2)->item.flow;
  }
  else //If number_records is an even number.
    return (find_node(number_records/2)-> item.flow + find_node((number_records/2)-1)->item.flow)/2;
}

int FlowList::list_has_year(int y) const
{
    if(find_year(y))
      return 1;
    else
      return 0;
}

void FlowList::remove_node_with_year(int y)
{
  Node * n = find_year(y);
  if (!n) //If find_year returns null
  {
    cout << "\n No node with year = " << y << " was found. Removal failed.";
    return;
  }
  remove(n->item);
  cout << "\n Record was successfully removed.";
  return;
}



//###########  SECTION 3: Private helper functions ###########################




void FlowList::destroy()
{
  //PROMISES: Deletes all nodes in the link list.
  if(!head) //If head is blank return.
    return;
  else
  {
    Node * this_node = head;
    while(this_node)
    {
      Node * next_node = this_node -> next;
      delete this_node;
      this_node = next_node;
    }
    head = 0;
    return;
  }
}

void FlowList::copy(const FlowList& source)
{
//PROMISES: Dynamically copies the link list FlowList from the source into a new
//exact copy in the Heap without modifying the original.

    Node *current = source.head; //"current" is the node pointer that runs through source FlowList's nodes
    Node *new_prev = nullptr; //Points to the most recently copied node in new FlowList
    if (current == NULL)
      head = nullptr;
    else
    {
      //Creates new head node
      head = new Node;
      head -> item = current->item;
      head -> next = nullptr;
      //Prepares for loop
      new_prev = head;
      current = current->next;

      //Loops through, dynamically copies exact link list until it has reached
      //the tail of the original source.
      while(current)
      {
        Node * new_node = new Node;
        new_node->next = nullptr;
        new_node->item = current->item;
        new_prev->next = new_node;
        new_prev = new_node;
        current = current->next;
      }
    }
    return;
}

int FlowList::itemA_is_smaller(const ListItem& itemA, const ListItem& itemB)
{
//PROMISES: Returns 1 if itemA is considered "smaller" than itemB
//This is the case if  its A's flow is smaller, or if the flow is the same and
// B's year is larger.
// Smaller Items should appear first on the linklist.
if(list_items_are_equal(itemA, itemB))
  return 0;
if(itemA.flow == itemB.flow)
{
  if(itemB.year > itemA.year)
    return 1;
  else return 0;
}
else if (itemA.flow < itemB.flow)
  return 1;
else return 0;
}

int FlowList::list_items_are_equal(const ListItem& a, const ListItem& b) const
{
  if ((a.year == b.year)&&(a.flow == b.flow))
    return 1;
  else
    return 0;
}

void FlowList::print_this_and_next(const Node * thisNode, ostream& my_stream) const
{
  //PROMISES: Prints this node and everything after.
  //Helper function to print_all_list_items through recursion.
  print_list_item(thisNode -> item, my_stream);
  if (thisNode -> next != nullptr)
    print_this_and_next(thisNode -> next, my_stream);
}

void FlowList::print_list_item(const ListItem& itemA, ostream& my_stream) const
{
  //PROMISES: Prints the given ListItem
  my_stream << "\n  " << itemA.year << "\t \t \t" << itemA.flow;
}

double FlowList::get_flow_sum() const
{
  double sum = 0;
  Node * my_node = head;
  while(my_node)
  {
    sum += my_node->item.flow;
    my_node = my_node -> next;
  }
  return sum;
}

Node * FlowList::find_node(int x) const
{
  //PROMISES: Returns the xth node in the link list, with the head being the
  //zeroth node. Returns a null pointer if the xth node doesn't exist.
  //REQUIRES: The link list is properly constructed, with no unexpected nullptrs.
  if (x >= number_records)
    return nullptr;
  else
  {
    Node * the_node = head;
    for(int i = 0; i<x; i++)
      the_node = the_node -> next;
    return the_node;
  }
}

Node * FlowList::find_year(int y) const
{
  Node * matching_node = nullptr;
  Node * check_this = head;
  while(check_this)
  {
    if (node_has_year(check_this, y))
      matching_node = check_this;
    check_this = check_this ->next;
  }
  return matching_node;
}

int FlowList::node_has_year(Node * n, int y) const
{
  return (n->item.year == y) ? 1 : 0;
}

void FlowList::remove_node(Node * delete_node, Node * previous)
{
//PROMISES: Gets 2 nodes: 1 to delete and the previous node. Removes delete
//node from linklist. If previous is null, it assumes that delete_node is head.
// If delete is null do nothing.
  if (!delete_node)
    return;
  if(!previous)
  {
    head = delete_node -> next;
    delete delete_node;
    incr_num_records(-1);
    return;
  }
  else
  {
    previous->next = delete_node -> next;
    incr_num_records(-1);
    delete delete_node;
  }
  return;
}
