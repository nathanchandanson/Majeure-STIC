DELETE FROM RESULTAT ;

PROMPT Nombre de lignes a produire
ACCEPT n
DECLARE
	x NUMBER:= 100;
BEGIN
FOR i IN 1..&n LOOP
	  IF MOD(x, 2) = 0 THEN	-- x is even
	   INSERT INTO RESULTAT VALUES (i, x|| ' is even');
	  ELSE
	   INSERT INTO RESULTAT VALUES ( i, x|| ' is odd');
	  END IF;
	  x := x+1 ;
END LOOP;
COMMIT;
END; 
/
SELECT * FROM RESULTAT ; 
