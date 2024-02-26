program main;
function if_ifElse_: integer;
var
    a, b: integer;
begin
    a := 5;
    b := 10;
    if (a = 5) then
    begin
        if (b = 10) then
            a := 25
        else
            a := a + 15;
    end;
    if_ifElse_ := a;
end;

begin
    write(if_ifElse_);
end.
