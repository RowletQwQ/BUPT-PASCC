program main;
var a,b,c,d,e: integer;
begin
  a := 5;
  b := 5;
  c := 1;
  d := -2;
  e := 2;
  if ((d * 1 div 2) < 0) or ((a - b) <> 0) and ((c + 3) mod 2 <> 0) then
  begin
    write(e);
  end;
  if ((d mod 2 + 67) < 0) or ((a - b) <> 0) and ((c + 2) mod 2 <> 0) then
  begin
    e := 4;
    write(e);
  end;
end.
