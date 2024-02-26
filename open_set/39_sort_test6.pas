program CountingSort;

var
  n, i: integer;
  ini_arr, sorted_arr: array[0..9] of integer;

procedure countingsort;
var
i, j, k, jj: integer;
count_arr: array[0..9] of integer;
begin
  for k := 0 to n - 1 do
    count_arr[k] := 0;
  for i := 0 to n - 1 do
    count_arr[ini_arr[i]] := count_arr[ini_arr[i]] + 1;
  for k := 1 to n - 1 do
    count_arr[k] := count_arr[k] + count_arr[k - 1];
  for j := 0 to n - 1 do
  begin
    jj := n - j;
    count_arr[ini_arr[jj - 1]] := count_arr[ini_arr[jj - 1]] - 1;
    sorted_arr[count_arr[ini_arr[jj - 1]]] := ini_arr[jj - 1];
  end;
end;

begin
  n := 10;
  ini_arr[0] := 4;
  ini_arr[1] := 3;
  ini_arr[2] := 9;
  ini_arr[3] := 2;
  ini_arr[4] := 0;
  ini_arr[5] := 1;
  ini_arr[6] := 6;
  ini_arr[7] := 5;
  ini_arr[8] := 7;
  ini_arr[9] := 8;

  countingsort;

  for i := 0 to n - 1 do
  begin
    write(sorted_arr[i]);
  end;
end.
