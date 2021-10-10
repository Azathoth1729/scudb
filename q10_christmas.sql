--non-recursive
WITH cte AS (
    SELECT ProductName
    FROM Product P, OrderDetail OD, "Order" O , Customer C
    WHERE P.Id = OD.ProductId AND OD.OrderId = O.Id AND O.CustomerId = C.Id AND C.CompanyName = 'Queen Cozinha' AND OrderDate LIKE '2014-12-25%'
    ORDER BY P.Id
)
SELECT GROUP_CONCAT(cte.ProductName, ',')
FROM cte;

--recursive
WITH RECURSIVE
    init AS (
        SELECT ProductName, RANK() over (ORDER BY P.Id) AS Rank, RANK() over (ORDER BY P.Id) + 1 AS Next
        FROM Product P,
             OrderDetail OD,
             "Order" O,
             Customer C
        WHERE P.Id = OD.ProductId
          AND OD.OrderId = O.Id
          AND O.CustomerId = C.Id
          AND C.CompanyName = 'Queen Cozinha'
          AND OrderDate LIKE '2014-12-25%'
        ORDER BY P.Id
    ),
    concate(ProductName, Rank, Next) AS (
            SELECT ProductName, Rank, Next
            FROM init
            WHERE RANK = 1
            UNION ALL
            SELECT  concate.ProductName|| ', ' || init.ProductName , init.Rank, init.Next
            FROM concate
                JOIN init ON init.Rank = concate.Next
    ),
    final(ProductName, Rank, Next) AS (
        SELECT ProductName, Rank, MAX(Rank)
        FROM concate
    )

SELECT ProductName
FROM final;

