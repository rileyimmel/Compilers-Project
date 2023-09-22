# Deliverable 1: TIP Parser Expansion
In this part of the project, we extended the existing TIP parser to add the features below and thus make it the SIP Parser.
- Arrays, a length operator, and array referencing
- Boolean operations (true, false, not, and, or)
- Modulo and negation operators
- Ternary conditional expressions
- Increment and decrement statements
- For loops of iterator and range style

# Challenges
We never faced any big challenges with this part of the project. There were a few things that stumped us a little, but we were always able to figure out how to solve/implement them within an hour or two. Some of these were features like inc/dec and ternary, specifically with its associativity.

# Testing Approach
In terms of testing, we used a loosely inverted TDD approach. We would first add a new feature to the grammar how we thought would work. We would then write at least 1 passing test, ensure it passed, then write at least 1 failing test.

We wrote these tests in a new unit test file SIPParserTest.cpp. This method of testing covered mainly equivalence tests as we were unsure how/if it is possible to do boundary or exception testing at the parse level.

In the process of updating the grammar, a few tests in the provided TIPParserTest.cpp file began to fail as we introduced new operators, specifically operators these tests were written to ensure did not parse. When these would arise, we simply removed those tests from the TIPParserTest.cpp file as they were covered in SIPParserTest.cpp anyway.

Once we had implemented all the new features and wrote equivalence tests, we began to ensure we had our grammar precedence set up correctly by writing tests focused on precedence for all the new features. In this process, we discovered there was some associativity issues, particularly with the ternary and so updated it accordingly.

The structure of the precedence tests assume working precedence and associativity for all native TIP features. For the operators and expressions that have been newly implemented, first, associativity was checked to ensure that operators like * and / have equal lexical standing (i.e. both 3 * 4 / 5 and 3 / 4 * 5 are evaluated left to right).

After checking associativity, precedence was checked between an expression and the expression directly succeeding it in the TIP.g4 file (i.e. % is evaluated first in both 3 + 4 % 5 and 3 % 4 + 5). By beginning with associativity tests, it can be shown that, by just doing tests between 1 of each type of operator (i.e. % higher than +), the same precedence tests will work for all operators of said group (i.e. *,/,% higher than +/-).