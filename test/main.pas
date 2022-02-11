
program Test4;
const num1 = 11;
      num2 = 27;
var
   age : integer ; age2 : string;

begin
	age := 0;
	age2 := 'hola mundo';

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
Write(age2);
end.








