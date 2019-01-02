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
		values (private_function_generate_long_hash(login),
				private_function_generate_long_hash(password),
				0, nickname);
	end
$f_body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


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
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_check_permissions(user_token text, minimal_user_permission_level integer)
returns boolean
as $body$
	select exists (
		select user_sessions.token
		from user_sessions inner join users on user_sessions.id_uuid_user = users.id_uuid
		where users.id_role >= minimal_user_permission_level and user_token = user_sessions.token
	)
$body$
language sql;


create or replace function private_function_get_permission_level(user_token text)
returns integer
as $body$
	select users.id_role
	from user_sessions inner join users on user_sessions.id_uuid_user = users.id_uuid
	where user_token = user_sessions.token;
$body$
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_game_list(game_amount integer, list_offset integer)
returns table(	game_name text,
				game_cost float,
				discount float4,
				date_of_release_game date )
as $body$
	select 	games.game_name,
			games.game_cost,
			games.discount,
			games.date_of_release_game
	from games
	where available
	offset list_offset
	limit game_amount;
$body$
SECURITY DEFINER
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_game_with_developer_list(game_amount integer, list_offset integer)
returns table(	game_name text,
				game_cost float,
				discount float4,
				date_of_release_game date,
				game_description text,
				developer_name text,
				developer_description text)
as $body$
	select 	games.game_name,
			games.game_cost,
			games.discount,
			games.date_of_release_game,
			games.game_description,
			developers.developer_name,
			developers.developer_description
	from games inner join developers on games.id_developer = developers.id
	where available
	offset list_offset
	limit game_amount;
$body$
SECURITY DEFINER
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_developer_info(name text)
returns table(	developer_name text,
				developer_description text)
as $body$
	select 	developers.developer_name,
			developers.developer_description
	from developers
	where developers.developer_name = name;
$body$
SECURITY DEFINER
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_generate_long_hash(target_text text)
returns text
as $body$
	begin
		return crypt(target_text, gen_salt('bf', 8));
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_test_long_hash(target_text text, text_hash text)
returns boolean
as $body$
	begin
		return text_hash = crypt(target_text, text_hash);
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_generate_short_hash(target_text text)
returns text
as $body$
	begin
		return encode(digest(target_text, 'sha1'), 'hex');
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_update_login(user_token text, new_login text)
returns void
as $body$
	declare
	user_id uuid;
	login_length integer;
	
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		login_length := length(new_login);
	
		if login_length < 6 or login_length > 32 then
			raise 'Login must be between 6 and 32 characters!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		update users
			set user_login = private_function_generate_long_hash(new_login)
			where id_uuid = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_get_user_nickname(user_token text)
returns text
as $body$
	declare
	user_login text;
	
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		select users.user_nickname into user_login
			from users inner join user_sessions on users.id_uuid = user_sessions.id_uuid_user
			where user_sessions.token = user_token;
		
		return user_login;
	end
$body$
language plpgsql;


create or replace function private_function_get_user_id_by_token(user_token text)
returns uuid
as $body$
	declare
	user_id uuid;
	
	begin	
		select user_sessions.id_uuid_user into user_id
			from  user_sessions
			where user_sessions.token = user_token;
		
		return user_id;
	end
$body$
language plpgsql;


create or replace function private_function_get_user_id_by_nickname(user_nickname text)
returns uuid
as $body$
	declare
	user_id uuid;
	
	begin
		select users.id_uuid into user_id
			from  users
			where users.user_nickname = user_nickname;
		
		return user_id;
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_update_password(user_token text, old_password text, new_password text)
returns void
as $body$
	declare
	old_user_password_hash text;
	user_id uuid;
	password_length integer;
	
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		password_length := length(new_password);
	
		if password_length < 6 or password_length > 32 then
			raise 'Password must be between 6 and 32 characters!';
		end if;

	
		user_id := private_function_get_user_id_by_token(user_token);
	
		select user_password into old_user_password_hash 
			from users
			where users.id_uuid = user_id;
		
		if ( private_function_test_long_hash(old_password, old_user_password_hash) = false ) then
			raise 'Invalid old password!';
		end if;
	
		update users
			set user_password = private_function_generate_long_hash(new_password)
			where users.id_uuid = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_test_token(user_token text)
