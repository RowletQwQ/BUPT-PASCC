program main;
const len = 20;
var
i,j,t,n,temp: integer;
len1,len2:integer;
mult1, mult2: array [0..19] of integer;
c1,c2: array [0..24] of integer;
result: array[0..39] of integer;

begin
  len1 := len;
  len2 := len;
  for i := 0 to 8 do
    mult1[i] := i + 1;
  mult1[9] := 0;
  for i := 10 to 18 do
    mult1[i] := i - 9;
  mult1[19] := 0;
  
  mult2[0] := 2;
  mult2[1] := 3;
  mult2[2] := 4;
  mult2[3] := 2;
  mult2[4] := 5;
  mult2[5] := 7;
  mult2[6] := 9;
  mult2[7] := 9;
  mult2[8] := 0;
  mult2[9] := 1;
  mult2[10] := 9;
  mult2[11] := 8;
  mult2[12] := 7;
  mult2[13] := 6;
  mult2[14] := 4;
  mult2[15] := 3;
  mult2[16] := 2;
  mult2[17] := 1;
  mult2[18] := 2;
  mult2[19] := 2;

  for i := 0 to len1 - 1 do
    c1[i] := mult1[i];
  for i := 0 to len2 - 1 do
    c2[i] := mult2[i];
  n := len1 + len2 - 1;

  for i := 0 to n do
    result[i] := 0;
  
  temp := 0;

  for i := 0 to len2 - 1 do
  begin
    t := c2[len2 - 1 - i];
    for j :=  0 to len1 - 1 do
    begin
      temp := result[n] + t * c1[len1 - 1 - j];
      if temp >= 10 then
      begin
        result[n] := temp;
        result[n - 1] :=result[n - 1] + temp div 10;
      end
      else
      begin
        result[n] := temp;
      end;
      n := n - 1;
    end;
    n := n + len1 - 1;
  end;

  if result[0] <> 0 then
    write(result[0]);
  
  for i := 1 to (len1 + len2 - 1) do
    write(result[i]);
end.