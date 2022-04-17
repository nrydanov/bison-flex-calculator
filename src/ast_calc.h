#ifndef _AST_CALC_H_
#define _AST_CALC_H_

#include "tree/tree.h"
#include "ast.h"
#include "ast.lex.h"
#include "ast.tab.h"
#include "abstract_calc.h"

double ast_parse_calc (abstract_expr_calc_t* abstract_expr_calc);

void ast_parse_destroy (abstract_expr_calc_t* abstract_expr_calc);

int ast_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr);

#endif /* _AST_CALC_H_ */