returns boolean
as $body$
	select exists(
		select token from user_sessions where token = user_token
	);
$body$
SECURITY DEFINER
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_logout(user_token text)
returns void
as $body$
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		delete from user_sessions where user_sessions.token = user_token;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_put_money(user_token text, amount_money float)
returns void
as $body$
	declare
		user_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		update user_purses
			set user_money = user_money + amount_money
			where id_uuid_user = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_buy(user_id uuid, description text, cost float)
returns uuid
as $body$
	declare
	new_user_money_amount float;
	new_purchase_uuid uuid;

	begin
		update user_purses
			set user_money = user_money - cost
			where id_uuid_user = user_id returning user_money into new_user_money_amount;
		
		if ( new_user_money_amount is null ) then
			raise 'User haven''t purse!';
		end if;
	
		insert into purchases(id_uuid_user, purchase_discription, "cost")
			values (user_id, description, cost) returning id_uuid into new_purchase_uuid;
		
		return new_purchase_uuid;
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_buy_game(user_token text, target_game_name text)
returns void
as $body$
	declare
		user_id uuid;
		game_id uuid;
		game_cost float;
		game_discount float;
		game_developer_id integer;
		purchase_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		select * into game_id, game_cost, game_discount, game_developer_id
		from private_function_get_game_id_and_info(target_game_name);
		
		game_cost := game_cost - game_cost * game_discount;
	
		purchase_id := private_function_buy(user_id, 'Buying a game ' || target_game_name || ' for personal use.', game_cost);
	
		insert into game_purchases(id_uuid_game, id_uuid_purchase)
			values(game_id, purchase_id);
		
		insert into user_games(id_uuid_user, id_uuid_game) 
			values(user_id, game_id);
			
		perform private_function_pay_developer_for_purchase(game_developer_id, game_cost);
		
	end
$body$
SECURITY DEFINER
language plpgsql;


create or replace function public_function_buy_game_addon(user_token text, target_game_name text, target_addon_name text)
returns void
as $body$
	declare
		user_id uuid;
		game_id_ uuid;
		game_developer_id integer;
		game_addon_id uuid;
		game_addon_cost float;
		purchase_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		select game_id, developer_id into game_id_, game_developer_id
		from private_function_get_game_id_and_info(target_game_name);
	
		select games_addons.id_uuid, games_addons.addon_cost into game_addon_id, game_addon_cost
			from games_addons
				inner join games_addons_list on games_addons.id_uuid = games_addons_list.id_uuid_addon
			where games_addons.addon_name = target_addon_name and
					games_addons_list.id_uuid_game = game_id_;
		
		if ( game_addon_id is null ) then
			raise 'Addon ''%'' for game ''%'' not found!', target_addon_name, target_game_name;
		end if;
	
		purchase_id := private_function_buy(user_id, 'Buying a game addon' || target_addon_name || ' for personal use.', game_addon_cost);
	
		insert into game_addon_purchases(id_uuid_game_addon, id_uuid_purchase)
			values(game_addon_id, purchase_id);
		
		insert into user_game_addons(id_uuid_user, id_uuid_game_addon) 
			values(user_id, game_addon_id);
			
		perform private_function_pay_developer_for_purchase(game_developer_id, game_addon_cost);
		
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_delete_account(user_token text)
returns void
as $body$
	declare
		user_id uuid;
		purchase_ids record;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);	
	
		delete from users where id_uuid = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_developer_status_cost()
returns float
as $body$
	begin
		return 99.0;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_buy_developer_status(user_token text, developer_name text)
