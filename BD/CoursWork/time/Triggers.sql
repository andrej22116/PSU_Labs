create or replace function trigger_function_on_user_login() returns trigger
as $body$
	begin
		if (TG_OP = 'INSERT') then
			delete from user_sessions where user_sessions.id_uuid_user = new.id_uuid_user;
			return new;
		elseif (TG_OP = 'UPDATE') then
			raise 'Can''t update rows on this table!';
		end if;
	end
$body$
language plpgsql;

create trigger trigger_on_user_login
before insert or update on user_sessions for each row
execute procedure trigger_function_on_user_login();


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function trigger_function_on_register_user() returns trigger
as $body$
	begin
		insert into user_purses(id_uuid_user) values(new.id_uuid);
		insert into user_statuses(id_uuid_user, id_status) values(new.id_uuid, 0);
		return new;
	end
$body$
language plpgsql;

create trigger trigger_on_register_user
after insert on users for each row
execute procedure trigger_function_on_register_user();


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function trigger_function_on_add_new_game() returns trigger
as $body$
	begin
		insert into games_statistics(id_uuid_game) values(new.id_uuid);
		return new;
	end
$body$
language plpgsql;

create trigger trigger_on_add_new_game
after insert on games for each row
execute procedure trigger_function_on_add_new_game();


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function trigger_function_on_buy() returns trigger
as $body$
	declare
		delta_money float;
		cashback float;
	begin
		if ( new.user_money < 0 ) then
			raise 'Error on buy. Insufficient funds!';
		end if;
		
		delta_money := old.user_money - new.user_money;
		--raise 'Old money: %, new money %, delta: %', old.user_money, new.user_money, delta_money;
	
		cashback := delta_money - delta_money * new.personal_discount;
		cashback := cashback * new.cashback;
	
		new.user_money := new.user_money + cashback;
		return new;
	end
$body$
language plpgsql;

create trigger trigger_on_buy
before update of user_money on user_purses for each row
execute procedure trigger_function_on_buy();


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function trigger_function_on_delete_account() returns trigger
as $body$
	declare
		purchase_ids record;
	
	begin
		delete from user_purses where id_uuid_user = old.id_uuid;
		delete from user_statuses where id_uuid_user = old.id_uuid;
		delete from user_sessions where id_uuid_user = old.id_uuid;
		delete from desired_games where id_uuid_user = old.id_uuid;
		delete from games_ratings where id_uuid_user = old.id_uuid;
		delete from user_games where id_uuid_user = old.id_uuid;
		delete from user_game_addons where id_uuid_user = old.id_uuid;
	
		for purchase_ids in select id_uuid from purchases where id_uuid_user = old.id_uuid
		loop
			delete from game_purchases where id_uuid_purchase = purchase_ids.id_uuid;
			delete from game_addon_purchases where id_uuid_purchase = purchase_ids.id_uuid;
			delete from developer_status_purchases where id_uuid_purchase = purchase_ids.id_uuid;
		end loop;
	
		delete from purchases where id_uuid_user = old.id_uuid;
	
		update news set id_uuid_user = uuid_nil() where id_uuid_user = old.id_uuid;
		update commentaries set id_uuid_user = uuid_nil() where id_uuid_user = old.id_uuid;
	
		return old;
	end
$body$
language plpgsql;

create trigger trigger_on_delete_account
before delete on users for each row
execute procedure trigger_function_on_delete_account();


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/


create or replace function trigger_function_on_delete_comment() returns trigger
as $body$	
	begin
		delete from games_commentaries where id_uuid_comment = old.id_uuid;
		delete from games_news_commentaries where id_uuid_comment = old.id_uuid;
		delete from global_news_commentaries where id_uuid_comment = old.id_uuid;
	
		return old;
	end
$body$
language plpgsql;

create trigger trigger_on_delete_comment
before delete on commentaries for each row
execute procedure trigger_function_on_delete_comment();


/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/
/*===================================================================================================*/
/*---------||------------||------------||------------||---------------||---------------||------------*/

-- Важный триггер, который обновляет статус пользователя - 8 запрос
create or replace function trigger_function_on_buy_new_game() returns trigger
as $body$
	declare
		user_games_amount integer;
		exists_on_statuses boolean;
	
	begin
		select count(user_games.id_uuid_user) into user_games_amount
			from user_games
			where user_games.id_uuid_user = new.id_uuid_user
			group by user_games.id_uuid_user;
		
		select exists (
			select id from statuses where statuses.id = user_games_amount
		) into exists_on_statuses;
	
		if ( exists_on_statuses ) then
			update user_statuses
				set id_status = user_games_amount
				where id_uuid_user = new.id_uuid_user;
		end if;
		
		return new;
	end
$body$
language plpgsql;

create trigger trigger_on_buy_new_game
after insert on user_games for each row
execute procedure trigger_function_on_buy_new_game();

create or replace function trigger_function_on_buy_new_desired_game() returns trigger
as $body$
	begin
		
		delete from desired_games
			where 	desired_games.id_uuid_game = new.id_uuid_game and
					desired_games.id_uuid_user = new.id_uuid_user;
		
		return new;
	end
$body$
language plpgsql;

create trigger trigger_on_buy_new_desired_game
after insert on user_games for each row
execute procedure trigger_function_on_buy_new_desired_game();