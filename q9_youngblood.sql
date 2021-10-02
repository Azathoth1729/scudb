SELECT RegionDescription || '|' || FirstName || '|' || LastName || '|' || MAX(BirthDate) AS Q9
FROM Employee EE,EmployeeTerritory ET, Territory T, Region R
WHERE EE.Id = ET.EmployeeId AND ET.TerritoryId = T.Id AND T.RegionId = R.Id
GROUP BY R.Id
ORDER BY R.Id;