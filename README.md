CRASH COURSE IN FORTH


=========================

by Edward Patel, Jan 1998

Abstract
--------

Forth is a small and effective programming language. Not many are aware of its existence or how its is used. This crash course was written together with the Jupiter ACE emulator, xace, to show how Forth is used on the Jupiter ACE. Jupiter ACE is the _outsider_ micro from the 80's. Instead of the common BASIC it has Forth as its programming language.

I will not give a full description of Forth but rather a small picture how it works and is used. Forth is also a set of flavours that differ in some parts. The Jupiter ACE has FORTH-79 as its base but lacks some of its words, it has also some additional words for its own purpose, i.e using tapes as storage.

For a better understanding about Forth read a book like Leo Brodie's _Starting FORTH_ or try the web-tutor for _4tH_ (Jan98) [http://www.geocities.com/SiliconValley/Bay/2334/4thtutor.htm](https://web.archive.org/web/20131123220257/http://www.geocities.com/SiliconValley/Bay/2334/4thtutor.htm)

The Vocabulary
--------------

Forth is a set of words that when they are executed they carry out some predefined actions. To execute a word just type it and press enter. To see a list of all words that can be used type `**vlist**` and press enter. This set of words can easily be extended. Example:

	: hello ." Hello, world!" cr ;

This example show how a word `**hello**` is defined and that it will when executed print `**Hello, world!**` on the screen. The colon means _compile word_ and the word after it, here `**hello**`, will be the name of the new word. The `**."**` is also a Forth word because Forth interprets all clusters of non-space characters as words. The word `**."**` means (will mean - in a strictly forth manner) print to screen all characters up to the first `**"**` and here that will be `**Hello, world!**`. The `**"**` is the end-of-output delimiter and the next word will be `**cr**` that means output a carriage-return character. The last word `**;**` means end of the compiled words actions.

A word can be defined several times. A new definition does not remove the old one but rather means that any new use of the word will use the new definition. Example:

	: abc ." old definition" cr ;
	: test abc ;
	: abc ." new definition" cr ;
	test

In this example the word `**test**` uses the word `**abc**` which by the order of defining is the word that prints `**old definition**`. When the new `**abc**` is defined it will not alter `**test**` or the old `**abc**` but rather declare a new `**abc**` for future usage. Because Jupiter ACE doesn't make use of whats known as the EDITOR, that is used during software development, it has a special word `**redefine**` that will change old words and their usage to new ones. After `**redefine abc**` will `**test**` in the example above print `**new definition**`.

A word that can't be found in the vocabulary will Forth try to interpret as a number and place on the stack. If the word can't be interpreted as a number will Forth print a `**?**` at the word.

The Stacks
----------

Forth uses a stack to exchange parameters between words. A calling word should first place the parameters on the stack for a word that will be executed and then execute it. When a called word is finished it should place the result on the stack and a calling word can then use it. The values are often numbers or memory addresses. The word `**.**` will print what is on top of the stack (and remove it). Example:

	3 2 1 . . .		_will print 1 2 3_

The basic operators `**+**`, `**-**`, `**/**` and `*****` uses two values from the stack and places the result on the stack. Example:

	1 1 + .			_will print 2_
	3 1 - .			_will print 2_
	4 2 / .			_will print 2_
	2 3 \* .			_will print 6_

Forth work with integers, here 16 bit. The Jupiter ACE has extra build in words to handle floating-point numbers. These are `**f+**`, `**f-**`, `**f***`, `**f/**`, `**f.**`, `**fnegate**`, `**int**` and `**ufloat**`, and to input a floating-point number add a `**.**` at the appropriate place, i.e `**1.**` for 1 or `**.1**` for 0.1. Note for the floating-point values that they occupy two values (items) on the stack.

The stack can be manipulated in different ways. Words for this are; `**dup**`, `**swap**`, `**drop**`, `**rot**`, `**pick**`. `**dup**` duplicates the top of stack value. `**swap**` exchanges the two values on top of the stack values. `**drop**` removes the top of the stack value. `**rot**` rotates the three values on top of the stack making the value on top of the stack the second value, the second value the third and the third value on to of the stack. `**pick**` takes the value on top of the stack and looks up that number of steps down the stack and gets that value. Examples:

	1 dup . .		  _will print 1 1_
	2 1 swap . .              _will print 2 1_
	2 1 drop .                _will print 2_
	3 2 1 rot . . .           _will print 3 1 2_
	4 3 2 1 3 pick . . . . .  _will print 3 1 2 3 4_

Example of value passing through the stack.

	: add4 4 + ;
	: add8 add4 add4 ;
	5 add4 .		_will print 9_
	5 add8 .		_will print 13_	

Forth has also a second stack called the return stack. This stack is used to store return addresses during execution of a called word and other misc things. The words `**r>**` and `**>r**` is often used to move values back and forth between the stack and return stack. `**>r**` means move to the return stack and `**r>**` means move to the stack from the return stack.

Constants and Variables
-----------------------

A constant can be created as;

	: max.x 63 ;

which is a word `**max.x**` that places the value 63 on the stack. Because this a common thing to do Forth has a word just for creating constants and its name is `**constant**`. Example:

	63 constant max.x

This does the same as the previous example. A variable is similar but the user is able to change its value. When the variables name (word) is executed it rather gives a value that can be used to access the value of the variable, both for reading and writing. Example:

	12 variable x
	x @ .			_will print 12_
	13 x !			_will set x to 13_
	x @ .			_will print 13_

