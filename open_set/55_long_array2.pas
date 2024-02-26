program Arrays;

var
  a: array[0..4095] of integer;
  b: array[0..3, 0..1023] of integer;
  c: array[0..1023, 0..3] of integer;

function f1: integer;
begin
  a[5] := 4000;
  a[4000] := 3;
  a[4095] := 7;
  c[0, a[4095]] := a[2216] + 9;
  f1 := a[a[5]];
end;

begin
  b[1][0] := 1;
  b[2][0] := 2;
  b[2][1] := 3;
  b[3][0] := 4;
  b[3][1] := 5;
  b[3][2] := 6;
  c[0][0] := 1;
  c[0][1] := 2;
  c[1][0] := 3;
  c[1][1] := 4;
  write(f1);
  write(c[2][0]);
end.
