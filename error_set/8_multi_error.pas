poragam 1;   // err 1

const
  x = 10;
  a == 2;  // err 2

var
  a, b: integer;
  c: ; // err 3

function set_a(val: integer) ; // err 4
begin
  a := ;    // err 5
  set_a == val; // err 6
end;

begin
  1 := ; // err 7
  a := ; // err 8
  integer := 3  // err 9
  a := 4;
end