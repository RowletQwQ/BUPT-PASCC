program main;
  
var
  parent: array[0..1004] of integer;
  n, m, i, p, q, clusters: integer;

function getint: integer;
begin
  read(getint);
end;

function find(root: integer): integer;
begin
  if parent[root] = root then
    find := root
  else
  begin
    parent[root] := find(parent[root]);
    find := parent[root];
  end;
end;

procedure merge(p, q: integer);
var
  root_p, root_q: integer;
begin
  root_p := find(p);
  root_q := find(q);
  if root_p <> root_q then
  begin
    parent[root_q] := root_p;
  end;
end;

begin
  n := getint();
  m := getint();
  
  for i := 0 to n - 1 do
  begin
    parent[i] := i;
  end;
  
  for i := 0 to m - 1 do
  begin
    p := getint();
    q := getint();
    merge(p, q);
  end;
  
  clusters := 0;
  for i := 0 to n - 1 do
  begin
    if parent[i] = i then
      clusters := clusters + 1;
  end;
  
  write(clusters);
  read(clusters);
end.
