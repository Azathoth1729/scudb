SELECT DISTINCT ShipName || '|' || SUBSTR(ShipName, 1, INSTR(ShipName, '-') -1)
FROM "Order"
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;



