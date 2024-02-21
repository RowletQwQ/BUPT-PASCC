program main;
var
sum, i, ans: integer;
arr: array[0..19] of integer;

function f(i, j: integer): integer;
begin
    sum := sum + 1;
    if (i >= j) or (i >= 20) then
        f := 0
    else
    begin
        arr[i] := 1;
        if i = 0 then
            f := arr[0]
        else
            f := arr[i - 1];
    end;
end;

function g(i,j: integer):integer;
begin
    sum := sum + 2;
    if (i >= j) or (i >= 20) then
        g := 1
    else
    begin
        arr[i] := 0;
        if i = 0 then
            g := arr[0]
        else
            g := arr[i - 1];
    end;
end;

function h(i: integer): integer;
begin
    sum := sum + 3;
    if (i < 0) or (i >= 20) then
        h := 0
    else
        h := arr[i];
end;

begin
    for i := 0 to 19 do
        arr[i] := 0;
    for i := 0 to 19 do
    begin
        if (f(0, i) <> 0) and (f(1, i) <> 0) and (f(2, i) <> 0) and (f(3, i) <> 0) and (f(4, i) <> 0) and
            (f(5, i) <> 0) and (f(6, i) <> 0) and (f(7, i) <> 0) and (f(8, i) <> 0) and (f(9, i) <> 0) and
            (f(10, i) <> 0) and (f(11, i) <> 0) and (f(12, i) <> 0) and (f(13, i) <> 0) and (f(14, i) <> 0) and
            (f(15, i) <> 0) and (f(16, i) <> 0) and (f(17, i) <> 0) and (f(18, i) <> 0) and (f(19, i) <> 0) then
        ;
    end;

    for i := 0 to 19 do
    begin
        if (g(0, i) <> 0) or (g(1, i) <> 0) or (g(2, i) <> 0) or (g(3, i) <> 0) or (g(4, i) <> 0) or
            (g(5, i) <> 0) or (g(6, i) <> 0) or (g(7, i) <> 0) or (g(8, i) <> 0) or (g(9, i) <> 0) or
            (g(10, i) <> 0) or (g(11, i) <> 0) or (g(12, i) <> 0) or (g(13, i) <> 0) or (g(14, i) <> 0) or
            (g(15, i) <> 0) or (g(16, i) <> 0) or (g(17, i) <> 0) or (g(18, i) <> 0) or (g(19, i) <> 0) then
        ;
    end;

    ans := 0;
    if (h(0) <> 0) and (h(1) <> 0) or (not (h(2) <> 0)) or (h(3) <> 0) then
        ans := 1;
    ans := 0;
    if (not (h(4) <> 0)) or (h(5) <> 0) and (not (h(6) <> 0)) and (h(7) <> 0) or (not (h(8) <> 0)) then
        ans := 1;
    ans := 0;
    if (h(9) <> 0) and (not (h(10) <> 0)) or (not (h(11) <> 0)) or (not (h(12) <> 0)) or (not (h(13) <> 0)) or (h(14) <> 0) and (h(15) <> 0) then
        ans := 1;
    ans := 0;
    if (h(0) <> 0) and (h(2) <> 0) and (not (h(3) <> 0)) and (not (h(4) <> 0)) or (h(5) <> 0) or (h(6) <> 0) and (not (h(7) <> 0)) or (h(8) <> 0) then
        ans := 1;
    write(sum + ans); 
end.
