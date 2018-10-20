-- Initial tables begin
drop table if exists "Заказчики" cascade;
create table "Заказчики" (
    "код заказчика" integer primary key,
    "наименовние" text not null,
    "адрес" text,
    "телефон" text,
    "контактное лицо" text
);

drop table if exists "Товары" cascade;
create table "Товары" (
    "код товара" integer primary key,
    "цена" float not null,
    "доставка" boolean not null,
    "описание" text
);

drop table if exists "Заказы" cascade;
create table "Заказы" (
    "код заказа" integer primary key,
    "код заказчика" integer not null,
    "код товара" integer not null,
    "количество" integer not null,
    "дата" date not null,
    foreign key ("код заказчика") references "Заказчики"("код заказчика"),
    foreign key ("код товара") references "Товары"("код товара")
);

-- Initial tables end

drop table if exists "Способы доставки" cascade;
create table "Способы доставки" (
    "код способа доставки" integer primary key,
    "наименование" text not null,
    "скорость" integer not null
);

drop table if exists "Цены способов доставки" cascade;
create table "Цены способов доставки" (
    "код способа доставки" integer not null,
    "цена" float not null,
    "дата" date not null,
    primary key("код способа доставки", "цена", "дата"),
    foreign key("код способа доставки") references "Способы доставки"("код способа доставки")
);

drop table if exists "Способы доставки товаров" cascade;
create table "Способы доставки товаров" (
    "код товара" integer not null,
    "код способа доставки" integer not null,
    primary key("код товара", "код способа доставки"),
    foreign key("код товара") references "Товары"("код товара"),
    foreign key("код способа доставки") references "Способы доставки"("код способа доставки")
);

alter table "Заказы"
    add column "код способа доставки" integer not null,
    add column "цена" float,
    add constraint "код способа доставки"
        foreign key("код способа доставки") 
        references "Способы доставки"("код способа доставки");

create or replace function trigger_function_on_update_table_orders()
returns trigger as $f_body$
begin
    new."цена" := 
        (select new."количество" * t_products."цена" + t_methods."цена" as method_cost
        from "Товары" t_products inner join "Цены способов доставки" t_methods
            on new."код товара" = t_products."код товара"
                and new."код способа доставки" = t_methods."код способа доставки"
        where new."дата" >= t_methods."дата"
        order by t_methods."дата" DESC
        limit 1)::float;

    return new;
end
$f_body$
language plpgsql;

drop trigger if exists trigger_on_update_table_orders on "Заказы";
create trigger trigger_on_update_table_orders
    before insert or update on "Заказы" for each row execute
    procedure trigger_function_on_update_table_orders();