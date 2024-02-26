program SelectSort;

var
  n, i: integer;
  arr: array[0..9] of integer;

procedure selectsort;
var i,j,min,tmp: integer;
begin
  for i := 0 to n - 2 do
  begin
    min := i;
    for j := i + 1 to n - 1 do
    begin
      if arr[min] > arr[j] then
        min := j;
    end;
    if min <> i then
    begin
      tmp := arr[min];
      arr[min] := arr[i];
      arr[i] := tmp;
    end;
  end;
end;

begin
  n := 10;
  arr[0] := 4;
  arr[1] := 3;
  arr[2] := 9;
  arr[3] := 2;
  arr[4] := 0;
  arr[5] := 1;
  arr[6] := 6;
  arr[7] := 5;
  arr[8] := 7;
  arr[9] := 8;

  selectsort;

  for i := 0 to n - 1 do
  begin
    write(arr[i]);
  end;
end.
