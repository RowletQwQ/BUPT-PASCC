program FindSmallest;

const
  space = 32;

var
  arr: array[0..999] of integer;
  n, k, i, low, high: integer;

procedure swap(a, b: integer);
var
  tmp: integer;
begin
  tmp := arr[a];
  arr[a] := arr[b];
  arr[b] := tmp;
end;

function findPivot(start, endIndex: integer): integer;
var
  pivot, pIndex, i: integer;
begin
  pivot := arr[endIndex];
  pIndex := start;

  for i := start to endIndex - 1 do
  begin
    if arr[i] <= pivot then
    begin
      swap(i, pIndex);
      pIndex := pIndex + 1;
    end;
  end;
  swap(pIndex, endIndex);
  findPivot := pIndex;
end;

procedure findSmallest(low, high, k, n: integer);
var
  pIndex, i: integer;
begin
  if low <> high then
  begin
    pIndex := findPivot(low, high);
    if k = pIndex then
    begin
      for i := 0 to pIndex - 1 do
      begin
        write(arr[i]);
      end;
    end
    else if k < pIndex then
    begin
      findSmallest(low, pIndex - 1, k, n);
    end
    else
    begin
      findSmallest(pIndex + 1, high, k, n);
    end;
  end;
end;

function getint: integer;
var
  n: integer;
begin
  read(n);
  getint := n;
end;

begin
  n := getint;
  k := getint;
  
  for i := 0 to n - 1 do
  begin
    arr[i] := getint;
  end;
  
  low := 0;
  high := n - 1;
  
  findSmallest(low, high, k, n);
end.