returns void
as $body$
	declare
		user_id uuid;
		purchase_id uuid;
		developer_id integer;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		purchase_id := private_function_buy(user_id, 'Buying Developer Status', public_function_get_developer_status_cost());
		
		insert into developers(developer_name) 
			values(developer_name) 
			returning id into developer_id;
	
		insert into developer_status_purchases(id_developer, id_uuid_purchase) 
			values(developer_id, purchase_id);
	
		insert into users_developers(id_uuid_user, id_developer, main_developer) 
			values(user_id, developer_id, true);
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/

/*
create or replace function public_function_buy_game_for_user(user_token text, target_user_nickname, target_game_name text)
returns void
as $body$
	declare
		user_id uuid;
		game_id uuid;
		game_cost float;
		game_discount float;
		purchase_id uuid;
		target_user_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		select games.id_uuid, games.game_cost, games.discount 
		into game_id, game_cost, game_discount
			from games
			where games.game_name = target_game_name;
		
		if ( game_id is null ) then
			raise 'Game ''%'' not found!', target_game_name;
		end if;
	
	
		target_user_id := private_function_get_user_id_by_nickname(target_user_nickname);
		if ( target_user_id is null ) then
			raise 'User with nickname ''%'' not found!', target_user_nickname;
		end if;
		
		game_cost := game_cost - game_cost * game_discount;
	
		purchase_id := private_function_buy(user_id, 'Buying a game for personal use.', game_cost);
	
		insert into game_purchases(id_uuid_game, id_uuid_purchase)
			values(game_id, purchase_id);
		
	end
$body$
SECURITY DEFINER
language plpgsql;
*/



/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_pay_developer_for_purchase(developer_id integer, money float)
returns void
as $body$
	update developers
		set developer_money = developer_money + money * 0.85
		where id = developer_id;
$body$
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_add_comment(user_id uuid, comment_text text)
returns uuid
as $body$
	declare
		new_comment_id uuid;
	
	begin
		insert into commentaries(id_uuid_user, "comment") 
			values(user_id, comment_text)
			returning id_uuid into new_comment_id;
		
		return new_comment_id;
	end
$body$
language plpgsql;


create or replace function private_function_modify_comment(comment_id uuid, user_id uuid, new_comment_text text)
returns void
as $body$
	declare
		updated_rows bigint;

	begin
		with update_result as (
			update commentaries set
				"comment" = new_comment_text,
				modify_time = localtimestamp
				where id_uuid = comment_id and id_uuid_user = user_id
				returning *
		)
		select count(*) into updated_rows
			from update_result;
		
		if ( updated_rows <> 1 ) then
			raise 'Error on modify comment!';
		end if;
	end
$body$
language plpgsql;


create or replace function private_function_delete_comment(comment_id uuid, user_id uuid)
returns void
as $body$
	declare
		deleted_rows bigint;
	begin
		with delete_result as (
			delete from commentaries 
				where id_uuid = comment_id and id_uuid_user = user_id
				returning *
		)
		select count(*) into deleted_rows
			from delete_result;		
		
		if ( deleted_rows <> 1 ) then
			raise 'Error on delete comment!';
		end if;
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_add_comment_for_game(user_token text, game_name text, comment_text text)
returns uuid
as $body$
	declare
		user_id uuid;
		game_id uuid;
		new_comment_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
		game_id := private_function_get_game_id_by_name(game_name);
		
		new_comment_id := private_function_add_comment(user_id, comment_text);
		insert into games_commentaries(id_uuid_game, id_uuid_comment) 
			values(game_id, new_comment_id);
		
		return new_comment_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


create or replace function public_function_modify_comment_for_game(user_token text, comment_uuid uuid, new_text text)
returns void
as $body$
	declare
		user_id uuid;
		game_id uuid;
		new_comment_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
		
		execute private_function_modify_comment(comment_uuid, user_id, new_text);
	end
$body$
SECURITY DEFINER
language plpgsql;


