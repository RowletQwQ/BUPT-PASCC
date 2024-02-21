program main;
var
k: integer;
i,j: integer;
ret0, ret1: real;
arr: array[0..39, 0..2] of real;
arr2: array[0..23, 0..2] of integer;

function params_f40(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13,
                    x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24,
                    x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35,
                    x36, x37, x38, x39: real): real;
var
i: integer;
arr: array[0..9] of real;
begin
    if x39 <> 0 then
    begin
        arr[0] := x0+x1+x2+x3;
        arr[1] := x4+x5+x6+X7;
        arr[2] := x8+x9+x10+x11;
        arr[3] := x12+x13+x14+x15;
        arr[4] := x16+x17+x18+x19;
        arr[5] := x20+x21+x22+x23;
        arr[6] := x24+x25+x26+x27;
        arr[7] := x28+x29+x30+x31;
        arr[8] := x32+x33+x34+x35;
        arr[9] := x36+x37+x38+x39;
        for i :=  0 to 9 do
            write(arr[i]);
        params_f40 := arr[k];
    end
    else
    begin
        params_f40 := params_f40(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13,
                      x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24,
                      x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35,
                      x36, x37, x38, x39, x0 + x1 + x2);
    end;
end;

function params_f40_i24(i23, i2, i6: integer; x4: real; i1, i4, i5: integer;
                        x8, x15, x7: real; i22: integer; x3: real;
                        x28: real; i0: integer; x37: real; i19: integer; x30: real;
                        x12, x1, x11, x38, x6: real; i7: integer; x32: real; i10, i13: integer;
                        x20, x33, x23, x9, x25: real; i8: integer; x39: real; i17: integer;
                        x21, x16, x5, x34: real; i18, i9: integer; x14, x10, x0: real;
                        i12: integer; x31: real; i11, i16: integer; x27, x24, x13, x29: real;
                        i3, i21, i20: integer; x18, x19, x22, x26, x36, x17: real;
                        i15: integer; x2: real; i14: integer; x35: real): real;
var
i : integer;
arr : array[0..9] of real;
arr2: array[0..7] of real;
begin
    if i23 <> 0 then
    begin
        arr[0] := x0+x1+x2+x3;
        arr[1] := x4+x5+x6+X7;
        arr[2] := x8+x9+x10+x11;
        arr[3] := x12+x13+x14+x15;
        arr[4] := x16+x17+x18+x19;
        arr[5] := x20+x21+x22+x23;
        arr[6] := x24+x25+x26+x27;
        arr[7] := x28+x29+x30+x31;
        arr[8] := x32+x33+x34+x35;
        arr[9] := x36+x37+x38+x39;
        arr2[0] := (i0 + i1 + i2) * 1.0;
        arr2[1] := (i3 + i4 + i5) * 1.0;
        arr2[2] := (i6 + i7 + i8) * 1.0;
        arr2[3] := (i9 + i10 + i11) * 1.0;
        arr2[4] := (i12 + i13 + i14) * 1.0;
        arr2[5] := (i15 + i16 + i17) * 1.0;
        arr2[6] := (i18 + i19 + i20) * 1.0;
        arr2[7] := (i21 + i22 + i23) * 1.0;
        for i :=  0 to 9 do
            write(arr[i]);
        for i :=  0 to 7 do
            write(arr2[i]);
        for i :=  0 to 7 do
            arr2[i] := arr2[i] - arr[i];
        params_f40_i24 := arr2[k];
    end
    else
        params_f40_i24 := params_f40_i24(i1, i2, i6, x4, i1, i4, i5, x8, x15, x7, i22, x3, x28,
                          i0, x37, i19, x30, x12, x1, x11, x38, x6, i7, x32,
                          i10, i13, x20, x33, x23, x9, x25, i8, x39, i17, x21,
                          x16, x5, x34, i18, i9, x14, x10, x0, i12, x31, i11,
                          i16, x27, x24, x13, x29, i3, i21, i20, x18, x19, x22,
                          x26, x36, x17, i15, x2, i14, x35);
end;

begin
    k := 0;
    for i := 0 to 23 do
        for j := 0 to 2 do
            arr2[i ,j] := i * 2 - j * 3;
    for i := 0 to 39 do
        for j := 0 to 2 do
            arr[i, j] := i * 2.2 - j * 3.3;
    
    ret0 := params_f40(
      arr[0][k], arr[1][k], arr[2][k], arr[3][k], arr[4][k], arr[5][k],
      arr[6][k], arr[7][k], arr[8][k], arr[9][k], arr[10][k], arr[11][k],
      arr[12][k], arr[13][k], arr[14][k], arr[15][k], arr[16][k], arr[17][k],
      arr[18][k], arr[19][k], arr[20][k], arr[21][k], arr[22][k], arr[23][k],
      arr[24][k], arr[25][k], arr[26][k], arr[27][k], arr[28][k], arr[29][k],
      arr[30][k], arr[31][k], arr[32][k], arr[33][k], arr[34][k], arr[35][k],
      arr[36][k], arr[37][k], arr[38][k], arr[39][k]);

    ret1 := params_f40_i24(
      arr2[23][k], arr2[2][k], arr2[6][k], arr[4][k], arr2[1][k], arr2[4][k],
      arr2[5][k], arr[8][k], arr[15][k], arr[7][k], arr2[22][k], arr[3][k],
      arr[28][k], arr2[0][k], arr[37][k], arr2[19][k], arr[30][k], arr[12][k],
      arr[1][k], arr[11][k], arr[38][k], arr[6][k], arr2[7][k], arr[32][k],
      arr2[10][k], arr2[13][k], arr[20][k], arr[33][k], arr[23][k], arr[9][k],
      arr[25][k], arr2[8][k], arr[39][k], arr2[17][k], arr[21][k], arr[16][k],
      arr[5][k], arr[34][k], arr2[18][k], arr2[9][k], arr[14][k], arr[10][k],
      arr[0][k], arr2[12][k], arr[31][k], arr2[11][k], arr2[16][k], arr[27][k],
      arr[24][k], arr[13][k], arr[29][k], arr2[3][k], arr2[21][k], arr2[20][k],
      arr[18][k], arr[19][k], arr[22][k], arr[26][k], arr[36][k], arr[17][k],
      arr2[15][k], arr[2][k], arr2[14][k], arr[35][k]);

      write(ret0);
      write(ret1);
end.
