#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "abstract_calc.h"
#include "parser_calc.h"
#include "ast_calc.h"
#include "jit_calc.h"

typedef enum 
{
  CM_PARSE,
  CM_AST,
  CM_LLVM,
} calc_mode_t;

int main (int argc, char* argv[])
{
  abstract_expr_calc_t abstract_expr_calc;
  calc_mode_t calc_mode = CM_PARSE;
  int repeat = 1;
  int op;
  value_type_t x_value;
  
  while ((op = getopt (argc, argv, "pajr:x:")) != -1)
    switch (op)
      {
        case 'p':
          calc_mode = CM_PARSE;
          break;
        case 'a':
          calc_mode = CM_AST;
          break;
        case 'j':
          calc_mode = CM_LLVM;
          break;
        case 'r':
          repeat = atoi (optarg);
          break;
        case 'x':
          // TODO: Make parse function universal for each value_type_t
          x_value = atoi (optarg);
          break;
      }
  int rc;
  switch (calc_mode)
    {
    case CM_PARSE:
      rc = expr_parser_init (&abstract_expr_calc, x_value, argv[optind]);
      break;
    case CM_AST:
      rc = expr_ast_init (&abstract_expr_calc, x_value, argv[optind]);
      break;
    case CM_LLVM:
      rc = expr_jit_init (&abstract_expr_calc, x_value, argv[optind]);
      break;
    }
  if (rc)
    {
      fprintf (stderr, "Failed to init calculator");
      return (EXIT_FAILURE);
    }
  int i;
  double sum = 0;
  for (i = 0; i < repeat; ++i)
    {
      if (abstract_expr_calc.calc (&abstract_expr_calc))
        {
          fprintf (stderr, "An error caught during a calculation");
          return (EXIT_FAILURE);
        }
      sum += abstract_expr_calc.result;
    }

  printf ("%s = %g\n", argv[optind], sum);

  abstract_expr_calc.destroy (&abstract_expr_calc);

  return (EXIT_SUCCESS);
}
