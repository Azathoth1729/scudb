WITH final AS (
    WITH cte AS (
        WITH cte_BLONP AS (
            SELECT Id, OrderDate
            FROM "Order"
            WHERE "Order".CustomerId = 'BLONP'
            ORDER BY OrderDate
            LIMIT 10
        )
        SELECT *,
               lag(OrderDate) over ()           AS Temp,
               rank() over (ORDER BY OrderDate) AS Rank
        FROM cte_BLONP
    )

    SELECT Id, OrderDate,
           CASE
               WHEN Rank=1 THEN OrderDate
               ELSE Temp
               END AS PreOrderDate
    FROM cte
)

SELECT Id || '|' ||
       OrderDate || '|' ||
       PreOrderDate || '|' ||
       ROUND(CAST(julianday(OrderDate) - julianday(PreOrderDate) AS FLOAT), 2) AS Q7
FROM final