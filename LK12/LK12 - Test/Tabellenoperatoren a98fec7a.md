# Projektion (Select):&#x20;

**Funktion:** Bestimmte Spalte(n) von Tabellen zu einer "Result Tabelle" gruppieren und ausgeben.&#x20;

**Benutzung:** `SELECT <spaltennamen>, <weitereSpaltennamen> from <Tabelle>`

Beispiel:

- `SELECT names from users`
  - gruppiert alle Namen der Tabelle "users" in eine Result Tabelle und zeig diese an.
- `SELECT names from (SELECT names from users)`
  - gruppoert alle Namen in eine Resultat2 Tabelle der Resultat Tabelle von `SELECT names from users` und zeigt diese dann an. Die Ausgabe sieht 1 zu 1 so aus wie oben.

# Selektion (Where):

**Funktion:** Zeilen hinaus filtern, welche eine Bedingung erfüllen.

**Benutzung:** `SELECT <spaltenname> from <Tabelle> where <Bedingung (z.B. name="Tom")>`

**Wichtig:** Man kann auch mithilfe von `and` und `or` mehre Bedingungen festlegen mit einem `where` definieren.

**Beispiel:** `... where name='Tom' and nachname='Müller'`

Operatoren die hierbei genutzt werden können:

- `not`
- `and`, `or`
- `=`, `>`, `<`, `>=`, `<=`, `<>` | `!=`
- `BETWEEN`
- `LIKE`
- `IN`

# ORDER BY

**Funktion:** Ergebnisse sortieren. (ASC: ansteigend, DESC: absteigend)

**Benutzung:** `SELECT <spaltenname> from <Tabelle> ORDER BY <spaltenname> DESC/ASC`

Per default wird die Resultat Tabelle in Aufsteigender reihenfolge (ASC) sortiert.

Bei Zahlen wird der größe nach Sortiert (`1 < 2`, usw.) und bei Buchstaben wird sortiert mit `"a" < "b"` und `"aa" < "ab"`.

Bei `ASC` wird das kleinste Element wird nach oben Sortiert und das größte nach unten und vice versa bei `DESC`.

# GROUP BY

**Funktion:** Gibt es mehrere gleiche Eigenschaften in verschiedene Zeilen, werden diese mit der Group by Funktion zur einer Konvertiert. Dazu kann man noch Funktionen benutzen um eigenschaften über diese anschließende "Zeilengruppe(n)" zu bekommen.  (z.B. Count(\*) oder max(\*))

**Benutzung:** `SELECT Nutzername, count(*) from Nutzer GROUP BY Nutzername`

→ Zeigt an, wie viele Nutzernamen es von den jeweiligen exestierenden gibt.&#x20;

# Like

**Funktion:** Begriff der bei Konditionen (where) verwendet wird um zu übeprüfen ob ein Wert eine gewissen ähnlichkeit zu einem anderen hat

**Benutzung:** `Select * from usernames where username like 'mark%'`

→ Gibt alle Zeilen aus wo der username mit mark anfängt. \
"%" bedeutet: alle mögliche Zeichenfolgen der länge 0 bis n. \
"\_" steht für genau ein mögliches Zeichen. Z.b. "\_\_llo" würde "Hello" und "hallo" matchen.

# Limit

**Funktion:** Limitiert die Ergebnisse einer Tabelle auf n Zeilen.&#x20;

Benutzung: Select \* from users limit 0,4

→ Es werden nur die ersten 4 Zeilen der Result Tabelle ausgegeben.&#x20;
