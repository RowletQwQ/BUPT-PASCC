program main;
var a,b,c,d,e: integer;
flag:boolean;
begin
  read(a);
  read(b);
  read(c);
  read(d);
  read(e);
  flag := false;
  if ((a - b * c <> d - a / c) or (a * b / c = e + d) or (a + b + c = d + e)) then
  begin
    flag := true;
  end;
  if flag then
    write(1);
end.