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