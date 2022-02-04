


program nestedPrime_;
var
   i, j:integer;

begin

   for i := 2 to 50
   begin
      for j := 2 to i do
      begin
         if (i mod j = 0)
            break ;
      end;

      if(j = i) then
         writeln( ' is prime' ) ;
   end;
end.






