program main;
var
  ret, a, b, c, d, e, f: integer;
begin
  ret := 0;
  a := 1;
  b := 2;
  c := 3;
  d := 4;
  e := 5;
  f := 6;

  if (a * b + c < 6) and (d <> 0) then
  begin
    if (e <> 0) or (not(a + 0 <> 0)) then
    begin
      if (c = 2) and (d + e > 2) then
        ret := 3
      else
      begin
        if (f mod c <> 0) and (e <> 0) then
          ret := 4
        else
        begin
          if (d div b + a >= 2) then
          begin
            if (e - f >= 0) or (d > 4) then
              ret := 6
            else
            begin
              if (c <> f) then
              begin
                if (b + e * d > 10) then
                begin
                  if (f = 0) then
                    ret := 9
                  else
                    ret := 10;
                end
                else
                  ret := 8;
              end
              else
                ret := 7;
            end;
          end
          else
            ret := 5;
        end;
      end;
    end
    else
      ret := 2;
  end
  else
    ret := 1;

  write(ret);
end.
