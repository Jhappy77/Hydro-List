#include "hydro.h"
#include "list.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <unistd.h>
#include <ios>
#include <limits>
#include <sstream>


using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

int main ()
{
  FlowList theList;
  displayHeader();
  int x = readData(theList);
  manage_UI(theList);
}

void displayHeader()
{
  cout << "Program: Flow Studies - Fall 2019" << endl;
  cout << "Version 1.0" << endl;
  cout << "Lab Section B1" << endl;
  cout << "Created by Joel Happ" << endl;
  pressEnter();
}

void pressEnter()
{
  cout << "\n<<<  Press Enter to Continue  >>> \n";
  cin.get();
}

int readData(FlowList& my_list)
{
  //REQUIRES: flow.txt is a file with multiple rows of a year integer followed by a flow double
  using namespace std;
  ifstream my_input;
  my_input.open("flow.txt");
  assert(my_input);
  int number_read = 0;
  while(!my_input.eof())
  {
    int a;
    double b;
    my_input >> a >> b;
    ListItem new_item = {a, b};
    my_list.insert(new_item);
    number_read += 1;
  }
  my_input.close();
  return number_read;
}

int menu()
{
  cout << "\n Please select one of the following operations: \n";
  cout << "\t 1. Display flow list, average, and median. \n";
  cout << "\t 2. Add data \n";
  cout << "\t 3. Save your present data into flow.txt \n";
  cout << "\t 4. Remove data \n";
  cout << "\t 5. Quit program. \n";
  cout << "Enter your choice as a single key pressed (1, 2, 3, 4, or 5) \n";
  char my_char = cin.get();
  while(!((my_char >= '1')&&(my_char<= '5')) )
  {
    cout << "\n Illegal input. Please enter an integer between 1 and 5. \n";
    time_delay(700);
    my_char = cin.get();
  }
  return my_char - '0';
}

void display(const FlowList& list)
{
  cout << "\n  Year \t\t\tFlow (in billions of m^3) \n";
  cout << "-----------------------------------------------------";
  list.print_all_list_items();
  cout << "\n The average flow is: " << average(list);
  cout << "\n The median flow is: " << median(list) << endl;
}


double average(const FlowList& list)
{
  return list.get_flow_avg();
}

double median(const FlowList& list)
{
  return list.get_flow_median();
}


void addData(FlowList& list)
{
  int y; double f;
  const char * msg1 = "\n Enter an integer value for the year: ";
  y = getInt(msg1);
  const char * msg2 = "\n Enter a double for the flow, in billions of cubic meters:";
  f = getDouble(msg2);

  if (list.list_has_year(y))
  {
    cout << "\n Error: duplicate data.";
  }
  else
  {
    ListItem addthis = {y, f};
    list.insert(addthis);
    cout << "\n The year " << y << " with  flow: " << f << " has been added to the list.";
  }
}

void removeData(FlowList& list)
{
  int y;
  const char * msg = "\n Enter the year that you want to remove: ";
  y = getInt(msg);
  list.remove_node_with_year(y);
}

void manage_UI(FlowList& list)
{
  while(1)
  {
    int m = menu();
    clear_buffer();
    time_delay(600);
    if (m == 1)
      display(list);
    else if (m == 2)
      addData(list);
    else if (m == 3)
      saveData(list);
    else if (m == 4)
      removeData(list);
    else if (m == 5)
    {
      cout <<"\n Program terminated successfully...";
      exit(0);
    }
    else
    {
      cout <<"\n Error: Unexpected menu input. Program terminating.";
    }
    pressEnter();
  }
}

void saveData(const FlowList& list)
{
  std::ofstream outputObj;
  outputObj.open("flow.txt");
  assert(outputObj);
  list.print_all_list_items(outputObj);
  outputObj.close();
  cout << "\n Your data has been saved into the file called flow.txt \n";
}

void time_delay(double x)
{
  x /= 1000;
  sleep(x);
  return;
}

void clear_buffer()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  time_delay(100);
}

double getDouble(const char * message)
{
  std::string floatstr;
  double f = 0;
  while(!f)
  {
    cout << message;
    getline (cin,floatstr);
    stringstream(floatstr) >> f;
  }
  return f;
}

int getInt(const char * message)
{
  return (int)(getDouble(message));
}
