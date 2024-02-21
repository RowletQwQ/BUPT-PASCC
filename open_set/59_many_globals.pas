program main;
var
a0,a1,a2,a3,a4,a5,a6,a7,a8,a9:integer;
a10,a11,a12,a13,a14,a15,a16,a17,a18,a19:integer;
a20,a21,a22,a23,a24,a25,a26,a27,a28,a29:integer;
a30,a31,a32,a33,a34,a35,a36,a37,a38,a39:integer;

function testParam8(a0,a1,a2,a3,a4,a5,a6,a7: integer): integer;
begin
  testParam8 := a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7;
end;

function testParam16(a0,a1,a2,a3,a4,a5,a6,a7
                ,a8,a9,a10,a11,a12,a13,a14,a15: integer):integer;
begin
  testParam16 := a0 + a1 + a2 - a3 - a4 - a5 - a6 - a7 +
            a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15;
end;

function testParam32(a0,a1,a2,a3,a4,a5,a6,a7
                ,a8,a9,a10,a11,a12,a13,a14,a15,
                a16,a17,a18,a19,a20,a21,a22,a23,
                a24,a25,a26,a27,a28,a29,a30,a31: integer):integer;
begin
  testParam32 := a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 +
            a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 +
            a16 + a17 - a18 - a19 - a20 - a21 - a22 + a23 +
            a24 + a25 + a26 + a27 + a28 + a29 + a30 + a31;
end;

begin
        a0 := 0;
        a1 := 1;
        a2 := 2;
        a3 := 3;
        a4 := 4;
        a5 := 5;
        a6 := 6;
        a7 := 7;
        a8 := 8;
        a9 := 9;
        a10 := 0;
        a11 := 1;
        a12 := 2;
        a13 := 3;
        a14 := 4;
        a15 := 5;
        a16 := 6;
        a17 := 7;
        a18 := 8;
        a19 := 9;
        a20 := 0;
        a21 := 1;
        a22 := 2;
        a23 := 3;
        a24 := 4;
        a25 := 5;
        a26 := 6;
        a27 := 7;
        a28 := 8;
        a29 := 9;
        a30 := 0;
        a31 := 1;

        a32 := 4;
        a33 := 5;
        a34 := 6;
        a35 := 7;
        a36 := 8;
        a37 := 9;
        a38 := 0;
        a39 := 1;
        a0 := testParam8(a0, a1, a2, a3, a4, a5, a6, a7);
        write(a0);
        a0 := testParam16(a32, a33, a34, a35,
                         a36, a37, a38, a39,
                         a8, a9, a10, a11,
                         a12, a13, a14, a15);
        write(a0);
        a0 := testParam32(a0, a1, a2, a3,
                         a4, a5, a6, a7,
                         a8, a9, a10, a11,
                         a12, a13, a14, a15,
                         a16, a17, a18, a19,
                         a20, a21, a22, a23,
                         a24, a25, a26, a27,
                         a28, a29, a30, a31);
        write(a0);
end.
