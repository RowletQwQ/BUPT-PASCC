program main;

const 
  INF = 32767;

var
  e: array[0..15, 0..15] of integer;
  dis, book: array[0..15] of integer;
  m, n: integer;
  u, v, i, j: integer;

procedure Dijkstra();
var
  i, min_num, min_index, k, j: integer;
begin
  for i := 1 to n do
  begin
    dis[i] := e[1, i];
    book[i] := 0;
  end;
  book[1] := 1;

  for i := 1 to n - 1 do
  begin
    min_num := INF;
    min_index := 0;
    for k := 1 to n do
    begin
      if (min_num > dis[k]) and (book[k] = 0) then
      begin
        min_num := dis[k];
        min_index := k;
      end;
    end;
    book[min_index] := 1;
    for j := 1 to n do
    begin
      if e[min_index, j] < INF then
      begin
        if dis[j] > dis[min_index] + e[min_index, j] then
          dis[j] := dis[min_index] + e[min_index, j];
      end;
    end;
  end;
end;

begin
  read(n);
  read(m);

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      if i = j then
        e[i, j] := 0
      else
        e[i, j] := INF;
    end;
  end;

  for i := 1 to m do
  begin
    read(u);
    read(v);
    read(e[u, v]);
  end;

  Dijkstra();

  for i := 1 to n do
    write(dis[i]);
  read(e[0,0]);
end.
