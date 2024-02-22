program example(input, output);

const
  c1 = 1; 
  c2 = -c1;
  c3 = 1;
  c4 = 10;
 
type
  t1 = record x: record x1: integer; x2: real; end; y: char; end;
  t2 = array [1..10] of array ['a'..'z'] of record x: integer; y: char; end;
  t3 = array [1..10] of array [c1..c4] of array [1..10] of record x : array [1..10] of record x:integer end end;

var
  n, a, b: integer; 
  c: char;
  f: real;
  rec: t1;
  str: array[1..10] of array[1..10] of array[1..10] of char;
  arr1, arr2: t2;
  arr3: array[1..10] of array[1..10] of char;
  arr4: t3;
  
procedure swap(var x, y: integer);
var
  temp: integer;
begin
  temp := x;
  x := y;
  y := temp;
end;

function gcd(a, b: integer): integer;
begin
  if b = 0 then gcd := a
  else gcd := gcd(b, a mod b);
end;

begin
  case n of
    1, 2: 
      begin
        if n > 0 then writeln
        else
          if n >= 5 then writeln()
          else
          begin
          n := n + 1;
          writeln('n < 5')
        end;
      end;
    3:
      begin
        while n <= 3 do n := n + 1
      end;
    4:
      begin
        n := 1;
        repeat
          writeln(n);
        until n <> 3;
      end;
    5:
      begin
        for n := 3 downto 1 do
          writeln(n);
        for n := 1 to 3 do
          writeln(n);
      end
    end;
  
  // record
  rec.x.x1 := 2023;
  
  // array
  arr1[1]['a'].y := 'a';
  arr1[2] := arr1[3];
  arr2 := arr1;
  str[1][1] := arr3[1];
  arr4[1][1][1].x[1].x := 1;

  // str
  arr3[1] := 'aaa' + 'b';

  // proc and func
  writeln(gcd(a, b) + 1);
  swap(a, b);

  // std 
  writeln('abs(', n, ') = ', abs(n));
  c := 'c';
  writeln('succ(', c, ') = ', succ(c));
  writeln('round(', f, ') = ', round(f));

  // read readln write
  read(n, c, f);
  readln();
  write(' ');
end.
