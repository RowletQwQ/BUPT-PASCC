program main;
const split = ',';
var
  a, b, k, i: integer;
  
function inc_a: integer;
var
  temp_b: integer;
begin
  temp_b := a;
  temp_b := temp_b + 1;
  a := temp_b;
  inc_a := a;
end;

  
begin
  a := -1;
  b := 1;
  k := 5;
  
  for i := 0 to k do
  begin
    if (inc_a <> 0) and (inc_a <> 0) and (inc_a <> 0) then
    begin
      write(a, b, split);
    end;
    
    if (inc_a < 14) or ((inc_a <> 0) and ((inc_a - inc_a + 1) <> 0)) then
    begin
      write(a, split);
      b := b * 2;
    end
    else
    begin
      inc_a;
    end;
  end;
  
  write(a,b,split);
  write(a);
end.
