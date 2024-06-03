SELECT name
FROM people
JOIN (SELECT person_id
      FROM directors JOIN ratings ON directors.movie_id = ratings.movie_id
      WHERE rating >= 9.0) AS T
ON people.id = T.person_id;
