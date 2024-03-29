%code top {
#include "ast.h"
#include "calc.lex.h"
#include "ast_calc.h"

static void ast_error (void* scanner, char* error) {}
}

%param {void* scanner}
%define api.prefix {ast_}
%define api.pure full

%token NUMBER

%left '+' '-'
%left '*' '/'
%precedence UMINUS

%start result

%% 

result: expr 
{
  return 0;
}

expr:
  expr '+' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ = ast_alloc_node (extra->arena, '+', $1, $3); 
  }
| expr '-' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ =  ast_alloc_node (extra->arena, '-', $1, $3); 
  }
| expr '*' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ =  ast_alloc_node (extra->arena, '*', $1, $3); 
  }
| expr '/' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ =  ast_alloc_node (extra->arena, '/', $1, $3); 
  }
| '-' expr %prec UMINUS 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ = ast_alloc_node (extra->arena, 'M', $2, -1); 
  }
| '|' expr %prec UMINUS 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ = ast_alloc_node (extra->arena, '|', $2, -1); 
  }
| '(' expr ')' { $$ = $2; }
| NUMBER 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$ = ast_alloc_num (extra->arena, $1); 
  }
| 'x'
  {
    extra_t* extra = calc_get_extra (scanner);
    $$ = ast_alloc_x (extra->arena);
  }

%%