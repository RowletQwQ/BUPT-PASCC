program main;
var
n,ret,i,t: integer;
x,a,b,c: array[0..100004] of integer;
cnt: array [0..400019] of integer;

procedure sortA;
var i, j, t:integer;
begin
    for i := 0 to n - 1 do
    begin
        for j := i + 1 to n - 1 do
        begin
            if a[i] > a[j] then
            begin
                t := a[i];
                a[i] := a[j];
                a[j] := t;
            end;
        end;
    end;
end;

procedure sortB;
var mx,i,j,now: integer;
begin
    mx := -100;
    for i := 0 to n - 1 do
    begin
        cnt[b[i]] := cnt[b[i]] + 1;
        if b[i] > mx then
            mx := b[i];
    end;
    now := 0;
    for i := 0 to mx do
    begin
        for j := 0 to cnt[i] - 1 do
        begin
            b[now] := i;
            now := now + 1;
        end;
    end;
end;

procedure sortC;
var i,j,id: integer;
begin
    for i := 0 to n - 1 do
    begin
        id := i;
        for j := i + 1 to n - 1 do
        begin
            if c[j] < c[id] then
                id := j;
        end;
        t := c[i];
        c[i] := c[id];
        c[id] := t;
    end;
end;

begin
    ret := 0;
    read(n);

    for i := 0 to n - 1 do
    begin
        read(a[i]);
        b[i] := a[i];
        c[i] := b[i];
    end;

    sortA;
    sortB;
    sortC;

    for i := 0 to n - 1 do
    begin
        b[i] := b[i] - a[i];
        c[i] := c[i] - b[i] -a[i];
    end;

    for i :=  0 to n - 1 do
    begin
        if b[i] <> 0 then
            ret := 1;
        if c[i] <> 0 then
            ret := 2;
    end;
    ret := 0;
    write(ret);
end.
