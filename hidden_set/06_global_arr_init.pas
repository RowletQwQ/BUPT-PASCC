program main;
var
  ret: integer;
  a0: array[0..2] of integer;
  b0: array[0..3] of integer;
  c0: array[0..6] of integer;
  c: array[0..4, 0..2] of integer;
  d: array[0..4, 0..2] of integer;
  e: array[0..4, 0..2] of integer;

procedure InitializeArrays;
begin
  // Initialize arrays a0, b0, and c0 element by element
  a0[0] := 0;
  a0[1] := 0;
  a0[2] := 0;

  b0[0] := 0;
  b0[1] := 1;
  b0[2] := 0;
  b0[3] := 0;

  c0[0] := 2;
  c0[1] := 8;
  c0[2] := 6;
  c0[3] := 3;
  c0[4] := 9;
  c0[5] := 1;
  c0[6] := 5;

  // Initialize arrays c, d, and e element by element
  c[0, 0] := 1;
  c[0, 1] := 2;
  c[0, 2] := 3;
  c[1, 0] := 4;
  c[1, 1] := 5;
  c[1, 2] := 6;
  c[2, 0] := 7;
  c[2, 1] := 8;
  c[2, 2] := 9;
  c[3, 0] := 10;
  c[3, 1] := 11;
  c[3, 2] := 12;
  c[4, 0] := 13;
  c[4, 1] := 14;
  c[4, 2] := 15;

  d[0, 0] := 1;
  d[0, 1] := 2;
  d[0, 2] := 3;
  d[1, 0] := 4;
  d[1, 1] := 5;
  d[1, 2] := 6;
  d[2, 0] := 7;
  d[2, 1] := 8;
  d[2, 2] := 9;
  d[3, 0] := 10;
  d[3, 1] := 11;
  d[3, 2] := 12;
  d[4, 0] := 13;
  d[4, 1] := 14;
  d[4, 2] := 15;

  e[0, 0] := 1;
  e[0, 1] := 2;
  e[0, 2] := 3;
  e[1, 0] := 4;
  e[1, 1] := 5;
  e[1, 2] := 6;
  e[2, 0] := 7;
  e[2, 1] := 8;
  e[2, 2] := 9;
  e[3, 0] := 10;
  e[3, 1] := 11;
  e[3, 2] := 12;
  e[4, 0] := 13;
  e[4, 1] := 14;
  e[4, 2] := 15;
end;

begin
  ret := 0;

  InitializeArrays;

  ret := 5;

  write(ret);
end.
