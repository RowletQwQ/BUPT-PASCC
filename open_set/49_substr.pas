program substr;
var 
A: array [0..14] of integer;
B: array [0..12] of integer;

function MAX(a, b: integer): integer;
begin
  if a >= b then
    MAX := a
  else
    MAX := b;
end;

function max_sum_nonadjacent(n: integer): integer;
var
i: integer;
temp: array [0..15] of integer;
begin
  temp[0] := A[0];
  temp[1] := MAX(A[0], A[1]);
  for i := 2 to n - 1 do
    temp[i] := MAX(temp[i - 2] + A[i], temp[i - 1]);
  max_sum_nonadjacent := temp[n - 1]
end;

function longest_common_subseq(len1, len2: integer): integer;
var i, j: integer;
p: array[0..15, 0..15] of integer;
begin
  for i := 0 to 15 do
    p[i, 0] := 0;
  for j := 0 to 15 do
    p[0, j] := 0;
  for i := 1 to len1 do
  begin
    for j := 1 to len2 do
    begin
      if A[i - 1] = B[j - 1] then
        p[i, j] := p[i - 1, j - 1] + 1
      else
        p[i, j] := MAX(p[i - 1, j], p[i, j - 1]);
    end;
  end;
  longest_common_subseq := p[len1, len2];
end;

begin
  A[0] := 8;
  A[1] := 7;
  A[2] := 4;
  A[3] := 1;
  A[4] := 2;
  A[5] := 7;
  A[6] := 0;
  A[7] := 1;
  A[8] := 9;
  A[9] := 3;
  A[10] := 4;
  A[11] := 8;
  A[12] := 3;
  A[13] := 7;
  A[14] := 0;
  B[0] := 3;
  B[1] := 9;
  B[2] := 7;
  B[3] := 1;
  B[4] := 4;
  B[5] := 2;
  B[6] := 4;
  B[7] := 3;
  B[8] := 6;
  B[9] := 8;
  B[10] := 0;
  B[11] := 1;
  B[12] := 5;

  write(max_sum_nonadjacent(15));
  write(longest_common_subseq(15, 13));
end.
