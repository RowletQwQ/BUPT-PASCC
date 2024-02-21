program main;
const e = 2.1718281828459045;
split = '--';
var
x,y:real;
num,i:integer;

function my_fabs(x: real):real;
begin
    if x > 0 then
        my_fabs := x
    else
        my_fabs := -x;
end;

function my_pow(a:real; n: integer):real;
var i:integer; res: real;
begin
    if n < 0 then
        my_pow := 1 / (my_pow(a, -n))
    else
    begin
        res := 1.0;
        for i := 0 to n - 1 do
            res := res * a;
        my_pow := res;
    end;
end;

function my_sqrt(x:real):real;
var t:real; c:integer;
begin
    if x > 100 then
        my_sqrt := 10.0 * my_sqrt(x / 100)
    else
    begin
        t := x / 8 + 0.5 + 2 * x / (4 + x);
        for c := 0 to 9 do
            t := (t + x / t) / 2;
        my_sqrt := t;
    end
end;

function F1(x:real):real;
begin
    F1 := 1 / x;
end;

function F2(x:real):real;
begin
    F2 := 1 / my_sqrt(1 - x * x);
end;

function simpson(a,b: real; flag: integer): real;
var c:real;
begin
    c := a + (b - a) / 2;
    simpson := 0;
    if flag = 1 then
        simpson := (F1(a) + 4 * F1(c) + F1(b)) * (b - a) / 6
    else
        simpson := (F2(a) + 4 * F2(c) + F2(b)) * (b - a) / 6;
end;

function asr5(a,b,eps,AA: real; flag:integer):real;
var c,L,R:real;
begin
    c := a + (b - a) / 2;
    L := simpson(a, c, flag);
    R := simpson(c, b, flag);
    if my_fabs(L + R - AA) <= (15 * eps) then
        asr5 := L + R + (L + R - AA) / 15.0
    else
        asr5 := asr5(a, c, eps/2, L, flag) + asr5(c, b, eps/2, R, flag);
end;

function asr4(a,b,eps:real; flag: integer):real;
begin
    asr4 := asr5(a, b, eps, simpson(a, b, flag), flag);
end;

function eee(x:real):real;
var ee: real;
begin
    if x > 0.001 then
    begin
        ee := eee(x / 2);
        eee := ee * ee;
    end
    else
        eee := 1 + x + x * x / 2 + my_pow(x, 3) / 6 + my_pow(x, 4) / 24 + my_pow(x, 5) / 120;
end;

function my_exp(x:real):real;
var e1,e2: real; n: integer;
begin
    if x < 0 then
        my_exp := 1 / my_exp(-x)
    else
    begin
    //pascal no cut the integer part and float part
        n := 1;
        x := x - 1.0;
        e1 := my_pow(e, n);
        e2 := eee(x);
        my_exp := e1 * e2;
    end;
end;

function my_ln(x:real):real;
begin
    my_ln := asr4(1, x, 0.00000001, 1);
end;

function my_log(a,N: real):real;
begin
    my_log := my_ln(N) / my_ln(a);
end;

function my_powf(a,x:real):real;
begin
    my_powf := my_exp(x * my_ln(a));
end;

procedure putfloat(f:real);
begin
    write(f);
end;


function getfloat():real;
begin
    read(getfloat);
end;

begin
    num := 2;
    for i := 0 to num - 1 do
    begin
        x := getfloat;
        y := getfloat;
        putfloat(my_fabs(x));
        putfloat(my_pow(x, 2));
        putfloat(my_sqrt(x));
        putfloat(my_exp(x));

        if x > 0.0 then
            putfloat(my_ln(x))
        else
            write(split);

        if (x > 0.0) and (y > 0.0) then
            putfloat(my_log(x, y))
        else
            write(split);
        
        if x > 0.0 then
            putfloat(my_powf(x, y))
        else
            write(split);
    end;
    read(num);
end.
