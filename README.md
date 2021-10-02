# scudb(p1)

**2019141460319 金可成**

## q1

### Problem Description

+ The purpose of this query is to make sure that the formatting of your output
  matches exactly the formatting of our auto-grading script.
+ **Details**: List all Category Names ordered alphabetically.


### Code

```sql
SELECT CategoryName
FROM Category
ORDER BY CategoryName;
```

### Result

![q1 result](./assets/q1.png "q1 result")


## q2

### Problem Description
+ Get all unique `ShipNames` from the Order table that contain a hyphen `'-'` 
+ **Details**: In addition, get all the characters preceding the (first) hyphen. Return ship
names alphabetically. Your first row should look like `Bottom-Dollar Markets|Bottom`

### Code

```sql
SELECT DISTINCT ShipName || '|' ||substring(ShipName, 1, charindex('-', ShipName) -1)
FROM "Order"
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;
```

### Result

![q2 result](./assets/q2.png "q2 result")


## q3

### Problem Description

+ Indicate if an order's `ShipCountry` is in North America. For our purposes, this
  is `'USA', 'Mexico', 'Canada'`
+ **Details**: You should print the Order `Id` , `ShipCountry` , and another column that is
  either `'NorthAmerica'` or `'OtherPlace'` depending on the Ship Country.
  Order by the primary key ( `Id` ) ascending and return 20 rows starting from Order
  `Id` `15445` Your output should look
  like `15445|France|OtherPlace` or `15454|Canada|NorthAmerica`

### Code

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

### Result

![q3 result](./assets/q3.png "q3 result")


## q4

### Problem Description

+ For each `Shipper` , find the percentage of orders which are late
+ **Details**: An order is considered late if ShippedDate > RequiredDate . Print the
  following format, order by descending percentage, rounded to the nearest
  hundredths, like United Package|23.44

### Code

```sql
SELECT Delay.CompanyName || '|' ||
       ROUND((CAST(Delay AS FLOAT) * 100 / CAST(Total AS FLOAT)) ,2) AS PerDelay
FROM
    (SELECT  S.Id, S.CompanyName, COUNT(*) AS Delay
    FROM Shipper S, "Order" O
    WHERE S.Id = O.ShipVia AND O.ShippedDate > O.RequiredDate
    GROUP BY S.Id) Delay
    ,
    (SELECT  S.Id, S.CompanyName, COUNT(*) AS Total
    FROM Shipper S, "Order" O
    WHERE S.Id = O.ShipVia
    GROUP BY S.Id) Total
WHERE Delay.Id = Total.Id
ORDER BY PerDelay DESC
```

### Result

![q4 result](./assets/q4.png "q4 result")


## q5

### Problem Description

+ Compute some statistics about categories of products
+ **Details**: Get the number of products, average unit price (rounded to 2 decimal
  places), minimum unit price, maximum unit price, and total units on order for
  categories containing greater than 10 products.
  Order by Category `Id` . Your output should look like `Beverages|12|37.98|4.5|263.5|60`

### Code

```sql
SELECT CategoryName || '|' ||
       COUNT(*) || '|' ||
       round(AVG(UnitPrice), 2) || '|' ||
       MIN(UnitPrice) || '|' ||
       MAX(UnitPrice) || '|' ||
       SUM(UnitsOnOrder) AS Q5
FROM Product, Category
WHERE Product.CategoryId = Category.Id
GROUP BY CategoryId
HAVING COUNT(*) > 10
ORDER BY CategoryId
```

### Result

![q5 result](./assets/q5.png "q5 result")


## q6

### Problem Description

+ For each of the 8 discontinued products in the database, which customer made the
  first ever order for the product? Output the
  customer's `CompanyName` and `ContactName`
+ **Details**: Print the following format, order by `ProductName` alphabetically: `Alice
  Mutton|Consolidated Holdings|Elizabeth Brown`

### Code

```sql

```

### Result

![q6 result](./assets/q6.png "q6 result")


## q7

### Problem Description

+
+

### Code

```sql

```

### Result

![q7 result](./assets/q7.png "q7 result")


## q8

### Problem Description

+
+

### Code

```sql

```

### Result

![q8 result](./assets/q8.png "q8 result")


## q9

### Problem Description

+
+

### Code

```sql

```

### Result

![q9 result](./assets/q9.png "q9 result")


## q10

### Problem Description

+
+

### Code

```sql

```

### Result

![q10 result](./assets/q10.png "q10 result")