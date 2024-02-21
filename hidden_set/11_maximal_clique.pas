program MaxClique;

var
  store: array[0..29] of integer;
  n, m: integer;
  graph: array[0..29, 0..29] of integer;
  edges: array[0..599, 0..1] of integer;
  i, ret: integer;

function is_clique(num: integer): integer;
var
  i, j: integer;
begin
  is_clique := 1;
  for i := 1 to num - 1 do
  begin
    for j := i + 1 to num - 1 do
    begin
      if graph[store[i], store[j]] = 0 then
        is_clique := 0;
    end;
  end;
end;

function maxCliques(i, k: integer): integer;
var
  max_, j, tmp: integer;
begin
  max_ := 0;
  for j := 1 to n do
  begin
    store[k] := j;
    if is_clique(k + 1) <> 0 then
    begin
      if k > max_ then
        max_ := k;
      tmp := maxCliques(j, k + 1);
      if tmp > max_ then
        max_ := tmp;
    end;
  end;
  maxCliques := max_;
end;

begin
  read(n);
  read(m);
  for i := 0 to m - 1 do
  begin
    read(edges[i, 0]);
    read(edges[i, 1]);
  end;
  for i := 0 to m - 1 do
  begin
    graph[edges[i, 0], edges[i, 1]] := 1;
    graph[edges[i, 1], edges[i, 0]] := 1;
  end;
  ret := maxCliques(0, 1);
  write(ret);
end.
