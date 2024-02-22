program testError;
const
    // error 1
    declared_const = 10;
    declared_const = 10;
    x = undifined_const;                            // error 25
type
    declared_type = integer;
    declared_type = real;
var 
    error_arr : array [1.2..10.2] of integer;       // error syntax
    error_arr2 : array [10..1] of char;             // error syntax
    // error 1
    declared_var : integer;
    declared_var : integer;
    Undefined_type_var: undefined_type;             // error semantic                      
    a: boolean;
    b: record x: int32; end;                        // error semantic
    c:array [1..10] of integer;
function declared_func: integer;
const
    y = declared_var;                               // error 25
begin
end;
// error semantic
function declared_func(declared_var: integer; declared_var: real): integer;     
begin
end;
begin
  declared_func := 1;                               // error semantic                           
  undefined_var := 1;                               // error 0
  undeclared_func();                                // error semantic
  undeclared_func;                                  // error semantic
  case declared_var of
    1, 2.1: writeln('n is between 1 and 3')         // error syntax
  end;
  read(c);                                          // error 40
  write(c);                                         // error 41
end.