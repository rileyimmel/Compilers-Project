
You are to describe your process for selecting optimizations, describe each optimization that is included, and describe the evidence that supports its unique benefit in optimizing SIP programs.
## Scope

For this deliverable, we were to focus on extending the optimizer to include new passes. We had the choice of doing so on our SIP compiler we've built up in deliverables 1-4 or to go back to the base TIP compiler and add optimization passes to that. Given we were unable to get our Deliverable 4 working and for fear that the time cost to get it in working shape would be too great, we chose to go back to the TIP compiler for this deliverable.

## Approach

We didn't really know where to start on this deliverable and so spent some time exploring and trying to understand the LLVM PassBuilderPipelines.cpp file that was linked. We were able to garner a little understanding from this but ultimately, it proved to be a bit confusing and so we mainly would just look at the include statements of the header files to see what passes were available.

We first focused on finding loop passes as those seemed to have the most options.

Our general approach was to duplicate what is seen in the demo branch of TIPC. We would add the header file, add a if contains conditional to Optimizer.cpp and then write a microbenchmark file. We would then run the benchmark with and without the new optimization and change around the n value until we were either convinced the optimization made an impact. If it did, we kept it, if not, got rid of it (which happened *a lot*).

We tried looking at other optimizations that weren't just loop focused but struggled with this (discussed below).

We made each optimization an optional one as seen in the demo as well as created an "all" option which combined all the new optimizations (as well as the existing ones).
- We were confused on what exactly was wanted in this regard. The document made it sound like we should be benchmarking by compiling with every single implemented optimization and then timing it versus a version that is compiled with all but the new optimization but this feels like it doesn't necessarily make sense as some optimizations simply don't apply/have any effect on others. I.e. if we write a benchmark focused on inductive variable simplification, loop rotation and un switching might have no effect. Because of this, we chose to conduct our benchmarks by compiling with the base TIP optimizations and then comparing to a compilation of the base + the new optimization. Our confusion also laid in the fact that the document also seemed to point towards doing this as it said to follow the demo branch which seemed to do this approach.
    - We also chose to do a sanity check on this and convinced ourselves that doing base TIP vs base TIP + new makes the most sense. You don't necessarily always want to run every optimization (otherwise why would clang allow selectively choosing the O level) and also, doing the benchmarks with all optimizations might obscure the impact of just the new optimization. Additionally, based on ordering of passes, it is possible that a previous optimization actually hinders the effect of a new one. Thus we chose to make each new optimization togglable while also providing an "all" option for ease of use (which follows the same ordering as if the user were to manually list out all possible optimizations as arguments).
        - Of course the same arguments made above can be applied to the base TIP optimizations and thus pose the question why didn't we do zero optimizations vs just the new one. But seeing as the base optimizations were not made togglable (except all together), we chose to treat them as our baseline.

## Testing/Microbenchmarks

Our testing consisted of making and running microbenchmarks for the new optimizations. We would create a little program specifically with a focus on featuring code that the optimization could take advantage of to speed up the program. We would then run the following to convince ourselves whether or not the optimization had an effect:

```
bs bmark.tip && mv bmark ubmark && bs -opt bmark.tip && mv bmark obmark
time ./ubmark n && time ./obmark n
```

where

```
- bs is an alias to the build script
- bmark was the name of the optimization 
	- ivs.tip, lr.tip, etc.
- ubmark is unoptimized benchmark (default TIP optimizations only)
- obmark is optimized benchmark (default TIP + new optimization)
- n is a variable we played around with to see if any speed up existed
```

We would start with n = 10,000 and go up until either the times become too long (close to 1 minute) or we could see a demonstrable time decrease (i.e. was clearly a result of the optimization and not coincidence of hardware, the current load on portal$^1$, CPU scheduling etc.) Some of these optimizations/benchmarks took very large n's before a significant time decrease was observed.


- ivs (Inductive Variable Simplification) took quite a while but really sped up once it did (100,000,000 gave a 525x increase and 10,000,000,000 gave a 13,109x increase.)
- slup (Simple Loop Un-switching) took 100,000,000 to get a 2x increase on our benchmark program. Below that value, it ranged from ~0.25x to 2x.
- lr (Loop Rotation) took 100,000 to achieve a 2x increase but the benchmark featured a nested while loop.


