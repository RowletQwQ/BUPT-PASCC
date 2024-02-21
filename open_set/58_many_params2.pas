program main;
var ret: integer;
a: array[0..60, 0..66] of integer;
b: array[0..52, 0..58] of integer;

function func(aa: integer; c: integer; e, f: integer; h, i: integer): integer;
var
  index: integer;
begin
  index := 0;
  while (index < 10) do
  begin
    write(b[aa, index]);
    index := index + 1;
  end;

  write(a[17, c]);

  while (i < 10) do
  begin
    b[6, i] := h * 128875 mod 3724;
    i := i + 1;
    h := h + 7;
  end;

  func := e + f;
end;


begin
    a[17, 1] := 6;
    a[17, 3] := 7;
    a[17, 4] := 4;
    a[17, 7] := 9;
    a[17, 11] := 11;

    b[6, 1] := 1;
    b[6, 2] := 2;
    b[6, 3] := 3;
    b[6, 9] := 9;

    ret :=  func(a[17, 1], a[17, 3],b[6, 3], b[6, 0], b[34, 4], b[51, 18]) * 3;
    write(ret);
end.
