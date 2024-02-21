program main;
var 
arr: array[0..109] of integer;
n: integer;
m, a, b, k, loc, i: integer;
flag: boolean;

procedure init(n: integer);
var i: integer;
begin
  for i := 1 to n * n + 1 do
    arr[i] := -1;
end;

function findfa(a: integer):integer;
begin
  if arr[a] = a then
    findfa := a
  else
  begin
    arr[a] := findfa(arr[a]);
    findfa := arr[a];
  end;
end;

procedure mmerge(a, b: integer);
var m, n: integer;
begin
  m := findfa(a);
  n := findfa(b);
  if m <> n then
    arr[m] := n;
end;

begin
  n := 4;
  m := 10;
  flag := false;
  init(n);
  k := n * n + 1;

  for i := 0 to m - 1 do
  begin
    read(a);
    read(b);
    if flag = false then
    begin
      loc := n * (a - 1) + b;
      arr[loc] := loc;
      if a = 1 then
      begin
        arr[0] := 0;
        mmerge(loc, 0);
      end;
      if a = n then
      begin
        arr[k] := k;
        mmerge(loc, k);
      end;

      if (b < n) and (arr[loc + 1] <> -1) then
        mmerge(loc, loc + 1);
      if (b > 1) and (arr[loc - 1] <> -1) then
        mmerge(loc, loc - 1);
      if (a < n) and (arr[loc + n] <> -1) then
        mmerge(loc, loc + n);
      if (a > 1) and (arr[loc - n] <> -1) then
        mmerge(loc, loc - n);

      if (arr[0] <> -1) and (arr[k] <> -1) and (findfa(0) = findfa(k)) then
      begin
        flag := true;
        write(i + 1);
      end;
    end;
  end;

  if flag = false then
    write(-1);
end.
