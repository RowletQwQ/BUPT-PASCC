program long_array;

function long_array(k: integer): integer;
var
  a1, a2, a3: array[0..149] of integer;
  i, j, ans: integer;
begin
  for i := 0 to 149 do
    a1[i] := (i * i) mod 10;

  for i := 0 to 149 do
    a2[i] := (a1[i] * a1[i]) mod 10;

  for i := 0 to 149 do
    a3[i] := (a2[i] * a2[i]) mod 100 + a1[i];

  ans := 0;

  for i := 0 to 149 do
  begin
    if i < 10 then
    begin
      ans := (ans + a3[i]) mod 1333;
      write(ans);
    end;

    if i < 20 then
    begin
      for j := (150 div 2) to 149 do
        ans := ans + a3[i] - a1[j];
      write(ans);
    end;

    if i < 30 then
    begin
      for j := 150 div 2 to 149 do
      begin
        if j > 2233 then
        begin
          ans := ans + a2[i] - a1[j];
        end
        else
        begin
          ans := (ans + a1[i] + a3[j]) mod 13333;
        end;
      end;
      write(ans);
    end
    else
    begin
      ans := (ans + a3[i] * k) mod 99988;
    end;
  end;

  long_array := ans;
end;

begin
  write(long_array(9));
end.
