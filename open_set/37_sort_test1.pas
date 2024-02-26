program main;
var i,n: integer;
arr:array[0..9] of integer;

function bubblesort:integer;
var i,j,tmp:integer;
begin
  for i := 0 to n - 2 do
  begin
    for j := 0 to (n - 2 - i) do
    begin
      if arr[j] > arr[j + 1] then
      begin
        tmp := arr[j + 1];
        arr[j + 1] := arr[j];
        arr[j] := tmp;
      end;
    end;
  end;
  bubblesort := 0;
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
  for i := bubblesort to n - 1 do
  begin
    write(arr[i]);
  end;
end.