create or replace function public_function_delete_comment_for_game(user_token text, comment_uuid uuid)
returns void
as $body$
	declare
		user_permission_level integer;
		user_id uuid;
		game_id uuid;
		new_comment_id uuid;

	begin
		user_permission_level := private_function_get_permission_level(user_token);
		
		if ( user_permission_level is null ) then
			raise 'Permission denied!';
		end if;
	
		case
			when user_permission_level = 0 then
				user_id := private_function_get_user_id_by_token(user_token);
				execute private_function_delete_comment(comment_uuid, user_id);
			
			when user_permission_level > 0 then
				delete from games_commentaries where games_commentaries.id_uuid_comment = comment_uuid;
		end case;
		
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function private_function_get_game_id_and_info(
				in target_game_name text,
				out game_id uuid,
				out game_cost float,
				out game_discount float,
				out developer_id integer)
as $body$
	begin
		select games.id_uuid, games.game_cost, games.discount, games.id_developer
		into game_id, game_cost, game_discount, developer_id
			from games
			where games.game_name = target_game_name;
		
		if ( game_id is null ) then
			raise 'Game ''%'' not found!', target_game_name;
		end if;
	end
$body$
language plpgsql;


create or replace function private_function_get_game_id_by_name(target_game_name text)
returns uuid
as $body$
	declare
		game_id_ uuid;
	
	begin
		select game_id into game_id_
			from private_function_get_game_id_and_info(target_game_name);
		
		return game_id_;
	end
$body$
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


-- Developer tests
create or replace function private_function_is_developer(user_id uuid)
returns boolean
as $body$
	select exists(
		select *
		from users_developers
		where users_developers.id_uuid_user = user_id			
	);
$body$
language sql;


create or replace function private_function_is_main_developer(user_id uuid)
returns boolean
as $body$
	select exists(
		select *
		from users_developers
		where users_developers.id_uuid_user = user_id and users_developers.main_developer
	);
$body$
language sql;


create or replace function private_function_is_developer_of_game(user_id uuid, game_id uuid)
returns boolean
as $body$
	select exists(
		select *
		from users_developers
			inner join developers on users_developers.id_developer = developers.id
			inner join games on developers.id = games.id_developer
		where users_developers.id_uuid_user = user_id and games.id_uuid = game_id
	);
$body$
language sql;


create or replace function private_function_is_main_developer_of_game(user_id uuid, game_id uuid)
returns boolean
as $body$
	select exists(
		select *
		from users_developers
			inner join developers on users_developers.id_developer = developers.id
			inner join games on developers.id = games.id_developer
		where 	users_developers.id_uuid_user = user_id and
				games.id_uuid = game_id and
				users_developers.main_developer
	);
$body$
language sql;


create or replace function private_function_get_developer_id(user_id uuid)
returns integer
as $body$
	select users_developers.id_developer
	from users_developers
	where users_developers.id_uuid_user = user_id;
$body$
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_add_game(
				user_token text,
				game_name text,
				game_cost float,
				game_description text)
returns void
as $body$
	declare
		user_id uuid;
		developer_id integer;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		if ( private_function_is_main_developer(user_id) = false ) then
			raise 'Permission denied!';
		end if;
	
		developer_id := private_function_get_developer_id(user_id);
	
		insert into games("game_name", "date_of_release_game", "game_cost", "id_developer", "game_description")
			values(game_name, current_date, game_cost, developer_id, game_description);
	end
$body$
SECURITY DEFINER
language plpgsql;


create or replace function public_function_add_game_addon(user_token text, game_name text, addon_name text, addon_cost float, addon_description text)
returns void
as $body$
	declare
		user_id uuid;	
		game_id uuid;
		game_addon_id uuid;

	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
		game_id := private_function_get_game_id_by_name(game_name);
	
		if ( private_function_is_main_developer_of_game(user_id, game_id) = false ) then
			raise 'Permission denied!';
		end if;
	
		insert into games_addons(addon_name, addon_cost, addon_description)
			values(addon_name, addon_cost, addon_description)
			returning id_uuid into game_addon_id;
		
		insert into games_addons_list(id_uuid_game, id_uuid_addon)
			values(game_id, game_addon_id);
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/

