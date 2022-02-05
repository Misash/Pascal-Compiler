
program Test4;
var
   age : integer;

begin
	age := 0;
	if (age < 1) then
		begin
			Writeln('Age cannot be less than 1...');
			age := 100;
		end
	else
begin
if (age >= 100) then
begin
			Writeln('Age cannot be equal or greater than 100...');
		age := age - 20 - 30;
		end;
	end;
Write(age);
end.








