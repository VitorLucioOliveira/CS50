SELECT name
FROM people
JOIN (SELECT person_id
      FROM stars JOIN movies ON stars.movie_id = movies.id
      WHERE movies.year = 2004) AS T
ON people.id = T.person_id
ORDER BY birth;
