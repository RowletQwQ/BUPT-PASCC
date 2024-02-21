program main;
var a, b, c: integer;
begin
  read(a);
  read(b);
  if ((a = b) and (a <> 3)) then
  begin
    c := 1;
  end
  else
  begin
    c := 0;
  end;
  write(c);
end.
