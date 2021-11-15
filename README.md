# lab1

**2019141460319 金可成**

This is SCU Sqlite Database Systems

## assignment

### Task1: Extensible Hash Table

+ [x] `HashKey(K)`
+ [x] `Find(K, V)`
+ [x] `Insert(K, V)`
+ [x] `Remove(K) `
+ [x] `GetGlobalDepth()`
+ [x] `GetLocalDepth(bucket_id)`
+ [x] `GetNumBuckets()`
+ [x] thread-safe using `std::mutex`

#### result:

![extensible_hash_test](assests/extensible_hash_test.png)

### Task2: LRU Page Replacement Policy

+ [x] `Insert(T)`
+ [x] `Victim(T)`
+ [x] `Erase(T)`
+ [x] `Size()`
+ [x] thread-safe using `std::mutex`

#### result:

![lru_replacer_test](assests/lru_replacer_test.png)

### Task3: Buffer pool Manager

### Build

```
mkdir build
cd build
cmake ..
make
```

Debug mode:

```
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Testing

```
cd build
make check
```

### Run virtual table extension in SQLite

Start SQLite with:

```
cd build
./bin/sqlite3
```

In SQLite, load virtual table extension with:

```
.load ./lib/libvtable.dylib
```

or load `libvtable.so` (Linux), `libvtable.dll` (Windows)

Create virtual table:  
1.The first input parameter defines the virtual table schema. Please follow the format of (column_name [space]
column_type) seperated by comma. We only support basic data types including INTEGER, BIGINT, SMALLINT, BOOLEAN, DECIMAL
and VARCHAR.  
2.The second parameter define the index schema. Please follow the format of (index_name [space] indexed_column_names)
seperated by comma.

```
sqlite> CREATE VIRTUAL TABLE foo USING vtable('a int, b varchar(13)','foo_pk a')
```

After creating virtual table:  
Type in any sql statements as you want.

```
sqlite> INSERT INTO foo values(1,'hello');
sqlite> SELECT * FROM foo ORDER BY a;
a           b         
----------  ----------
1           hello   
```

See [Run-Time Loadable Extensions](https://sqlite.org/loadext.html)
and [CREATE VIRTUAL TABLE](https://sqlite.org/lang_createvtab.html) for further information.

### Virtual table API

https://sqlite.org/vtab.html

### TODO

* update: when size exceed that page, table heap returns false and delete/insert tuple (rid will change and need to
  delete/insert from index)
* delete empty page from table heap when delete tuple
* implement delete table, with empty page bitmap in disk manager (how to persistent?)
* index: unique/dup val, variable val
