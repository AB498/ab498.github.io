SELECT student.name -- READ FROM BOTTOM UP
FROM students AS student -- Means student has taken all courses
WHERE NOT EXISTS ( -- When the list of courses not taken by student is empty
  SELECT c.course_id -- List of courses not taken by student
  FROM courses AS c -- Take that to be a valid course for above query
  WHERE NOT EXISTS ( -- Where not found the target cource c to be taken by student
    SELECT * -- A Loop to find at least one course of id c.course_id that student has taken
    FROM courses AS c2
    WHERE courceTo.student_id = student.student_id 
    AND c2.course_id = c.course_id
  )
);
