{ test comment }
program main;
var a: integer;
begin
  a := 5;
  {
    int b = 4;
    a = b + a;
    (*/*
      b = 1;
      // b = 2;
    *)
  }
  write(a);
end.