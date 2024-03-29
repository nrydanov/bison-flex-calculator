#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "arena.h"
#include "tree.h"

unsigned int ast_alloc_node ( arena_t* arena, int nodetype
                            , unsigned int l, unsigned int r ) 
{
  unsigned int index = arena_allocate (arena, 1);
  if (index < 0) 
    {
      fprintf (stderr, "Internal AST error: Not enough memory");
      exit (EXIT_FAILURE);
    }
  node_t* block = arena->arena + index;
  block->op.l = l;
  block->op.r = r;
  block->nodetype = nodetype;
  
  return index;
}

unsigned int ast_alloc_num (arena_t* arena, double d) 
{
  unsigned int index = arena_allocate (arena, 1);
  if (index < 0) 
    {
      fprintf (stderr, "Internal AST error: Not enough memory");
      exit (EXIT_FAILURE); 
    }
  node_t* value = arena->arena + index;
  value->nodetype = 'K';
  value->val = d;
  return index;
}

unsigned int ast_alloc_x (arena_t* arena) 
{
  unsigned int index = arena_allocate (arena, 1);
  if (index < 0) 
    {
      fprintf (stderr, "Internal AST error: Not enough memory");
      exit (EXIT_FAILURE); 
    }
  node_t* value = arena->arena + index;
  value->nodetype = 'X';
  return index;
}

value_type_t ast_eval (arena_t* arena, value_type_t x_value) 
{
  value_type_t results[arena->allocated];
    
  for (int i = 0; i < arena->allocated; ++i) 
    {
      node_t* node = &arena->arena[i];
      switch (node->nodetype) 
        {
          case 'K' : 
            results[i] = node->val;
            break;
          case 'X':
            results[i] = x_value;
            break;
          case '+' : 
            results[i] = results[node->op.l] + results[node->op.r];
            break;
          case '-' :
            results[i] = results[node->op.l] - results[node->op.r];
            break;
          case '*' :
            results[i] = results[node->op.l] * results[node->op.r];
            break;
          case '/' :
            results[i] = results[node->op.l] / results[node->op.r];
            break;
          case '|' :
            results[i] = fabs (results[node->op.l]);
            break;
          case 'M' :
            results[i] = -results[node->op.l];
            break;
          default:
            fprintf (stderr, "Internal AST error: Bad node %c\n", node->nodetype);
            break;
        }
    }
    if (arena->allocated == 0) 
      {
        fprintf (stderr, "Internal AST error: No allocated memory");
        exit (EXIT_FAILURE);
      }

      printf("%f", results[arena->allocated - 1]);

    return results[arena->allocated - 1];
}