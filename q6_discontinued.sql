SELECT ProductName || '|' ||CompanyName || '|' ||ContactName AS Q6, MIN(OrderDate)
FROM Product P, OrderDetail OD, "Order" O, Customer C
WHERE P.Id = OD.ProductId AND OD.OrderId = O.Id AND O.CustomerId =  C.Id AND P.Discontinued = 1
GROUP BY ProductName
ORDER BY ProductName;
