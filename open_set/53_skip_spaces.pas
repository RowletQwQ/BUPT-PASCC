program main;
// ???  // ????
// ?????
{dfdafa}
var
i,j,sum,t: integer;
arr: array[0..99] of integer;
begin
  t := 5;
  i := 0;
  sum := 0;
  for j := 0 to t - 1 do
  begin
    i := i + 1;
    arr[j] := i;
  end;

  for j := 0 to i - 1 do
  begin
    sum := sum + arr[j];
  end;
  write(sum mod 79);
end.