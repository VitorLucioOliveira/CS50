SELECT name
FROM people
JOIN (SELECT person_id
      FROM stars JOIN movies ON stars.movie_id = movies.id
      WHERE movies.title = 'Toy Story') AS T
ON people.id = T.person_id;
