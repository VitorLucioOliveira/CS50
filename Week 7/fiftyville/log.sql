
-- report of the day --
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
+-------------------------------------------------------------------------------------------------------------------------------------------------- +
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.                                                                       |
| Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.      |
+---------------------------------------------------------------------------------------------------------------------------------------------------+

-- bakery logs --  5P2BI95
SELECT activity ,hour , minute, license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 and minute <= 25 ;
+----------+------+--------+---------------+
| activity | hour | minute | license_plate |
+----------+------+--------+---------------+
| exit     | 10   | 16     | 5P2BI95       |
| exit     | 10   | 18     | 94KL13X       |
| exit     | 10   | 18     | 6P58WS2       |
| exit     | 10   | 19     | 4328GD8       |
| exit     | 10   | 20     | G412CB7       |
| exit     | 10   | 21     | L93JTIZ       |
| exit     | 10   | 23     | 322W7JE       |
| exit     | 10   | 23     | 0NTHK55       |
+----------+------+--------+---------------+

-- interview --
SELECT name ,transcript
FROM interviews
WHERE month = 7 AND day = 28;                                                                                                                |

| Ruth    |
Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot inthat time frame.                                                          |

| Eugene  |
I don't know the thief's name, but it was someone I recognized. Earlier this morning,
before I arrived at Emmas bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
                                                                                              |
| Raymond |
As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket. |


-- Phone calls --
SELECT caller  , receiver , duration
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <=60;                                                                                                                |
+----------------+----------------+----------+
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (130) 555-0289 | (996) 555-8899 | 51       |
| (499) 555-9472 | (892) 555-8872 | 36       |
| (367) 555-5533 | (375) 555-8161 | 45       |
| (609) 555-5876 | (389) 555-5198 | 60       |
| (499) 555-9472 | (717) 555-1342 | 50       |
| (286) 555-6063 | (676) 555-6554 | 43       |
| (770) 555-1861 | (725) 555-3243 | 49       |
| (031) 555-6622 | (910) 555-3251 | 38       |
| (826) 555-1652 | (066) 555-9701 | 55       |
| (338) 555-6650 | (704) 555-2131 | 54       |
+----------------+----------------+----------+

-- NUMEROs ---
SELECT name, passport_number
FROM people
WHERE phone_number IN (SELECT caller
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <=60) AND license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 and minute <= 25 );

+--------+-----------------+
|  name  | passport_number |
+--------+-----------------+
| Sofia  | 1695452385      |
| Diana  | 3592750733      |
| Kelsey | 8294398571      |
| Bruce  | 5773159633      |
+--------+-----------------+

-- VOO --
SELECT passport_number , flight_id
FROM passengers
WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29) and passport_number IN (SELECT passport_number
FROM people
WHERE phone_number IN (SELECT caller
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <=60) AND license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 and minute <= 25 ));

+-----------------+-----------+
| passport_number | flight_id |
+-----------------+-----------+
| 3592750733      | 18        |
| 1695452385      | 36        |
| 5773159633      | 36        |
| 8294398571      | 36        |
+-----------------+-----------+

-- SAIU Cidade para--
 SELECT city, full_name, id
 FROM airports
 WHERE id IN ( SELECT destination_airport_id
 FROM flights
 WHERE id = 18
);
+--------+-----------------------------+----+
|  city  |          full_name          | id |
+--------+-----------------------------+----+
| Boston | Logan International Airport | 6  |
+--------+-----------------------------+----+

--- ATM --

SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'deposit' ;

+----------------+------------------+
| account_number | transaction_type |
+----------------+------------------+
| 86363979       | deposit          |
+----------------+------------------+

-- Conta do Banco --

SELECT name, phone_number
FROM people
WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'deposit' )
);



