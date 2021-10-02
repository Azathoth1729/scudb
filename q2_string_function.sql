SELECT DISTINCT ShipName || '|' ||substring(ShipName, 1, charindex('-', ShipName) -1)
FROM "Order"
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;



