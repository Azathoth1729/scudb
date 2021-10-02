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