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