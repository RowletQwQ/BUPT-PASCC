{ test the priority of add and mul }
program main;
var a,b,c,d: integer;
begin
  a := 10;
  b := 4;
  c := 2;
  d := 2;
  write(c + a * b - d);
end.
