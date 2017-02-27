#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

void push_stack(struct s_node** top_ref, int new_data){
  struct s_node* new_node =
            (struct s_node*) malloc(sizeof(struct s_node));
  if (new_node == NULL){
     printf("Stack overflow \n");
     exit(0);
  }           
  new_node->data  = new_data;
  new_node->next = (*top_ref);  
  (*top_ref)  = new_node;
}
 
int pop_stack(struct s_node** top_ref)
{
  char res;
  struct s_node *top;
  if (*top_ref == NULL){
     printf("Stack overflow \n");
     exit(0);
  }else{
     top = *top_ref;
     res = top->data;
     *top_ref = top->next;
     free(top);
     return res;
  }
}

