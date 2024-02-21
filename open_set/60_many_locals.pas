program main;
var
  a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x:integer;
  sum,sum1,sum2,sum3:integer;

function foo:integer;
var 
arr: array[0..15] of integer;
a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p: integer;
sum1,sum2:integer;
begin
  arr[0] := 0;
  arr[1] := 1;
  arr[2] := 2;
  arr[3] := 3;
  arr[4] := 0;
  arr[5] := 1;
  arr[6] := 2;
  arr[7] := 3;
  arr[8] := 0;
  arr[9] := 1;
  arr[10] := 2;
  arr[11] := 3;
  arr[12] := 0;
  arr[13] := 1;
  arr[14] := 2;
  arr[15] := 3;
  a := 3;
  b := 7; 
  c := 5; 
  d := 6; 
  e := 1; 
  f := 0; 
  g := 3; 
  h := 5;
  i := 4; 
  j := 2; 
  k := 7; 
  l := 9; 
  m := 8; 
  n := 1; 
  o := 4; 
  p := 6;
  sum1 := a + b + c + d + e + f + g + h;
  sum2 := i + j + k + l + m + n + o + p;

  foo := sum1 + sum2 + arr[a];
end;

begin
  a := 3;
  b := 7; 
  c := 5; 
  d := 6; 
  e := 1; 
  f := 0; 
  g := 3; 
  h := 5;
  i := 4; 
  j := 2; 
  k := 7; 
  l := 9; 
  m := 8; 
  n := 1; 
  o := 4; 
  p := 6;
  sum1 := a + b + c + d + e + f + g + h;
  sum2 := i + j + k + l + m + n + o + p;

  sum1 := sum1 + foo();

  q := 4; 
  r := 7; 
  s := 2; 
  t := 5; 
  u := 8; 
  v := 0; 
  w := 6; 
  x := 3;

  sum2 := sum2 + foo();

  a := i;
  b := j;
  c := k;
  d := l;
  e := m;
  f := n;
  g := o;
  h := p;

  sum3 := q + r + s + t + u + v + w + x;

  sum := sum1 + sum2 + sum3;

  write(sum);
end.