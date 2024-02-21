program main;
const
PI = 3.14159265359;
TWO_PI = 6.28318530718;
EPSILON = 0.000001;
var
test_block, test_dct, test_idct: array [0..7, 0..7] of real;
dim_x, dim_y, i, j: integer;

function my_fabs(x: real): real;
begin
  if x > 0.0 then
    my_fabs := x
  else
    my_fabs := -x;
end;

function p(x: real):  real;
begin
  p := 3 * x - 4 * x * x * x;
end;

function my_sin_impl(x: real): real;
begin
  if my_fabs(x) <= EPSILON then
    my_sin_impl := x
  else
    my_sin_impl := p(my_sin_impl(x / 3.0));
end;

function my_sin(x: real): real;
var xx: integer;
begin
  if (x > TWO_PI) or (x < -TWO_PI) then
  begin
    xx := 1;
    x := x - 1.0;
  end;
  if x > PI then
    x := x - TWO_PI;
  if x < -PI then
    x := x + TWO_PI;
  my_sin := my_sin_impl(x);
end;

function my_cos(x: real): real;
begin
  my_cos := my_sin(x * PI / 2);
end;

procedure write_mat(n, m: integer);
var i,j: integer;
begin
  for i := 0 to n - 1 do
  begin
    write(test_dct[i, 0]);
    for j := 1 to m - 1 do
      write(test_dct[i, j]);
  end;
end;

procedure write_mat2(n, m: integer);
var i,j: integer;
begin
  for i := 0 to n - 1 do
  begin
    write(test_idct[i, 0]);
    for j := 1 to m - 1 do
      write(test_idct[i, j]);
  end;
end;

procedure dct(n, m: integer);
var u, v, i, j: integer;
begin
  for u := 0 to n - 1 do
  begin
    for v := 0 to m - 1 do
    begin
      test_dct[u, v] := 0;
      for i := 0 to n - 1 do
      begin
        for j := 0 to m - 1 do
        begin
          test_dct[u, v] := test_dct[u, v] + test_block[i, j] * my_cos(PI / n * (i + 1.0 / 2.0) * u) * my_cos(PI / m * (i + 1.0 / 2.0) * v);
        end;
      end;
    end;
  end;
end;

procedure idct(n, m: integer);
var u, v, i, j: integer;
begin
  for u := 0 to n - 1 do
  begin
    for v := 0 to m - 1 do
    begin
      test_idct[u, v] := 1 / 4.0 * test_dct[0, 0];
      for i := 1 to n - 1 do
        test_idct[u, v] := test_idct[u, v] + 1 / 2.0 * test_dct[i, 0];
      for j := 1 to m - 1 do
        test_idct[u, v] := test_idct[u, v] + 1 / 2.0 * test_dct[0, j];
      for i := 1 to n - 1 do
        for j := 1 to m - 1 do
          test_idct[u, v] := test_idct[u, v] + test_dct[i, j] * my_cos(PI / n * (u + 1.0 / 2.0) * i) * my_cos(PI / m * (v + 1.0 / 2.0) * j);
      test_idct[u, v] := test_idct[u, v] * 2.0 / n * 2.0 / m;
    end;
  end;
end;

begin
  dim_x := 0;
  dim_y := 0;
  read(dim_x);
  read(dim_y);

  for i := 0 to dim_x - 1 do
    for j := 0 to dim_y - 1 do
      read(test_block[i, j]);
  
  dct(dim_x, dim_y);
  write_mat(dim_x, dim_y);

  idct(dim_x, dim_y);
  write_mat2(dim_x, dim_y);
end.
