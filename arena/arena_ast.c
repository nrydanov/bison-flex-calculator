#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "arena_ast.h"
#include <math.h>

unsigned int newast (arena* arena, int nodetype, unsigned int l, unsigned int r) {
    unsigned int n = arena_allocate(arena, 1);   
    if (n < 0) {
        yyerror(arena, NULL, "Not enough memory");
        exit(0);
    }
    node* block = arena->arena + n;
    block->l = l;
    block->r = r;
    block->nodetype = nodetype;
    
    return n;
}

unsigned int newnum (arena* arena, double d) {
    unsigned int a = arena_allocate(arena, 2);
    if (a < 0) {
        yyerror(arena, NULL, "Not enough memory");
        exit(0); 
    }
    value* val = (value*)(arena->arena + a);
    val->nodetype = 'K';
    val->number = d;
    return a;
}

double eval (arena* arena, struct node* a) {
    double v;
    unsigned int type = a->nodetype;
    node* block = arena->arena;
    if (type == 'K') {
        value* val = (value*) a;
        v = val->number;
    } 
    else
    if (type == '+') {
        v = eval(arena, block + a->l) + eval(arena, block + a->r);
    }
    else
    if (type == '-') {
        v = eval(arena, block + a->l) - eval(arena, block + a->r);
    }
    else
    if (type == '*') {
        v = eval(arena, block + a->l) * eval(arena, block + a->r);
    }
    else
    if (type == '/') {
        v = eval(arena, block + a->l) / eval(arena, block + a->r);
    }
    else
    if (type == '|') {
        v = fabs(eval(arena, block + a->l));
    }
    else
    if (type == 'M') {
        v = -eval(arena, block + a->l);
    }
    else {
        printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}
