program BinarySearchTree;

var
  value: array[0..9999] of integer;
  left_child: array[0..9999] of integer;
  right_child: array[0..9999] of integer;
  now: integer;
  ret, n, readN, i, root: integer;

function search(root, x: integer): integer;
begin
  if (root = -1) or (value[root] = x) then
    search := root
  else 
  begin
    if (x > value[root]) then
      search := search(right_child[root], x)
    else
      search := search(left_child[root], x);
  end;
end;

function find_minimum(root: integer): integer;
begin
  if (root = -1) then
    find_minimum := -1
  else 
  begin
    if (left_child[root] <> -1) then
      find_minimum := find_minimum(left_child[root])
    else
      find_minimum := root;
  end;
end;

function new_node(x: integer): integer;
begin
  value[now] := x;
  left_child[now] := -1;
  right_child[now] := -1;
  new_node := now;
  now := now + 1;
end;

function insert(root, x: integer): integer;
begin
  if (root = -1) then
    insert := new_node(x)
  else 
  begin
    if (x > value[root]) then
      right_child[root] := insert(right_child[root], x)
    else
      left_child[root] := insert(left_child[root], x);
  end;
  insert := root;
end;

function delete_node(root, x: integer): integer;
var
  tmp: integer;
begin
  if (x > value[root]) then
begin
    right_child[root] := delete_node(right_child[root], x);
end
else
begin
    if (x < value[root]) then
    begin
        left_child[root] := delete_node(left_child[root], x);
    end
    else
    begin
        if (left_child[root] = -1) and (right_child[root] = -1) then
        begin
            delete_node := -1;
        end
        else
        begin
            if (left_child[root] = -1) or (right_child[root] = -1) then
            begin
                if (left_child[root] = -1) then
                begin
                    delete_node := right_child[root];
                end
                else
                begin
                    delete_node := left_child[root];
                end;
            end
            else
            begin
                tmp := find_minimum(right_child[root]);
                value[root] := value[tmp];
                right_child[root] := delete_node(right_child[root], value[tmp]);
            end;
        end;
    end;
end;
  delete_node := root;
end;

procedure inorder(root: integer);
begin
  if (root <> -1) then
  begin
    inorder(left_child[root]);
    write(value[root], ' ');
    inorder(right_child[root]);
  end;
end;



begin
  ret := 0;
  now := 0;

  read(n);
  if (n = 0) then
    ret := 0;

  read(readN);
  root := new_node(readN);

  for i := 1 to n - 1 do
  begin
    read(readN);
    insert(root, readN);
  end;

  inorder(root);

  read(n);
  for i := 1 to n do
  begin
    read(readN);
    root := delete_node(root, readN);
  end;

  inorder(root);
end.
