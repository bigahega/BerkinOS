; Get the cursor pos. OUT: BX = Offset
;--------------------------------------
get_cursor:
      push   eax
      push   edx

      mov   dx, 0x3D4
      mov   al, 0x0E
      out   dx, al
      inc   dx
      in   al, dx
      mov   bh, al
      mov   al, 0x0F
      dec   dx
      out   dx, al
      inc   dx
      in   al, dx
      mov   bl, al

      pop   edx
      pop   eax
      ret
