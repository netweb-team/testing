CREATE TABLE users (
    id serial not null primary key,
    username varchar(64) unique,
    password varchar(128),
    is_login boolean
);

CREATE TABLE document (
    id serial not null primary key,
    dtext text,
    name varchar(128) unique
);

CREATE TABLE ownership (
    id serial not null primary key,
    user_id int,
    doc_id int,
    CONSTRAINT to_user FOREIGN KEY(user_id) REFERENCES users(id) on delete CASCADE,
    CONSTRAINT to_document FOREIGN KEY(doc_id) REFERENCES document(id) on delete CASCADE
);