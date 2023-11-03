## Scope

For this deliverable, we were to extend the weeding and semantics part of the compiler to work with the SIP additions. This included adding to the weeding pass, creating new concrete types, extending the type constraints, and creating tests to cover all new functionality.

## Approach

Our approach was to first look at and extend the weeding pass by including assigning through an array element reference (E1[E2] = E3).

Next we began to extend the TypeConstraintVisitor file. We would write a few endVisit methods then when we ran into needing a new TipType, we would create it and then resume writing the endVisit methods. This resulted in us creating the TipBool and TipArray types. We also had to update the Substituter.

When we were doing our constraints, we had to choose how to represent the overall type for a few structures and for this we tried to use alpha as sparingly as possible but still had to use it in some places.

## Testing

Once we finished a first try at the constraints, we began to write tests copying the "new" style (the style seen in UnifierTest.cpp). Through this we found a few issues in terms of printing the types and a few missed or incorrect constraints. We went back and fixed those and got our tests of this style working. We also wrote tests for TipBool following the style found for other concrete type tests. During our testing we ran into issues with TIP features which we updated; these included changing if, while, and comparison operators to have their types be boolean. For if and while this was their condition while for comparison, this was the resultant type (i.e. the overall type of the expression which is either stored or used as a condition).

We also had to update some of the provided TIP Tests like TypeConstraintCollector as it was expecting ints instead of bools. We also had to update cmpassignment.tip as it was expecting an int too.

Through the tests written in
```
SIPSemanticTests.cpp
TipBoolTest.cpp
TipArrayTest.cpp
SIPCheckAssignableTest.cpp
```
we were able to hit 100% code coverage of all new additions.

## Challenges

The hardest part was nailing down the constraints. We got a lot of hints and information from class on 11/2 that made it easier but not easy. We still spent a while and went through a few iterations of our type constraints before getting them nailed down and working right.
