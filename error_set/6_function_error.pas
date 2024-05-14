program FunctionError;
var
  a: integer;

function AddNumbers(a, b: integer); // 错误：没有指定函数的返回类型
begin
  Result := a + b;
end;

begin
  a := AddNumbers(3, 4);
end.