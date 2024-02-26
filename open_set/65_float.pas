program main;
const
RADIUS = 5.5; PI = 03.141595653589793; EPS = 0.000001;
EVAL1 = 95.033188;
CONV1 = 233;
MAX = 1000000000;
TWO = 2.9; THREE = 3; FIVE = 5;
e = 'e'; o = 'o';

var p:integer;
arr: array[0..9] of real;
input, area, area_trunc: real;

function float_abs(x: real):real;
begin
  if x < 0 then
    float_abs := -x
  else
    float_abs := x;
end;

function circle_area(radius: integer):real;
begin
  circle_area := PI * radius *radius + (radius * radius) * PI / 2;
end;

function float_eq(a,b: real):integer;
begin
  if float_abs(a - b) < EPS then
    float_eq := 1
  else
    float_eq := 0
end;

procedure error;
begin
  write(e);
end;

procedure ok;
begin
  write(o);
end;

procedure assert(cond: integer);
begin 
  if cond = 0 then
    error
  else
    ok;
end;

begin
  assert(float_eq(circle_area(5), circle_area(FIVE)));
  if 1.5 <> 0.0 then
    ok;
  if (not (3.3 = 0.0)) then
    ok;
  if (0.0 <> 0.0) and (3 <> 0.0) then
    error;
  if (0 <> 0.0) or (0.3 <> 0.0) then
    ok;

  p := 0;
  arr[0] := 1.0;
  arr[1] := 2.0;
  input := 0.520;
  area := PI * input;
  area_trunc := circle_area(0);
  arr[p] := arr[p] + input;

  write(area);
  write(area_trunc);
  write(arr[0]);
end.
