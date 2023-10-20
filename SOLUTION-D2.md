The scope of this deliverable was to extend the frontend of SIP to accommodate the new grammar rules/extensions created in Deliverable 1. This involved creating new AST node types, implementing the visitor pattern for new nodes, specifying new operators, adding new functionality to existing nodes, and specifying pretty print behavior.

It was decided to create 9 new nodes, and combine as much new functionality into existing nodes as reasonably possible. The structure is as follows:

- boolean type > new node
- unary not > new unary node
- and > add to binaryexpr
- or >  add to binaryexpr
- arrays
    - [E1, ..., En] > new node
    - [E1 of E2] > new node
- length op \# > add to new unary node
- E1[E2] > new node
- % > add to binary expr
- negation > add to new unary node (Kept old negNumber and made new expr version)
- (> / >= / <= ) > add to relational node
- ternary > new node
- inc/dec > new node
- for loops
    - for (E1 : E2) S > new node
    - for (E1 : E2 .. E3 by E4) S > new node

The above decision seemed logical and simplest for the sake of conciseness, while not stretching the bounds of each node unreasonably.

It was decided that our main testing principle would be to achieve 100% statement coverage for all new code written. To achieve this, testing was split into multiple categories, namely, SIPASTNodeTests, SIPASTPrinterTests, and SIPPrettyPrinterTests.

SIPASTNodeTests were focused on the structure of each node. They were created while generating new AST nodes and modifying existing nodes, and test the entire structure of the node. For example:

In the test generated to check the state of Ternary Nodes, we created a mock condition, a mock true expression, and a mock false expression which were fed as parameters to the ASTTernaryExpr constructor. First, the getter methods are tested. Next, the size of the children vector of the ASTTernaryExpr node is checked, in this case, there is one condition, one true expr, and a false expr, and so, it correctly reports 3 total. It then checks the post-order traversal, and makes sure that the tree is being visited correctly, and in the correct format. Lastly, it prints the entire expr using the node's print method to make sure it is in the right form.

The above test case was repeated for each new or modified node. This allowed 100% statement coverage on all necessary files in SIP's frontend/ast/treetypes as well as the newly added lines to ASTBuilder.cpp.

SIPASTPrinterTests and SIPASTPrettyPrinterTests both take in a program and an expected output, and compare the result of the build of the program to the expected output while using their respective print methods; i.e. the print method found in the specific AST node file for SIPASTPrinterTests, and the specific pretty printer method for that node. By including every new operator, statement, and expression, we were able to hit 100% statement coverage in frontend/prettyprint and frontend/ast.

Accounting for the difficulty of the deliverable, we found it initially challenging to understand the structure of the AST and it's modules and what exactly needed updating/additions. Once this was well understood, though, it seemed rather trivial to implement the necessary code. We were briefly tripped up with the creation of templates and the implementation of post-order traversals. Aside from that, there were not many large issues encountered.

