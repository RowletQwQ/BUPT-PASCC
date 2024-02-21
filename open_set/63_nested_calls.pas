program main;
var i, i1, i2, i3, i4, a: integer;
arr: array [0..9] of integer;

function func1(x, y, z: integer): integer;
begin
  if z = 0 then
    func1 := x * y
  else
    func1 := func1(x, y - z, 0);
end;

function func2(x, y: integer): integer;
begin
  if y <> 0 then
    func2 := func2(x mod y, 0)
  else
    func2 := x;
end;

function func3(x, y: integer): integer;
begin
  if y = 0 then
    func3 := x + 1
  else
    func3 := func3(x + y, 0);
end;

function func4(x, y, z: integer): integer;
begin
  if x <> 0 then
    func4 := y
  else
    func4 := z;
end;

function func5(x: integer): integer;
begin
  func5 := -x;
end;

function func6(x, y: integer): integer;
begin
  if (x <> 0) and (y <> 0) then
    func6 := 1
  else
    func6 := 0;
end;

function func7(x: integer): integer;
begin
  if x = 0 then
    func7 := 1
  else
    func7 := 0;
end;

begin
  i1 := 1;
  i2 := 2;
  i3 := 3;
  i4 := 4;
  for i := 0 to 9 do
    arr[i] := i + 1;
  a := func1(
      // this
      func2(
          // is
          func1(
              // comment
              func3(func4(func5(func3(func2(func6(func7(i1), func5(i2)), i3),
                                      // this
                                      i4)),
                          // is
                          arr[0],
                          // function
                          func1(func2(func3(func4(func5(arr[1]),
                                                  // call
                                                  func6(arr[2], func7(arr[3])),
                                                  func2(arr[4], func7(arr[5]))),
                                            arr[6]),
                                      arr[7]),
                                func3(arr[8], func7(arr[9])), i1)),
                    func2(i2, func3(func7(i3), i4))),
              arr[0], arr[1]),
          arr[2]),
      arr[3],
      func3(func2(func1(func2(func3(arr[4], func5(arr[5])), func5(arr[6])),
                        arr[7], func7(arr[8])),
                  func5(arr[9])),
            i1));
  write(a);
end.