/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - Р В РЎСџР В Р’ВµР РЋР вЂљР В Р вЂ Р РЋРІР‚в„–Р В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_cooments_for_game(name_of_game text, commemts_amount integer, list_offset integer)
returns table (id_uuid uuid, nickname text, "role" text, status text, add_comment_time timestamp, modify_comment_time timestamp, "comment" text)
as $body$
select 		commentaries.id_uuid,
			users.user_nickname,
			roles.role_name,
			statuses.status_name,
			commentaries.comment_time,
			commentaries.modify_time,
			commentaries."comment"	
	from  	games
			inner join 	games_commentaries 	on games_commentaries.id_uuid_game = games.id_uuid
			inner join 	commentaries 		on games_commentaries.id_uuid_comment = commentaries.id_uuid
			inner join 	users 				on commentaries.id_uuid_user = users.id_uuid
			left join 	user_statuses 		on users.id_uuid = user_statuses.id_uuid_user
			left join 	statuses 			on user_statuses.id_status = statuses.id	
			inner join 	roles				on users.id_role = roles.id
	where	games.game_name = name_of_game
	order by commentaries.comment_time asc
	limit 	commemts_amount
	offset 	list_offset;
$body$
SECURITY DEFINER
language sql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - Р В РІР‚в„ўР РЋРІР‚С™Р В РЎвЂўР РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_summary_game_cost_with_addons(user_token text, name_of_game text)
returns table (game_cost float, summary_addons_cost float)
as $body$
	declare
		user_id uuid;
		game_id uuid;
	
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		return query
			select games.game_cost, sum(games_addons.addon_cost::float) as summary_addons_cost
			from 	games
					inner join user_games			on user_games.id_uuid_game = games.id_uuid
					left join games_addons_list 	on games.id_uuid = games_addons_list.id_uuid_game
					left join games_addons 		on games_addons.id_uuid = games_addons_list.id_uuid_addon
					left join user_game_addons		on user_game_addons.id_uuid_game_addon = games_addons.id_uuid
			where	games.game_name = name_of_game and
					user_games.id_uuid_user = user_id and
					( (games_addons.id_uuid is not null and
							user_game_addons.id_uuid_game_addon is not null and
							user_game_addons.id_uuid_user = user_id) or
					  (games_addons.id_uuid is null and user_game_addons.id_uuid_game_addon is null) )
			group by games.game_cost;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - Р В РЎС›Р РЋР вЂљР В Р’ВµР РЋРІР‚С™Р В РЎвЂ�Р В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_developer_of_most_discussed_game()
returns table (developer_name text)
as $body$
	select 	developers.developer_name
	from	developers
			inner join games				on games.id_developer = developers.id
			inner join games_commentaries	on games_commentaries.id_uuid_game = games.id_uuid
			inner join commentaries			on games_commentaries.id_uuid_comment = commentaries.id_uuid
	group by developers.developer_name
	order by count(commentaries.id_uuid) desc, max(commentaries.comment_time) desc;
$body$
SECURITY DEFINER
language sql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - Р В РЎСџР РЋР РЏР РЋРІР‚С™Р РЋРІР‚в„–Р В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_game_addons(target_game_name text)
returns table (addon_name text, addon_cost float, addon_description text)
as $body$
	select 	games_addons.addon_name, games_addons.addon_cost, games_addons.addon_description
	from	games_addons
			inner join games_addons_list	on games_addons.id_uuid = games_addons_list.id_uuid_addon
			inner join games				on games.id_uuid = games_addons_list.id_uuid_game
	where	games.game_name = target_game_name;
$body$
SECURITY DEFINER
language sql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - Р В Р РѓР В Р’ВµР РЋР С“Р РЋРІР‚С™Р В РЎвЂўР В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_top_spending_money(begin_date date, end_date date)
returns table (user_nickname text)
as $body$
	select 	users.user_nickname
	from	users
			inner join purchases on users.id_uuid = purchases.id_uuid_user
	where	purchases.purchase_date_time::date >= begin_date and
			purchases.purchase_date_time::date <= end_date
	group by users.user_nickname
	order by sum(purchases."cost"::float) desc
	limit 1;
