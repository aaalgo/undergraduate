program goodprg;
	const
		iterationtime=10;
	var
		result:integer;
		num1:integer;
		num2:integer;
		tag:boolean;
	procedure tentimes(i:integer);
		var
			times:integer;
		begin
			times:=iterationtime;
			while (times>=1) do
				begin
					times:=times-1;
					result:=result+i
				end
		end;
	procedure tentimesadd(j:integer;var k:integer);
		begin
			tentimes(j);
			tentimes(k)
		end;
	begin
		result:=0;
		num1:=3;
		num2:=5;
		tag:=true;
		if (num1<=0)
			then tag:=false
			else if (num2<=0)
					then tag:=false;
		if (tag=true)
			then tentimesadd(num1,num2);
		write(result)
	end.		