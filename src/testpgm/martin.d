program main;

procedure print(val0 : integer;val1 : integer;val2 : integer;val3 : integer;val4 : integer;val5 : integer);
var
    name : array[6] of integer;
    i : integer;
begin
    name[0] :=val0;
    name[1] :=val1;
    name[2]:=val2;
    name[3]:=val3;
    name[4]:=val4;
    name[5]:=val5;
    i:=0;
    while i < 6 do
        write(name[i]);
	i:=i+1;
    end;
end;

begin
    print(77,97,114,116,105,110);
    write(10);
end.