$body$
SECURITY DEFINER
language sql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - Р В РІР‚в„ўР В РЎвЂўР РЋР С“Р РЋР Р‰Р В РЎпїЅР В РЎвЂўР В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“ - Р РЋР С“Р В РЎпїЅ. Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂ�Р В РЎвЂ“Р В РЎвЂ“Р В Р’ВµР РЋР вЂљ
 */

/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - 11 Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_user_game_addons(user_token text, target_game_name text)
returns table (addon_name text, addon_description text)
as $body$
	declare
		user_id uuid;
		game_id uuid;
	
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
		game_id := private_function_get_game_id_by_name(target_game_name);
	
		return query
			select	games_addons.addon_name, games_addons.addon_description
			from 	games_addons
					inner join games_addons_list 	on games_addons.id_uuid = games_addons_list.id_uuid_addon
					inner join user_game_addons		on games_addons_list.id_uuid_addon = user_game_addons.id_uuid_game_addon
			where 	user_game_addons.id_uuid_user = user_id and
					games_addons_list.id_uuid_game = game_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - 12 Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_games_nobody_bought(game_amount integer, list_offset integer)
returns table (game_name text, game_cost float, game_discount float4, date_of_release_game date)
as $body$
	select 	games.game_name, games.game_cost, games.discount, games.date_of_release_game
	from	games
	where	games.available and games.id_uuid not in (
		select user_games.id_uuid_game from user_games
	)
	limit game_amount
	offset list_offset;
$body$
language sql;

-- Р В РІР‚в„ўР РЋРІР‚С™Р В РЎвЂўР РЋР вЂљР В Р’В°Р РЋР РЏ Р РЋРІР‚РЋР В Р’В°Р РЋР С“Р РЋРІР‚С™Р РЋР Р‰
create or replace function public_function_lock_game(user_token text, target_game_name text)
returns void
as $body$
	begin
		if ( private_function_check_permissions(user_token, 2) = false ) then
			raise 'Permission denied!';
		end if;
	
		update games
			set available = false
			where id_uuid = target_game_name;
	end
$body$
SECURITY DEFINER
language plpgsql;


create or replace function public_function_unlock_game(user_token text, target_game_name text)
returns void
as $body$
	begin
		if ( private_function_check_permissions(user_token, 2) = false ) then
			raise 'Permission denied!';
		end if;
	
		update games
			set available = true
			where id_uuid = target_game_name;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*
 *  Р В РІР‚в„ўР В РЎвЂ™Р В РІР‚вЂњР В РЎСљР В Р’В«Р В РІвЂћСћ Р В РІР‚вЂќР В РЎвЂ™Р В РЎСџР В Р’В Р В РЎвЂєР В Р Р‹ [Р В РІР‚вЂќР В РЎвЂ™Р В РІР‚СњР В РЎвЂ™Р В РЎСљР В РїС—Р…Р В РІР‚Сћ] - 13 Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“
 */
create or replace function public_function_get_user_desired_games(nickname text)
returns table (desired_game text)
as $body$
	select 	games.game_name
	from	games
			inner join desired_games 	on games.id_uuid = desired_games.id_uuid_game
			inner join users			on desired_games.id_uuid_user = users.id_uuid
	where	users.user_nickname = nickname;
$body$
SECURITY DEFINER
language sql;


create or replace function private_function_user_have_game(user_id uuid, game_id uuid)
returns boolean
as $body$
	select exists (
		select * from user_games 
		where 	user_games.id_uuid_user = user_id and
				user_games.id_uuid_game = game_id
	);
$body$
language sql;


