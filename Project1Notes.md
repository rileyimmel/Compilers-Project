
[comment]: # (This file was for internal purposes to keep track of testing progress. It is being preserved for posterity reasons. Precedence tests were never added to this file but do exist for this part of the project)

Features:

- Boolean
    - Tests:
        - Equivalence:
            - 1 pass in an if: if ( x == true) else if ( x == false)
            - 1 pass as stored in var: y = true
            - 1 pass a while cond.: while ( true )
            - 1 pass as while cond. w/ 'not': while ( not true)

- Unary 'not'
    - Tests:
        - Equivalence:
            - 1 pass: if (not x)
            - 1 pass as while cond. w/ 'not': while ( not true)
            - 1 fail: x = not y

- 'and' & 'or'
    - Tests:
        - Equivalence:
            - 1 pass for and: x = true; y = true; while (x and y)
            - 1 fail for and: x = true; while (x and @)
            - 1 pass for or: x = true; y = true; while (x or y)
            - 1 fail for or: x = true; while (x or @)

- Arrays [E1, ..., En] & [E1 of E2]
    - Tests:
        - Equivalence:
            - 1 pass for first style: a = [0,1]; b = [];
            - 2 fail for first style: a = [0,]; @ = [0,1];
            - 1 pass for of style: a = [5 of 3];
            - 2 fail for of style: a = [5 of @]; a = [5 of ];

- '#'
    - Tests:
        - Equivalence:
            - 1 pass: a = [0,1]; b = #a;
            - 1 fail: a = [0,1]; b = #@;

- Array ref. op. E1[E2]
    - Tests:
        - Equivalence:
            - 1 pass: b = a[0];
            - 2 fail: b = a[@]; b = @[0];

- '%'
    - Tests:
        - Equivalence:
            - 1 pass test: x = y % 1
            - 1 lexer pass test
            - 1 fail test: x = y % @

- '-', arithmetic negation
    - Tests:
        - Equivalence:
            - 1 pass test: x = -x
            - 1 fail test: x = -@

- Relational ('<','<=','>=')
    - Tests:
        - Equivalence:
            - 1 pass test for each op: x = NUMBER op NUMBER
            - 1 lexer pass test for LE
            - 1 fail test for each op: x = 1 op @

- Ternary, E1 ? E2 : E3
    - Tests:
        - Equivalence:
            - 1 pass test: a = x ? y : z;
            - 1 fail test: a = x ? @ : z;

- E++ & E--
    - Tests:
        - Equivalence:
            - 1 pass test each: x++; x--;
            - 1 fail test each: @++; @--;

- Foreach 'for (E1 : E2) S'
    - Tests:
        - Equivalence:
            - 1 pass test: expr : expr
            - 1 fail test: expr : @

- Foreach range 'for (E1 : E2 .. E3 by E4) S'
    - Tests:
        - Equivalence:
            - 1 pass: varying versions: all exprs as vars, as numbers, mixed. Each version has a loop with and without the by keyword
            - 3 fail: without the '..', 1 of the 4 exprs is not an expr, missing 1 of 3 required exprs