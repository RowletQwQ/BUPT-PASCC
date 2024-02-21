program main;
var a, sum, i: integer;

function func: integer;
var b,a: integer;
begin
  b := 7;
  a := 1;
  if (a = b) then
  begin
    a := a + 1;
    func := 1;
  end
  else
    func := 0;
end;

begin
  a := 7;
  sum := 0;
  for i := 0 to 99 do
  begin
    if (func() = 1) then
      sum := sum + 1;
  end;
  write(a);
  write(sum);
end.
