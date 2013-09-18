#include "queue.hpp"
int main()
{
  queue my_queue;
  my_queue.push(3);
  my_queue.push(25);
  my_queue.after(25, 17);
  my_queue.before(17, 5);
  my_queue.before(3, 20);
  my_queue.pop();
  my_queue.erase(25);
  my_queue.print_list();
  
  return 0;
}




