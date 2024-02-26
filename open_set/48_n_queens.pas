program NQueens;
const
newline = ',';
blank = ' ';

var
  ans: array[1..50] of integer;
  sum, n: integer;
  row: array[1..50] of integer;
  line1: array[1..50] of integer;
  line2: array[1..100] of integer;
  k, i: integer;

procedure printans;
var
  i: integer;
begin
  sum := sum + 1;
  for i := 1 to n do
  begin
    write(ans[i]);
    if i = n then
      write(newline)
    else
      write(blank);
  end;
end;

procedure f(step: integer);
var
  i: integer;
begin
  for i := 1 to n do
  begin
    if (row[i] <> 1) and (line1[step + i] = 0) and (line2[n + step - i] = 0) then
    begin
      ans[step] := i;
      if step = n then
        printans;
      row[i] := 1;
      line1[step + i] := 1;
      line2[n + step - i] := 1;
      f(step + 1);
      row[i] := 0;
      line1[step + i] := 0;
      line2[n + step - i] := 0;
    end;
  end;
end;


begin
  sum := 0;
  read(k);
  for i := 1 to k do
  begin
    read(n);
    f(1);
  end;

  write(sum);
end.
