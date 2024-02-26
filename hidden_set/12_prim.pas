program main;
var
n, m: integer;
ret,i: integer;
u,v,c,fa: array [0..1004] of integer;

function find(x: integer):integer;
var asdf: integer;
begin
  if x = fa[x] then
    find := x
  else
  begin
    asdf := find(fa[x]);
    fa[x] := asdf;
    find := asdf;
  end;
end;

function same(x,y: integer):integer;
begin
  x := find(x);
  y := find(y);
  if x = y then
    same := 1
  else
    same := 0;
end;

function prim:integer;
var i,j,t,res: integer;
begin
  for i := 0 to m - 1 do
  begin
    for j := i + 1 to m - 1 do
    begin
      if c[i] > c[j] then
      begin
        t := u[i];
        u[i] := u[j];
        u[j] := t;
        t := v[i];
        v[i] := v[j];
        v[j] := t;
        t := c[i];
        c[i] := c[j];
        c[j] := t;
      end;
    end;
  end;

  for i := 1 to n do
    fa[i] := i;
  res := 0;
  for i := 0 to m - 1 do
  begin
    if same(u[i], v[i]) = 0 then
    begin
      res := res + c[i];
      fa[find(u[i])] := v[i];
    end;
  end;

  prim := res;
end;

begin
  ret := 0;
  read(n);
  read(m);
  for i := 0 to m - 1 do
  begin
    read(u[i]);
    read(v[i]);
    read(c[i]);
  end;

  ret := prim;
  write(ret);
end.
