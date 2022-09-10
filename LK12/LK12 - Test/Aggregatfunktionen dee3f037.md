# DISTINCT:

**Funktion:** Die Zeilen einer Tabelle die mehrfach die selben Werte besitzten werden nur einmal drinnen gelassen.

**Benutzung:** `SELECT DISTINCT City from users`

`SELECT City from users`  erstellt eine Result Tabelle  in dem alle Städte der users drinnen stehen.  Sind zwei users aus "Germany", so wird in dieser Result Tabelle zwei Zeilen die Werte "Germany" haben.\
Fügen wir oben ein `DISTINCT`  hinzu, so werden alle "Germany" Einträge zu einer gemerged.

<br>

# AS:

**Funktion:** Bennene eine Spalte in der Result Tabelle um.

**Benutzung:** `SELECT usernames as name from users`

# COUNT()

**Funktion:** Einträge aus Tabelle zählen

**Benutzung:** `SELECT count(*) from Nutzer`

# MIN() / MAX():

**Funktion:** Extreme suchen. (min(): minimum - max(): maximum)

**Benutzung:** `SELECT min(alter) from Nutzer`

# YEAR(\<datum>)

**Funktion:** Liefert den Jahr von einem Timestamp bzw. Datum

**Benutzung:** `Select * from users where YEAR(birthday) < 2006`

# CURRENT\_TIME()

**Funktion:** Liefert die aktuelle Zeit als Datum bzw. Timestamp

**Benutzung:** `Select CURRENT_TIME as Now`

Gibt dir die aktuelle Zeit mit dem Namen "Now"
