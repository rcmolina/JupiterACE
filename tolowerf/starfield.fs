15 constant count ( number of stars, <= 40 )

0 variable seed  ( random number seed )

definer array ( array construct )
  2 * allot
does>
  swap 2 * +
;!

( set aside space for various arrays )
40 array xc
40 array yc
40 array zc
40 array tx
40 array ty

( random number generator )
: (rnd)
  seed @
  259 * 3 +
  32767 and
  dup
  seed !
;

: rnd
  (rnd)
  32767 */
;

: stars
  cls
  count 0 do (initialise stars)
    16 rnd 8 - 4 * i xc !
    11 rnd 5 - 4 * i yc !
    12 6 rnd + i zc !
    32 i tx !
    22 i ty !
  loop

  ( main loop )
  begin
    count 0 do ( delete old stars )
      i tx @ 32 +
      i ty @ 22 +
      0 plot

      ( update position )
      i xc @ 4 *
      i zc @ 3 + /
      i tx !

      i yc @ 4 *
      i zc @ 3 + /
      i ty !

      i zc @ 1 -
      i zc !
      i zc @

      ( check if left screen )
      1 < if
        16 rnd 8 - 4 * i xc !
	11 rnd 5 - 4 * i yc !
	12 6 rnd + i zc !
      then

      ( replot stars )
      i tx @ 32 +
      i ty @ 22 +
      1 plot
    loop

    0
  until
;
