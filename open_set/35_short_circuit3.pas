program main;
const
AA='A';BB='B';CC='C';DD='D';E='E';F='F';G='G';H='H';I='I';J='J';K='K';
c=1;
var
a, b, d: integer;
i0,i1,i2,i3,i4: integer;

function set_a(val: integer): integer;
begin
  a := val;
  set_a := val;
end;

function set_b(val: integer): integer;
begin
  b := val;
  set_b := val;
end;

function set_d(val: integer): integer;
begin
  d := val;
  set_d := val;
end;

begin
  a := 2;
  b := 3;
  if (set_a(0) <> 0) and (set_b(1) <> 0) then
    ;
  write(a);
  write(b);

  a := 2;
  b := 3;
  if (set_a(0) <> 0) and (set_b(1) <> 0) then
    ;
  write(a);
  write(b);

  d := 2;
  if (c >= 1) and (set_d(3) <> 0) then
    ;
  write(d);
  if (c <= 1) or (set_d(4) <> 0) then
    ;
  write(d);
  
  if (16 >= (3 - (2 + 1))) then
    write(AA);
  if (25 - 7) <> (36 - 6 * 3) then
    write(BB);
  if (1 <> (7 mod 2)) then
    write(CC);
  if 3 <= 4 then
    write(DD);
  if 0 <> 0 then
    write(E);
  if 1 <> 0 then
    write(F);
  
  i0 := 0;
  i1 := 1;
  i2 := 2;
  i3 := 3;
  i4 := 4;
  if (i0 <> 0) or (i1 <> 0) then
    write(G);
  if (i0 >= i1) or (i1 <= i0) then
    write(H);
  if (i2 >= i1) and (i4 <> i3) then
    write(I);
  if (i0 = 0) and (i3 < i3) or (i4 >= i4) then
    write(J);
  if (i0 = 0) or (i3 < i3) and (i4 >= i4) then
    write(K);
end.