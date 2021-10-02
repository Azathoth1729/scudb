
-- WITH ctePN(ProductName)
-- AS
-- (
--     SELECT P.Id, ProductName
--     FROM Product P, OrderDetail OD, "Order" O , Customer C
--     WHERE P.Id = OD.ProductId AND OD.OrderId = O.Id AND O.CustomerId = C.Id AND C.CompanyName =  'Queen Cozinha' AND OrderDate LIKE '2014-12-25%'
--     ORDER BY P.Id
--
--
-- )

-- WITH cte AS (
    SELECT P.Id, ProductName, rank() over (ORDER BY P.Id) AS Rank
    FROM Product P, OrderDetail OD, "Order" O , Customer C
    WHERE P.Id = OD.ProductId AND OD.OrderId = O.Id AND O.CustomerId = C.Id AND C.CompanyName =  'Queen Cozinha' AND OrderDate LIKE '2014-12-25%'
    ORDER BY P.Id
-- )


