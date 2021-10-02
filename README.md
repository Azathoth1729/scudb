# scudb(p1)

**2019141460319 金可成**

## q1

### code

```sql
SELECT CategoryName
FROM Category
ORDER BY CategoryName;
```

### result

![q1 result](./assets/q1.png "q1 result")

## q2

### code

```sql
SELECT DISTINCT ShipName || '|' ||substring(ShipName, 1, charindex('-', ShipName) -1)
FROM "Order"
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;
```

### result

![q2 result](./assets/q2.png "q2 result")

## q3

### code

```sql
SELECT Id || '|' || ShipCountry || '|' ||
CASE
    WHEN ShipCountry IN ('USA', 'Mexico', 'Canada') THEN 'NorthAmerica'
    ELSE 'OtherPlace'
END AS CountryInfo
FROM "Order"
WHERE Id >=15445
ORDER BY Id;
```

### result

![q3 result](./assets/q3.png "q3 result")

## q4

### code

```sql

```

### result

![q4 result](./assets/q4.png "q4 result")