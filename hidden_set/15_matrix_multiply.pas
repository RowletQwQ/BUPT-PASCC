program main;

var
  a,b,res: array[1..100, 1..100] of integer;
  n1, m1, n2, m2, i, j, k: integer;

procedure matrix_multiply;
begin
  for i := 1 to m1 do
  begin
    for j := 1 to n2 do
    begin
      for k := 1 to n1 do
      begin
        res[i][j] := res[i][j] + a[i][k] * b[k][j];
      end;
    end;
  end;
end;

function getint: integer;
begin
  read(getint);
end;

begin
  m1 := getint;
  n1 := getint;
  for i := 1 to m1 do
  begin
    for j := 1 to n1 do
    begin
      a[i][j] := getint;
    end;
  end;

  m2 := getint;
  n2 := getint;
  for i := 1 to m2 do
  begin
    for j := 1 to n2 do
    begin
      b[i][j] := getint;
    end;
  end;

  matrix_multiply;

  for i := 1 to m1 do
  begin
    for j := 1 to n2 do
    begin
      write(res[i][j]);
    end;
  end;
end.
