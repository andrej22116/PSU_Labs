/*
	Функция регистрирует нового пользователя,
	если пользователя с текущем логином и никнеймом ещё не существует.
*/
create or replace function public_function_registration(login text, password text, nickname text)
returns void
as $f_body$
	declare
		login_length integer;
		password_length integer;
		nickname_length integer;
		has_login boolean;
	begin
		login_length := length(login);
		password_length := length(password);
		
		if login_length < 6 or login_length > 32 then
			raise 'Login must be between 6 and 32 characters!';
		end if;
		
		if password_length < 6 or password_length > 64 then
			raise 'Password must be between 6 and 64 characters!';
		end if;
	
		if nickname_length < 6 or nickname_length > 32 then
			raise 'Nickname must be between 6 and 32 characters!';
		end if;
		
		select exists (select users.user_login from users where users.user_login = crypt(login, users.user_login)) into has_login;
		if has_login = true then
			raise 'This username "%" already exist!', login;
		end if;
	
		insert into users (user_login, user_password, id_role, user_nickname)
		values (crypt(login, gen_salt('bf', 8)), crypt(password, gen_salt('bf', 8)), 0, nickname);
	end
$f_body$
language plpgsql;