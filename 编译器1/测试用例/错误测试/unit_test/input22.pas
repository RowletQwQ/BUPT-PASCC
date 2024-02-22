program TestError26;
var
  arr: array[1..5] of integer;
  index: char;
begin
  index := 'i';
  arr[index] := 'a'; 
end.