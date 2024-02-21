program main;
var ret:integer;

function Fn(f: integer): integer;
begin
    Fn := f * 2;
end;

begin
    ret := 0;
    ret := Fn(10);
    write(ret);
end.
