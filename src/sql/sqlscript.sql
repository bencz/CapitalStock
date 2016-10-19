CREATE TABLE "portfolio" (
  "id" integer primary key autoincrement,
  "version" integer not null,
  "quantity" double precision not null,
  "totalcost" double precision not null,
  "userdetails_id" bigint,
  constraint "fk_portfolio_userdetails" foreign key ("userdetails_id") references "userdetails" ("id") deferrable initially deferred
)

CREATE TABLE "stock" (
  "id" integer primary key autoincrement,
  "version" integer not null,
  "stockcode" text not null,
  "companyname" text not null,
  "lastsaleprice" double precision not null,
  "volume" double precision not null,
  "pricevolume" double precision not null,
  "lastupdate" text,
  "country" text not null,
  "valuechange" double precision not null,
  "changepercent" double precision not null,
  "portfolio_id" bigint,
  constraint "fk_stock_portfolio" foreign key ("portfolio_id") references "portfolio" ("id") deferrable initially deferred
)

CREATE TABLE "trader" (
  "id" integer primary key autoincrement,
  "version" integer not null,
  "balance" double precision not null,
  "users_id" bigint,
  constraint "fk_trader_users" foreign key ("users_id") references "users" ("id") deferrable initially deferred
)

CREATE TABLE "transaction" (
  "id" integer primary key autoincrement,
  "version" integer not null,
  "quantity" integer not null,
  "transactionDate" text,
  "userdetails_id" bigint,
  "stock_id" bigint,
  constraint "fk_transaction_userdetails" foreign key ("userdetails_id") references "userdetails" ("id") deferrable initially deferred,
  constraint "fk_transaction_stock" foreign key ("stock_id") references "stock" ("id") deferrable initially deferred
)

CREATE TABLE "userdetails" (
  "id" integer primary key autoincrement,
  "version" integer not null,
  "name" text not null,
  "lastname" text not null,
  "age" integer not null,
  "country" text not null,
  "city" text not null,
  "users_id" bigint,
  constraint "fk_userdetails_users" foreign key ("users_id") references "users" ("id") deferrable initially deferred
)

CREATE TABLE "users" (
  "id" integer primary key autoincrement,
  "version" integer not null,
  "userName" text not null,
  "password" text not null,
  "accessLevel" integer not null,
  "creationdate" text,
  "lastaccess" text
)