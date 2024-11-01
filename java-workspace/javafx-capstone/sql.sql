create table user
(
    id       varchar(30) default '' not null
        primary key,
    password varchar(30)            null,
    location varchar(30)            null
);

insert into user values('test','test','')