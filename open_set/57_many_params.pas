program main;
var
arr: array [0..31, 0..1] of integer;
i: integer;

function param32_rec(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,
                    a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
                    a31,a32: integer): integer;
begin
    if a1 = 0 then
        param32_rec := a2
    else
        param32_rec := param32_rec(a1 - 1, (a2 + a3) mod 998244353, a4, a5, a6, a7, a8, a9,
                       a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20,
                       a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31,
                       a32, 0);
end;

function param32_arr: integer;
var sum: integer;
begin
    sum := arr[0][0] + arr[0][1];
    sum := sum + arr[1][0] + arr[1][1];
    sum := sum + arr[2][0] + arr[2][1];
    sum := sum + arr[3][0] + arr[3][1];
    sum := sum + arr[4][0] + arr[4][1];
    sum := sum + arr[5][0] + arr[5][1];
    sum := sum + arr[6][0] + arr[6][1];
    sum := sum + arr[7][0] + arr[7][1];
    sum := sum + arr[8][0] + arr[8][1];
    sum := sum + arr[9][0] + arr[9][1];
    sum := sum + arr[10][0] + arr[10][1];
    sum := sum + arr[11][0] + arr[11][1];
    sum := sum + arr[12][0] + arr[12][1];
    sum := sum + arr[13][0] + arr[13][1];
    sum := sum + arr[14][0] + arr[14][1];
    sum := sum + arr[15][0] + arr[15][1];
    sum := sum + arr[16][0] + arr[16][1];
    sum := sum + arr[17][0] + arr[17][1];
    sum := sum + arr[18][0] + arr[18][1];
    sum := sum + arr[19][0] + arr[19][1];
    sum := sum + arr[20][0] + arr[20][1];
    sum := sum + arr[21][0] + arr[21][1];
    sum := sum + arr[22][0] + arr[22][1];
    sum := sum + arr[23][0] + arr[23][1];
    sum := sum + arr[24][0] + arr[24][1];
    sum := sum + arr[25][0] + arr[25][1];
    sum := sum + arr[26][0] + arr[26][1];
    sum := sum + arr[27][0] + arr[27][1];
    sum := sum + arr[28][0] + arr[28][1];
    sum := sum + arr[29][0] + arr[29][1];
    sum := sum + arr[30][0] + arr[30][1];
    sum := sum + arr[31][0] + arr[31][1];
    param32_arr := sum;
end;

function param16(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16: integer): integer;
var arr2: array[0..15] of integer;
begin
    arr2[0] := a1;
    arr2[1] := a2;
    arr2[2] := a3;
    arr2[3] := a4;
    arr2[4] := a5;
    arr2[5] := a6;
    arr2[6] := a7;
    arr2[7] := a8;
    arr2[8] := a9;
    arr2[9] := a10;
    arr2[10] := a11;
    arr2[11] := a12;
    arr2[12] := a13;
    arr2[13] := a14;
    arr2[14] := a15;
    arr2[15] := a16;
    param16 := param32_rec(arr2[0], arr2[1], arr2[2], arr2[3], arr2[4], arr2[5], arr2[6],
                     arr2[7], arr2[8], arr2[9], arr2[10], arr2[11], arr2[12], arr2[13],
                     arr2[14], arr2[15], a1, a2, a3, a4, a5, a6, a7, a8, a9, a10,
                     a11, a12, a13, a14, a15, a16);
end;

function getint(var index: integer): integer;
var input: array[0..15] of integer;
begin
    input[0] := 17;
    input[1] := 13;
    input[2] := 80;
    input[3] := 55;
    input[4] := 81;
    input[5] := 91;
    input[6] := 95;
    input[7] := 58;
    input[8] := 13;
    input[9] := 5;
    input[10] := 63;
    input[11] := 19;
    input[12] := 54;
    input[13] := 45;
    input[14] := 67;
    input[15] := 63;
    index := index + 1;
    getint := input[index - 1];
end;

begin
    i := 0;
    arr[0, 0] := param16(getint(i), getint(i), getint(i), getint(i), getint(i),
                             getint(i), getint(i), getint(i), getint(i), getint(i),
                             getint(i), getint(i), getint(i), getint(i), getint(i),
                             getint(i));
    arr[0, 1] := 8848;
    for i := 1 to 31 do
    begin
        arr[i, 0] := arr[i - 1, 1] - 1;
        arr[i, 1] := arr[i - 1, 0] - 2;
    end;
    write(param32_arr);
end.

