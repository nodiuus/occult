# Occult
The Occult programming lanugage is a programming language... really made with mystery.. like an occult? 

# Building
To build Occult just copy and paste this:
```
$ git clone https://github.com/occultlang/occult && cd ./occult && chmod +x ./build.sh && ./build.sh
```

# Using Occult
To use Occult, you can just build it using the steps above and run this:
```
$ ./occultc <path/to/source.occ> 
```
To debug:
```
$ ./occultc <path/to/source.occ> -dbg
```

# Speed & Tests
Occult is about the same as C for running a **non** recursion fibonacci sequence
Test cases are in the `test_cases` directory

# Cleaning
To clean the build directory just run `clean.sh`

# To-do
- [ ] Array declarations for arguments
- [ ] Wrapper around arrays to make it easier to type 
- [ ] Add for loops
- [ ] Add matching
- [ ] Add imports
- [ ] Add casting
- [ ] Fix Commenting in lexical stage as well as floating points
- [ ] Fix floating points not working fully when generating code + parsing
- [ ] Add tuples
- [ ] Add incrementing with i++ and i-- etc. to codegen
- [ ] Get TinyC working with Ahead-of-Time compilation (made mode is still JIT)

Not sure what else?!

# How?
Right now Occult uses TinyCC as a backend for a JIT compiler, and Occult just compiles its own code into C and it runs on the fly.

Without the advances in generative AI, I would have never been able to write a compiler it has helped me so much with learning new concepts and some coding mistakes!
There's a clear vision for this project in the end to make it bootstrappable so it can compile itself and with safety in mind for the end user. <3 

# LICENSE
GNU Lesser General Public License v2.1 (Same as TinyCC)