The word `**variable**` takes a name and a value from the stack and allocates some memory for the variable. When the new word for the variable is executed it places a value on the stack (the address). The word `**@**` takes a value from the stack and looks up in memory the value stored at that address. The word `**!**` takes two values from the stack, the top of stack is the address where the second value will be stored.

Repetitions and Decisions
-------------------------

The simples way of doing a repetition is by using the words `**do**` and `**loop**`. Example:

	: test 100 0 do ." >" loop ;
	test				_will print 100 > characters_

The word `**do**` takes two values from the stack. The top of stack is the starting value (here 0) and the second (here 100) the value when the repetition should be ended. With the word `**i**` can one access the current value for the repetition. Example:

	: test 10 4 do i . loop ;
	test				_will print 4 5 6 7 8 9_ 

Note that the 10 is not printed in the example above. Note also that the word `**loop**` increases the value by one all the time. There is a special variation of the word `**loop**` that is `**+loop**` which takes a values from the stack and uses that as the increment. Example:

	: test 0 5 do i . -2 +loop ;
	test				_will print 5 3 1_

More complicated repetitions are available with the words `**begin**`, `**until**`, `**while**` and `**repeat**`. The word `**begin**` marks where the repetition begins (returns to). The word `**until**` takes a value from the stack, if it is zero (false) it will repeat the loop from the word `**begin**`.

	: test begin dup . 1- dup 0= until drop ;
	5 test				_will print 5 4 3 2 1_

The word `**1-**` is an optimized shortcut for the pair `**1**` and `**-**`. The word `**0=**` is an optimized shortcut for the pair `**0**` and `**=**`. The word `**=**` is a test operator that takes two values from the stack and if they are equal it will place a one (true - or minus one depending on the Forth) on the stack and if they are not equal it will place zero (false) on the stack.

The next repetition construction uses the words `**begin**`, `**while**` and `**repeat**`. The word `**begin**` work like in the `**until**` case but in this case will the word `**repeat**` unconditionaly repeat the loop from the word `**begin**`. The word `**while**` is placed somewhere inbetween a `**begin**` and a `**repeat**` and it takes a value from the stack. If the value is zero (false) it will leave the repetition and continue executing after the word `**repeat**`. If the value is not zero (true) it will not do anything which in effect means that it will continue to the word `**repeat**` and there repeat the repetition from the word `**begin**`. Example:

	: test begin dup while dup . 1- repeat ;
	5 test				_will print 5 4 3 2 1_

For simple decisions there are the words `**if**`, `**else**` and `**then**`. The word `**if**` takes one value of the stack. If the value is zero (false) will `**if**` ignore everything until the word `**else**` (or `**then**` if the `**else**` is missing) and continue executing after the word `**else**`. If the value is not zero (true) will everything inbetween the word `**if**` and the word `**else**` (or `**then**` if the `**else**` is missing) be executed and everything inbetween the word `**else**` and the word `**then**` will be ignored. Example:

	: test 0= if ." in" then ." complete!" ;
	0 test				_will print incomplete!_
	1 test				_will print complete!_
	: test if ." True!" else ." False!" then ;
	0 test				_will print False!_
	1 test				_will print True!_

Note that `**if**` constructions can be nested. Example:

	if       -----+
	  if     ---+ |
	  else   ---+ |
	    if   -+ | |
	    then -+ | |
	  then   ---+ |
	else     -----+
	  if     -+   |
	  then   -+   |
	then     -----+

Compiling words
---------------

TBD. Creating your own compiling words.

Jupiter ACE words
-----------------

The Jupiter ACE has a few additional words not from the FORTH-79 definition, these are:

`save`

`save <name>` saves the vocabulary as <name>

`load`

`load <name>` loads the vocabulary <name>

`verify`

\-

`bsave`

`s l bsave <name>` saves l bytes from the memory starting at address s as <name>

`bload`

`s l bload <name>` loades 0 bytes to the memory starting at address s as <name>. If s or l is zero will their value be taken from the file.

`bverify`

\-

`list`

`list <word>` lists the definition of <word>

`edit`

`edit <word>` loads the <word> so the user can edit it. When the user presses enter will a new definition be compiled. Use `redefine` to update the new definition for older usages of the word.

`redefine`

`redefine <word>` removes the old definition of <word> and updates the older usages of it.

`f+, f-, f*, f/, f., fnegate, int, ufloat`

floating-point number words

`ascii`

`ascii <word>` puts the first letter in <word> on the stack as its ascii value

`at`

`l c at` sets the next printing position on the screen, l can be from 0 to 22 and c can be from 0 to 31.

`beep`

`T t beep` sounds the beeper with tone T (specially calculated value) for t milliseconds

`call`

`addr call` will call Z80 machine code at addr, should be terminated with a `jp (iy)` Z80 instruction.

`cls`

clears the screen

`fast`

disables some error checking routines making it all run 25% faster

`in`

does a Z80 IN (x) - used for communicating with external hardware

`inkey`

reads the keyboard, puts the ascii value of the key or 0 if no key is pressed

`invis`

disables the printing to the upper part of the screen

`line`

interprets the input buffer as a normal FORTH line

`number`

\-

`out`

does a Z80 OUT(x) - used for communicating with external hardware

`plot`

`x y m plot` plots a dot at position (x,y) with mode m. (0,0) is the lower left corner and (63,45) is the upper right corner.

`retype`

\-

`slow`

enables some error checking routines (normal execution)

`vis`

enables the printing to the upper part of the screen

`definer <name> ... does>`

is the same as `: <name> CREATE ... DOES>`

`compiler <name> ... runs>`

\-