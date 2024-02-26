program ArrayAddition;

var
  M, L, N: integer;
  a0, a1, a2, b0, b1, b2, c0, c1, c2: array[0..2] of integer;
  i, x: integer;

function add: integer;
var
  i: integer;
begin
  for i := 0 to M - 1 do
  begin
    c0[i] := a0[i] + b0[i];
    c1[i] := a1[i] + b1[i];
    c2[i] := a2[i] + b2[i];
  end;

  add := 0;
end;

begin
  N := 3;
  M := 3;
  L := 3;

  for i := 0 to M - 1 do
  begin
    a0[i] := i;
    a1[i] := i;
    a2[i] := i;
    b0[i] := i;
    b1[i] := i;
    b2[i] := i;
  end;

  add;

  for i := 0 to N - 1 do
  begin
    x := c0[i];
    write(x);
  end;

  for i := 0 to N - 1 do
  begin
    x := c1[i];
    write(x);
  end;

  for i := 0 to N - 1 do
  begin
    x := c2[i];
    write(x);
  end;
end.
