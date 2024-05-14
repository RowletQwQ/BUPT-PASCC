program ProcedureError;
var
  a: integer;

procedure WriteNumber(a: integer); // 错误：过程体缺失

begin
  WriteNumber(3);
end.