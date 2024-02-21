program main;
var
arr1: array[0..9,0..1,0..2,0..3,0..4,0..5,0..1] of integer;
arr2: array[0..9,0..1,0..2,0..1,0..3,0..7,0..6] of integer;
x,y,h,i,j,k,l,m,n,ret:integer;

procedure loop1(x,y:integer);
var
a,b,c,d,e,f,g:integer;
begin
for a := 0 to x-1 do
  begin
    for b := 0 to 1 do
    begin
      for c := 0 to 2 do
      begin
        for d := 0 to 3 do
        begin
          for e := 0 to 4 do
          begin
            for f := 0 to 5 do
            begin
              for g := 0 to 1 do
              begin
                arr1[a][b][c][d][e][f][g] := a + b + c + d + e + f + g + x + y;
              end;
            end;
          end;
        end;
      end;
    end;
  end;
end;

procedure loop2;
var
a,b,c,d,e,f,g:integer;
begin
for a := 0 to 9 do
  begin
    for b := 0 to 1 do
    begin
      for c := 0 to 2 do
      begin
        for d := 0 to 1 do
        begin
          for e := 0 to 3 do
          begin
            for f := 0 to 7 do
            begin
              for g := 0 to 6 do
              begin
                arr2[a][b][c][d][e][f][g] := a + b + d + g;
              end;
            end;
          end;
        end;
      end;
    end;
  end;
end;

function loop3(h,i,j,k,l,m,n: integer):integer;
var ans,a,b,c,d,e,f,g: integer;
begin
ans := 0;
  for a := 0 to h-1 do
  begin
    for b := 0 to i-1 do
    begin
      for c := 0 to j-1 do
      begin
        for d := 0 to k-1 do
        begin
          for e := 0 to l-1 do
          begin
            for f := 0 to m-1 do
            begin
              for g := 0 to n-1 do
              begin
                ans := (ans mod 817) + arr1[a][b][c][d][e][f][g] + arr2[a][b][c][d][e][f][g];
              end;
            end;
          end;
        end;
      end;
    end;
  end;
  loop3 := ans;
end;

begin
  ret := 0;
  x := 1;
  y := 2;
  h := 3;
  i := 4;
  j := 5;
  k := 6;
  l := 7;
  m := 8;
  n := 9;
  loop1(x,y);
  loop2();
  ret := loop3(h,i,j,k,l,m,n);
  write(ret);
end.