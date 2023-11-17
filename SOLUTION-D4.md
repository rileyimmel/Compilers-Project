You should briefly describe any tricky aspects of your solution, any design alternatives you considered and how you decided among them, and your approach to testing and achieving high test coverage
### Scope

For this deliverable, we were to extend the code generation part of the compiler to work with the SIP additions. This included writing new methods in the CodeGenFunctions.cpp file as well as ensuring 100% coverage of these new methods with tests.

### Approach

Our approach was to attempt to replicate and adapt the existing methods but we ran into a decent amount of difficulty with this (see below).

### Testing

Due to time constraints and difficulty with correctly implementing the code-gen functions, we focused only on trying to get the provided SIPtests functioning.

### Challenges

We ran into a lot of trouble with Arrays specifically. We were getting lots of semantic errors when trying to run the SIP tests and a lot of "## is not an l-value". We struggled with understanding how to properly write and use the llvm code and thus were unable to get this functioning. When we started to go through adding the SIP tests one at a time and manipulating them to try and find where specific errors were coming from, we were able to get some hints as to possible issues with our codegen. For example, in sequencesum, we get "Load/Store operand is not a pointer type" and so this leads us to believe we are trying to treat something as a pointer in our for range codegen function that isn't. Additionally, it terms of arrays, we suspect we weren't use lValueGen = true and false correctly and might be why we were getting the "not an l-value" errors. Sadly we didn't have the time needed to do this meticulous process. There most likely are other errors that exist but due to the nature of the compiler trying to fix errors itself and not having time to do the meticulous process described above, we can't say with any certainty what other errors exist.  We do know for sure the following tests from the provided zip work:

- incdec.sip
- iteexpr.sip
- logicaloperators.sip
- newoperators.sip
- itesimple.sip
- relops.sip

There may be others that work but from a quick glance, all the rest included arrays in some fashion and so we didn't try adding them individually and focused on trying to get sequencesum to work. 