SELECT *
FROM(
    SELECT IFNULL(CompanyName, 'MISSING_NAME') AS CompanyName, CustomerId, ROUND(SUM(UnitPrice * Quantity) ,2)  AS TotalExpenditures,
           NTILE(4) OVER(ORDER BY CAST(ROUND(SUM(UnitPrice * Quantity) ,2) AS float)) AS ID
    FROM "Order"
         JOIN OrderDetail ON "Order".Id = OrderDetail.OrderId
         LEFT JOIN Customer ON "Order".CustomerId  = Customer.Id
    GROUP BY CustomerId
    ORDER BY TotalExpenditures
)
WHERE ID = 1;