program main;
const
  modn = 1000000007;

var
  dp: array[0..17, 0..17, 0..17, 0..17, 0..17, 0..6] of integer;
  list: array[0..199] of integer;
  cns: array[1..19] of integer;
  n: integer;
  i, j, k, l, m, h: integer;
  ans: integer;

function equal(a, b: integer): integer;
begin
  if a = b then
    equal := 1
  else
    equal := 0;
end;

function dfs(a, b, c, d, e, last: integer): integer;
var anss:integer;
begin
  if dp[a, b, c, d, e, last] <> -1 then
    dfs := dp[a, b, c, d, e, last];
  if a + b + c + d + e = 0 then
    dfs := 1
  else
  begin
    anss := 0;

    if a <> 0 then
      anss := (anss + (a - equal(last, 2)) * dfs(a - 1, b, c, d, e, 1)) mod modn;
    if b <> 0 then
      anss := (anss + (b - equal(last, 3)) * dfs(a + 1, b - 1, c, d, e, 2)) mod modn;
    if c <> 0 then
      anss := (anss + (c - equal(last, 4)) * dfs(a, b + 1, c - 1, d, e, 3)) mod modn;
    if d <> 0 then
      anss := (anss + (d - equal(last, 5)) * dfs(a, b, c + 1, d - 1, e, 4)) mod modn;
    if e <> 0 then
      anss := (anss + e * dfs(a, b, c, d + 1, e - 1, 5)) mod modn;
    dp[a, b, c, d, e, last] := anss mod modn;
    dfs := dp[a, b, c, d, e, last];
  end;
end;

begin
  read(n);

  for i := 0 to 17 do
  begin
    for j := 0 to 17 do
    begin
      for k := 0 to 17 do
      begin
        for l := 0 to 17 do
        begin
          for m := 0 to 17 do
          begin
            for h := 0 to 6 do
              dp[i, j, k, l, m, h] := -1;
          end;
        end;
      end;
    end;
  end;

  for i := 0 to n - 1 do
  begin
    read(list[i]);
    cns[list[i]] := cns[list[i]] + 1;
  end;

  ans := dfs(cns[1], cns[2], cns[3], cns[4], cns[5], 0);

  write(ans);
end.
