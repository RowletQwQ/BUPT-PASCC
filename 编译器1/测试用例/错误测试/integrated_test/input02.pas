program TypeTest;
type 
  MyArray = array[1..10] of integer;
var 
  myVariable: real;
  i: integer;
  j: real;
  arr: array[1..5] of integer;
  index: char;
  a: MyArray;
procedure foo(a: char; b: integer);
begin
end;
begin
  if myVariable then write('x');
  if not i then write('x');
  for myVariable := 1 to 10 do write('x');

  j := 5.0;
  for i := 1 to j do write('x');

  case j of
    'a': write('x')
  end;

  index := 'i';
  arr[index] := 'a'; 

  i[1] := 2;
  i.value := 5;

  a := a + 1; 

  j := j mod 2.5; 

  if j = 'a' then write('x');
  i := j; 

  foo('a');
  foo('a', j);

end.