program main;
const
space = 32;
ne = 'Not exist';
var
graph: array[0..3, 0..3] of integer;
color: array[0..3] of integer;
i, m: integer;

procedure printSolution();
var i: integer;
begin
  for i := 0 to 3 do
    write(color[i]);
end;

procedure printMessage();
begin
  write(ne);
end;

function isSafe():integer;
var i,j: integer;
begin
  isSafe := 1;
  for i := 0 to 3 do
    for j := i + 1 to 3 do
      if (graph[i, j] <> 0) and (color[j] = color[i]) then
        isSafe := 0;
end;

function graphColoring(m, i: integer): integer;
var
  j: integer;
  foundSolution: boolean;
begin
  foundSolution := false;

  if (i = 4) then
  begin
    if (isSafe() <> 0) then
    begin
      printSolution();
      graphColoring := 1;
      foundSolution := True;
    end;
  end
  else
  begin
    for j := 1 to m do
    begin
      color[i] := j;
      if (graphColoring(m, i + 1) <> 0) then
      begin
        foundSolution := True;
        Break;
      end;
      color[i] := 0;
    end;
  end;

  if foundSolution then
    graphColoring := 1
  else
    graphColoring := 0;
end;


begin
  graph[0, 0] := 0;
  graph[0, 1] := 1;
  graph[0, 2] := 1;
  graph[0, 3] := 1;
  graph[1, 0] := 1;
  graph[1, 1] := 0;
  graph[1, 2] := 1;
  graph[1, 3] := 0;
  graph[2, 0] := 1;
  graph[2, 1] := 1;
  graph[2, 2] := 0;
  graph[2, 3] := 1;
  graph[3, 0] := 1;
  graph[3, 1] := 0;
  graph[3, 2] := 1;
  graph[3, 3] := 0;
  m := 3;
  for i := 0 to 3 do
    color[i] := 0;
  if graphColoring(m, 0) = 0 then
    printMessage;
end.