1: I, Riley, have been using the gpu servers for development as building is much faster (can run make with 40 instead of 16; also have run into high cpu usage on portal multiple times) and noticed that it was taking higher n value's to see a significant time decrease and the time decrease achieved was smaller than when the benchmark was run on portal. This makes sense but was just an interesting note (it also most likely made me spend much more time looking for optimizations as the time decrease was not nearly as apparent on a few cases-- I wish I remember which but I've spent far too long looking at LLVM optimization passes in one day to remember which).

## Challenges

We faced many challenges with this deliverable that made it much more time-consuming and difficult than expected. There were 4 categories of challenges we faced.

#### Finding Optimizations

This category is essentially all encompassing of our challenges. We found it super difficult to find optimizations that either a) were applicable to TIP and / or b) actually made a demonstrable improvement. We struggled most with finding non-loop focused optimizations for the reasons just listed. Below are we what we believe to be the four largest causes of why we struggled with finding optimizations to implement.

#### The Provided Optimizations

This wasn't discovered until a few hours in of testing optimizations (and only found because of a random StackOverflow post- but is something we should have caught on our own), but the base optimizations in TIPC, seem to already account for quite a few of the possible passes. Specifically, the post (as far as I remember, I couldn't find it again) mentioned how the GVNPass and SimplifyCFGPass already did a lot of what other possible passes could do. This could have been avoided if I better understood the comment above the CFG pass about simplifying the control flow graph but I read it once and didn't really understand so moved on. I still don't fully understand what specifically these passes due in terms of which other passes they would make redundant /  have no impact (but I'm assuming its passes focused on dead code/expressions/etc. for the CFG pass).

#### TIP Limitations

The other very big issue was having to work with TIP instead of SIP. After looking through many optimization passes, it became apparent that most would not apply to TIP due to its severely limited feature set. There were quite a few passes that focused on arrays, globals, and other features TIP lacks. Some were features not even present in SIP but others were and thus we wish we had been able to get SIP working in the last deliverable. One specific pass I wanted to include was Tail Recursion Elimination which I noticed was in the Optimizer.cpp file of the main branch of TIPC on the template repo. But after digging, it looks like it was a leftover thing from converting to the new manager (and it was also never even implemented in the new manager, just its header file imported). I also may be misunderstanding what exactly this pass does (perhaps it changed with the new manager since I can see it was implemented in TIPC in the old pass manager iteration), but I don't understand how this would be applicable to TIP as it requires recursion and as far as I can tell/remember, TIP doesn't allow for if-else-else-if ... with returns inside the conditionals (and I can't seem to think of a way to make a recursive function in TIP).


#### Benchmark Programs

The other difficulty faced was that it's quite difficult to make benchmark programs which not only allow for exploitation of the specific optimization, but also that do so in a way that the optimization provides a very clear performance increase. It is entirely possible there were some optimizations that were tried that might have had a clear effect and been useful but we missed simply due to being unable to create an effective program/benchmark to demonstrate this.

#### Documentation

The last, and most frustrating issue, was the lack of quality documentation for the passes. I imagine this frustration stems from not being educated/familiar enough with LLVM docs./optimization/and whatever other prior knowledge is needed to most easily understand them. Some of the passes had more built out and well written documentation and made it easier to understand what they did while others had very barebones or technically dense documentation. Some even had no description of what they did or others had not been updated. One specific confusing instance was about the SCCP optimization which exists both as a scalar and IPO pass (which I sort of understand to be that its scope is different but I didn't spend long enough on this one to fully understand)? Although its unclear if both exist in the new manger? There was another optimization which had two different LLVM doc pages for it but I believe one was for the new manager while the other was for the old? And another one had one page with about 2 lines describing it but then a second different page where the comment was very in-depth with a diagram. Overall though, it was difficult to understand what optimizations to even bother trying because the documentation for some was either incredibly sparse or far too technical to understand and I imagine this again probably led to us passing over optimizations we could have implemented simply because we didn't understand what they were/did/required/etc.


