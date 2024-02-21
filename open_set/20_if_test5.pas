program main;

function if_if_Else: integer;
var a,b: integer;
begin
  a := 5;
  b := 10;
  if (a = 5) then
  begin
    if (b = 10) then
      a := 25;
  end
  else
    a := a + 15;
  if_if_Else := a;
end;

begin
  write(if_if_Else);
end.
