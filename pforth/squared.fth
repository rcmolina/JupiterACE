: SQUARED   ( n -- nsquared )     DUP *  ;
: SUM-OF-SQUARES   ( a b -- c )  SQUARED  SWAP SQUARED  +  ;
3 SQUARED . CR
3 4 SUM-OF-SQUARES . CR