create or replace function public_function_add_game_to_desired_games(user_token text, target_game_name text)
returns void
as $body$
	declare
		user_id uuid;
		game_id uuid;
		
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
		game_id := private_function_get_game_id_by_name(target_game_name);
	
		if ( private_function_user_have_game(user_id, game_id) ) then
			raise 'User have this game!';
		end if;
	
		insert into desired_games(id_uuid_user, id_uuid_game)
			values (user_id, game_id);
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_user_games(user_token text)
returns table( game_name text )
as $body$
	declare
		user_id uuid;
		
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise exception using message = 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		return query
		select 	games.game_name
		from	games
				inner join user_games on games.id_uuid = user_games.id_uuid_game
		where	user_games.id_uuid_user = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_current_user_info(user_token text)
returns table( 	user_nickname text,
				user_role text,
				user_status text,
				user_money float,
				user_cashback float,
				user_personal_discount float
			 )
as $body$
	declare
		user_id uuid;
		
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise exception using message = 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		return query
		select 	users.user_nickname, roles.role_name,
				statuses.status_name, user_purses.user_money,
				user_purses.cashback, user_purses.personal_discount
		from	users
				inner join roles on users.id_role = roles.id
				inner join user_statuses on user_statuses.id_uuid_user = user_id
				inner join statuses on user_statuses.id_status = statuses.id
				inner join user_purses on users.id_uuid = user_purses.id_uuid_user
		where	users.id_uuid = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_current_user_profile(user_token text)
returns table( 	role_id integer,
				user_role boolean
			 )
as $body$
	declare
		user_id uuid;
		
	begin
		if ( private_function_check_permissions(user_token, 0) = false ) then
			raise exception using message = 'Permission denied!';
		end if;
	
		user_id := private_function_get_user_id_by_token(user_token);
	
		return query
		select 	users.id_role, users_developers.main_developer
		from	users
				left join users_developers on users_developers.id_uuid_user = users.id_uuid
		where	users.id_uuid = user_id;
	end
$body$
SECURITY DEFINER
language plpgsql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_game_commentaries(target_game_name text, comment_amount integer, comments_offset integer)
returns table (	user_nickname 	text,
				comment_time 	timestamp,
				modify_time 	timestamp,
				"comment"		text,
				id				uuid
			  )
as $body$
	select 	users.user_nickname, commentaries.comment_time, commentaries.modify_time,
			commentaries."comment", commentaries.id_uuid
	from 	users
			inner join commentaries 		on commentaries.id_uuid_user = users.id_uuid
			inner join games_commentaries 	on games_commentaries.id_uuid_comment = commentaries.id_uuid
			inner join games 				on games.id_uuid = games_commentaries.id_uuid_game
	where 	games.game_name = target_game_name
	order by commentaries.comment_time
	limit 	comment_amount
	offset	comments_offset;
$body$
SECURITY DEFINER
language sql;


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function public_function_get_full_game_info(target_game_name text)
returns table( 	game_name text,
				game_cost float,
				discount float4,
				date_of_release_game date,
				game_description text,
				developer_name text,
				game_genres text[],
				game_tags text[],
				game_devices text[]
			 )
as $body$
	declare
		game_id uuid;
		game_genres text[];
		game_tags text[];
		game_devices text[];
		
	begin
		game_id := private_function_get_game_id_by_name(target_game_name);
		
		game_genres := array(
			select 	games_genres.genre_name
			from 	games_genres
					inner join games_genres_list on games_genres.id = games_genres_list.id_genre
			where	games_genres_list.id_uuid_game = game_id
		);
	
		game_tags := array(
			select 	games_tags.tag_name
			from 	games_tags
					inner join games_tags_list on games_tags.id = games_tags_list.id_tag
			where	games_tags_list.id_uuid_game = game_id
		);
	
		game_devices := array(
			select 	devices.device_name
			from 	devices
					inner join games_supported_devices on devices.id = games_supported_devices.id_device
			where	games_supported_devices.id_uuid_game = game_id
		);
	
		return query
		select 	games.game_name, games.game_cost, games.discount,
				games.date_of_release_game, games.game_description,
				developers.developer_name, game_genres, game_tags, game_devices
		from	games
				left join developers on games.id_developer = developers.id
		where	games.id_uuid = game_id and games.available;
	end
$body$
SECURITY DEFINER
language plpgsql;