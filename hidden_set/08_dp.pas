program main;

var
  t: array[0..1004, 0..1] of integer;
  dp: array[0..1004, 0..34] of integer;
  TT, W, x, i, j, res: integer;

function getint: integer;
var
  n: integer;
begin
  read(n);
  getint := n;
end;

begin
  for i := 0 to 1004 do
  begin
    t[i, 0] := 0;
    t[i, 1] := 0;
    for j := 0 to 34 do
      dp[i, j] := 0;
  end;

  TT := getint();
  W := getint();
  for i := 1 to TT do
  begin
    x := getint();
    t[i, x mod 2] := 1;
    dp[i, 0] := dp[i - 1, 0] + t[i, 1];
  end;

  for i := 1 to TT do
  begin
    for j := 1 to W do
    begin
      if (dp[i - 1, j] + t[i, (j + 1) mod 2] > dp[i - 1, j - 1] + t[i, (j + 1) mod 2]) then
      begin
        dp[i, j] := dp[i - 1, j] + t[i, (j + 1) mod 2];
      end
      else
      begin
        dp[i, j] := dp[i - 1, j - 1] + t[i, (j + 1) mod 2];
      end;
    end;
  end;

  res := 0;
  for j := 0 to W do
  begin
    if res < dp[TT, j] then
    begin
      res := dp[TT, j];
    end;
  end;
  write(res);
end.
