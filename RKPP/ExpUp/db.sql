create table athletes (
	id serial primary key,
	surname text not null,
	name text not null,
	middle_name text not null,
	age integer not null default 14 check(age >= 14),
	is_female boolean not null default false
);

create table physicals_characteristics (
	id serial primary key,
	id_athlete integer not null references athletes,
	mass float not null,
	biceps_girth float not null,
	chest_girth float not null,
	waist_girth float not null,
	leg_girth float not null,
	weight_on_biceps float not null,
	weight_on_chest float not null,
	weight_on_foot float not null,
	weight_on_back float not null,
	back_width float not null,
	mass_and_fat_ratio float not null,
	fixation_date date not null,
	unique (id_athlete, fixation_date)
	
);

create table body_checks (
	id serial primary key,
	id_athlete integer not null references athletes,
	fixation_date date not null,
	therapist boolean not null,
	surgeon boolean not null,
	oculist boolean not null,
	endDoctor boolean not null,
	dopingTest boolean not null,
	conclusion text not null,
	unique (id_athlete, fixation_date)
);

create table visits (
	id serial primary key,
	id_athlete integer not null references athletes,
	visit_date date not null,
	visit_time time not null,
	visited boolean not null default false,
	unique (id_athlete, visit_date)
);

create table payment (
	id serial primary key,
	id_athlete integer not null references athletes,
	payment_date timestamp not null,
	amount_of_payment float not null,
	days integer not null default 3 check (days > 0)
);