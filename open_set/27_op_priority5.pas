program main;
var a,b,c,d,e: integer; flag: boolean;
begin
  a := 1;
  b := 0;
  c := 1;
  d := 2;
  e := 4;
  flag := false;
  if ((a * b / c = e + d) and (a * (a + b) + c <= d + e) or (a - (b * c) = d - a / c)) then
  begin
    flag := true;
  end;
  if (flag) then
    write(1);
end.