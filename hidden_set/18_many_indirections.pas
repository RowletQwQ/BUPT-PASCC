program main;
const N=100;M=20;
var 
arr: array[0..99, 0..19] of integer;
i,j,sum:integer;

begin
    for i := 0 to M -1 do
    begin
        for j := 0 to N - 1 do
        begin
            arr[i, j] := j;
        end;
    end;
    sum := arr[0, arr[1, arr[2, arr[3, arr[4, arr[5, arr[6, arr[7, arr[8,arr[9,arr[10,arr[11,arr[12,arr[13,arr[14,arr[15,arr[16,arr[17,arr[18,arr[19,19]]]]]]]]]]]]]]]]]]]] + 
            arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr
                                                                                  [arr[arr[arr[arr[arr[arr[arr[19,18],
                                                                                                                17],16],15],14],13],12],11],10],9],8],7],6],5],4],3],2],1],0],19];
    write(sum);                                                                                                          
end.