program NestedLoops;
var
  a, i, j, k, ii, jj, kk, iii, jjj, kkk, iiii, jjjj, kkkk, iiiii, jjjjj, kkkkk: integer;
begin
  a := 0;
  for i := 0 to 2 do
  begin
    for j := 0 to 3 do
    begin
      for k := 0 to 4 do
      begin
        for ii := 0 to 2 do
        begin
          for jj := 0 to 4 do
          begin
            for kk := 0 to 3 do
            begin
              for iii := 0 to 5 do
              begin
                for jjj := 0 to 4 do
                begin
                  for kkk := 0 to 4 do
                  begin
                    for iiii := 0 to 2 do
                    begin
                      for jjjj := 0 to 5 do
                      begin
                        for kkkk := 0 to 6 do
                        begin
                          for iiiii := 0 to 4 do
                          begin
                            for jjjjj := 0 to 2 do
                            begin
                              for kkkkk := 0 to 5 do
                              begin
                                a := (a + 3) mod 999;
                              end;
                            end;
                          end;
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;
      end;
    end;
  end;

  write(a);
end.
