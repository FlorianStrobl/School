Eine Relation verbindet verschiedene Entities zusammen.&#x20;

Beispiel:&#x20;

`User - <Kauft> - Ware`

# Kardinalitäten

Die Kardinalität einer Relation gibt an, wie viele Elemente einer Seite zu den Elementen der anderen Seite zugeordnet werden. Man unterscheidet (in der Chen-Notation) unter diese Fällen:

- eins zu eins: `1:1`
- eins zu viele: `1:n`
- viele zu viele: `n:m`

n bzw. m steht hier für 1 oder mehr.

<br>

### Wie Identifiziere ich welche Kardinalität ich bei einer Relation habe?

Man stelle sich zwei Fragen bei folgendem Beispiel:

- `Entity1 - <Relation> - Entity2`

Frage 1: Eine Entity1 hat wie viele relations zu Entity2?&#x20;

→ wenn die Antwort 1 ist, dann ist die RECHTE Seite 1, ansonsten n/m

Frage 2: Eine Entity 2 hat wie viele relations zu Entity1?

→ wenn die Antwort 1 ist, dann ist die LINKE Seite 1, ansonsten n/m

<br>

### Realworld Beispiel:&#x20;

- `Mitarbeiter - <Leitet> - Projekt`

Frage 1: Ein Mitarbeiter leitet wie viele Projekte? Antwort: n

Frage 2: Ein Projekt wird von wie vielen Mitarbeiter geleitet? Antwort: m

→ Kardinalität ist **n:m**

Alternative zur Frage 2: Ein Projekt wird von wie vielen Mitarbeitern geleitet? Antwort: 1

→ Kardinalität ist **n:1**

<br>
