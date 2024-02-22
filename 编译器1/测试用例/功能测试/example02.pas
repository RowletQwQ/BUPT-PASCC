program example;
const date = 2023.5;
type string = array [1..20] of char;
var x: record
         name:string;
         data:integer;
       end;

procedure set(var x: integer);
begin
  x := trunc(date);
end;

begin
  x.name := 'Pascal-'+'S';
  set(x.data);
  writeln(x.name,' ','@',x.data);
end.
