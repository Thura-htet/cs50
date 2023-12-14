SELECT DISTINCT title FROM movies WHERE title IN 
(SELECT title FROM movies JOIN (stars JOIN people ON stars.person_id = people.id) ON movies.id = stars.movie_id WHERE name = "Johnny Depp")
AND title IN 
(SELECT title FROM movies JOIN (stars JOIN people ON stars.person_id = people.id) ON movies.id = stars.movie_id WHERE name = "Helena Bonham Carter");