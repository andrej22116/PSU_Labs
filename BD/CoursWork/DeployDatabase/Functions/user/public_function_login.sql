/*
	Функция авторизует пользователя, если данные были верны.
	Возвращает токен пользователя для доступа к некоторым данным.
*/
create or replace function public_function_login(login text, password text)
returns text
as $f_body$
	declare
		token_hash text;
		time_current timestamptz;
		user_hash_login text;
	begin
		
		select users.user_login into user_hash_login
		from users 
		where private_function_test_long_hash(login, users.user_login)
		and private_function_test_long_hash(password, users.user_password);
		if user_hash_login is null then
			raise 'Invalid login or password!';
		end if;
	
		time_current := current_timestamp;
		
		token_hash := private_function_generate_short_hash(login || password || time_current);
	
		insert into user_sessions(id_uuid_user, session_begin_time, token) values(
			(select users.id_uuid from users where users.user_login = user_hash_login),
			time_current,
			token_hash
		);
	
		return token_hash;
	end;
$f_body$
language plpgsql;