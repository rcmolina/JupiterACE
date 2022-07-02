\ Sample Forth Code
\ Author: Rafa Molina

: SQUARED   ( n -- n*n , square number )     DUP *  ;
: TEST.SQUARED ( -- )   ." 5*5 = " 5 SQUARED . CR ;
: SUM-OF-SQUARES   ( a b -- c )  SQUARED  SWAP SQUARED  +  ;

3 SQUARED . CR
." 7*7 = " 7 SQUARED . CR
TEST.SQUARED
." 3*3 + 4*4 = " 3 4 SUM-OF-SQUARES . CR
