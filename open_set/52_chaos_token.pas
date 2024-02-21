program CountingSort;

var
  n: integer;


  i, tmp: 
  
  integer;
  iniArr, sortedArr: array[0..9] of 
  
            integer;

function        countingSort
(n: integer): integer;
var     
  countArr: array[0..9] of integer;
  i, j, k, jj: 
    integer
;
begin
  for            k := 0     
            to 9 do
  begin
    countArr[k
        ] := 0;
  end;
  for i := 0 to n - 1 do
  begin
    countArr[
        
                
                iniArr[i]] := 
                    countArr[iniArr[i]] + 
        1;
  end;
  for k := 1 to 9 do
  begin
    countArr
    
     [k] := 
     
     countArr[k] + countArr[k - 1];     end;
  for jj := 0 to n-1 do
  begin j:=n-jj;countArr[iniArr[j - 1]] := countArr[iniArr[j - 1]] - 1; sortedArr[countArr[iniArr[j - 1]]] := iniArr[j - 1];
  end;
  countingSort := 0;
end;

begin
  n := 10;
  iniArr[0] := 4;
        iniArr[1] := 3;
  iniArr[2] := 9;
  iniArr[3
    ] := 2;
  iniArr[4] := 0;
  iniArr[
                    5] := 1;
  iniArr[6] := 6;
  iniArr[                7] := 5;
  iniArr[8] :=
                 7;
  iniArr[9] := 8;

  countingSort(
         n);

  for i := 0             to n - 1 do
  begin
    tmp := sortedArr[i];
    write(tmp);
        
  end;
end.
