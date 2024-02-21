program main;

var
  M, L, N: integer;

function tran(var a0, a1, a2, b0, b1, b2, c0, c1, c2: array of Single): integer;
var
  i: integer;
begin
  for i := 0 to M-1 do
  begin
    c1[2] := a2[1];
    c2[1] := a1[2];
    c0[1] := a1[0];
    c0[2] := a2[0];
    c1[0] := a0[1];
    c2[0] := a0[2];
    c1[1] := a1[1];
    c2[2] := a2[2];
    c0[0] := a0[0];
  end;

  tran := 0;
end;

var
  a0, a1, a2, b0, b1, b2, c0, c1, c2: array[0..2] of Single;
  i, x: integer;

begin
  N := 3;
  M := 3;
  L := 3;

  for i := 0 to M-1 do
  begin
    a0[i] := i;
    a1[i] := i;
    a2[i] := i;
    b0[i] := i;
    b1[i] := i;
    b2[i] := i;
  end;

  tran(a0, a1, a2, b0, b1, b2, c0, c1, c2);

  for i := 0 to N-1 do
  begin
    x := Round(c0[i]);
    write(x);
  end;

  for i := 0 to N-1 do
  begin
    x := Round(c1[i]);
    write(x);
  end;

  for i := 0 to N-1 do
  begin
    x := Round(c2[i]);
    write(x);
  end;
end.
