SELECT *
FROM
    (SELECT *,
            rank() over (
                ORDER BY Id
                ) AS ProductRank
    FROM Product
    WHERE  Product.Discontinued = 0) Discontinued
WHERE Discontinued.ProductRank % 8 = 0