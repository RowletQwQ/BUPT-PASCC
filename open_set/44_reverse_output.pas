program main;
var
  i: integer;

procedure reverse(n: integer);
var
  next: integer;
begin
  if n <= 1 then
  begin
    read(next);
    write(next);
  end
  else
  begin
    read(next);
    reverse(n - 1);
    write(next);
  end;
end;

begin
  i := 200;
  reverse(i);
end.
