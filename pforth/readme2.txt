http://www.softsynth.com/pforth/pf_ref.php#Compiling-File

Testing your Compiled pForth
Once you have compiled pForth, you can test it using the small verification suite we provide.  The first test you should run was written by John Hayes at John Hopkins University.  Enter:

pforth
include tester.fth
include coretest.fth
bye
----------------------------------------------------------
http://www.softsynth.com/pforth/pf_ref.php#Running-pForth

The process of building pForth involves several steps. This process is typically handled automatically by the Makefile or IDE Project.

Compile the 'C' based pForth kernel called "pforth" or "pforth.exe".
Execute "pforth" with the -i option to build the dictionary from scratch. Compile the "system.fth" file which will add all the top level Forth words. This can be done in one command by entering "pforth -i system.fth".
Save the compiled dictionary as "pforth.dic".
The next time you run pforth, the precompiled pforth.dic file will be loaded automatically.

---------------------------------------
https://www.thegeekstuff.com/2010/06/forth-programming-hello-world-example/

$ pforth helloworld.fth
PForth V21
pForth loading dictionary from file /usr/lib/pforth/pforth.dic
     File format version is 8
     Name space size = 120000
     Code space size = 300000
     Entry Point     = 0
     Little  Endian Dictionary
Begin AUTO.INIT ------
Including: helloworld.fth
Hello World!
End AUTO.TERM ------
