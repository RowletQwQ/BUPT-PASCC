program Hanoi;
const split = ',';
var
    n, t, i: integer;

procedure move(x, y: integer);
begin
    write(x,y,split);
end;

procedure hanoi(n, one, two, three: integer);
begin
    if n = 1 then
        move(one, three)
    else
    begin
        hanoi(n - 1, one, three, two);
        move(one, three);
        hanoi(n - 1, two, one, three);
    end;
end;

begin
    read(n);
    for i := 1 to n do
    begin
        read(t);
        hanoi(t, 1, 2, 3);
    end;
end.
