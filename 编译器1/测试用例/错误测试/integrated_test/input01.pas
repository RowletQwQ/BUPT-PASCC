$program testError;
const
  // error 14
  c1 = 'a'
type
    = integer;                      // error 10
var
  n: integer;
  arr: array[1..5] of integer; 
  b1, b2: boolean;
  
  v1  integer;                      // error 5
  v2: array[1..5] integer;          // error 8
  v3: array[1 10] of integer;       // error 13
  v4 := integer;                    // error 16
  v5:  ;                            // error 29

begin
  n := ((5 + 4) + 4;                // error 4
  n := 1 + ;                        // error 6
  arr[1 := 1;                       // error 12
  n := integer;                     // error 44
  n : = 1;                          // error 50
  
  // error 51
  if n > 0   
    write('x');
  
  // error 52
  repeat
    n = 5;
  
  // error 56
  if a   b then
    write('x');

// error 22
end