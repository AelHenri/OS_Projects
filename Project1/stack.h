#ifndef STACK
#define STACK

/* structure of a stack node */
struct s_node
{
   char data;
   struct s_node *next;
};
 
/* function to push an item to stack*/
void push_stack(struct s_node** top_ref, int new_data);
 
/* function to pop an item from stack*/
int pop_stack(struct s_node** top_ref);
 
#endif