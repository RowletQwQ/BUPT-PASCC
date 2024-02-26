program Subtraction;
var
  N, M, L, i, x: integer;
  a0: array [0..2] of integer;
  a1: array [0..2] of integer;
  a2: array [0..2] of integer;
  b0: array [0..2] of integer;
  b1: array [0..2] of integer;
  b2: array [0..2] of integer;
  c0: array [0..5] of integer;
  c1: array [0..2] of integer;
  c2: array [0..2] of integer;

function sub: integer;
begin
  for i := 0 to 2 do
  begin
    c0[i] := a0[i] - b0[i];
    c1[i] := a1[i] - b1[i];
    c2[i] := a2[i] - b2[i];
  end;

  sub := 0;
end;

begin
  N := 3;
  M := 3;
  L := 3;

  for i := 0 to 2 do
  begin
    a0[i] := i;
    a1[i] := i;
    a2[i] := i;
    b0[i] := i;
    b1[i] := i;
    b2[i] := i;
  end;

  sub;

  for i := 0 to 2 do
  begin
    x := c0[i];
    write(x);
  end;

  for i := 0 to 2 do
  begin
    x := c1[i];
    write(x);
  end;

  for i := 0 to 2 do
  begin
    x := c2[i];
    write(x);
  end;
end.
