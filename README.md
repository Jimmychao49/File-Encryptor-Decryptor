# File-Encryptor-Decryptor
This was my second programming assignment at university.

Voor de tweede programmeeropgave is het de bedoeling dat we een programma hebben dat een bestand kan encoderen en decoderen, een nieuw bestand aanmaakt en daarin schrijft. We encoderen de bestanden met een caesarcijferversleuteling, waar de verschuiving afhangt van het ingevoerde cijfer en de cijfers die zich in het te encoderen bestand te vinden zijn. 

Bijvoorbeeld een invoer bestand(voorbeeld1.txt) die we coderen met de pincode 4859:

    dit is een file die we coderen3456
    het zal vast een nieuwe pin nu hebben.

Dit zal dan gecodeerd worden naar het volgende bestand(voorbeeld2.txt):

    hqy)m{%niv%omtj)hqj){m%lslj{iv8=9>
    kiy&}eq&yexz#ijt#rnkx{j&sms&qy%nhfgkq2

# Other parameters
Daarnaast detecteren wij bij het encoderen ook getallen die in de invoer bestanden staan. Vervolgens rekenen we uit of het een potentiële Lychrel-getal kan zijn. Het aantal iteraties tot een palindroom wordt gegeven of het aantal iteraties totdat het over de INTMAX gaat. Wanneer het over de INTMAX gaat, dan is het een potentieel Lychrel-getal.

Het getal 295 Bijvoorbeeld zou dan 18 iteraties hebben totdat het tot een palindroom komt.
Een getal met grondtal 2 kan ook een potentiële Lychrel-getal zijn, omdat in ons programma de berekening voor een lychrel getal niet verder kan dan de INTMAX, maar de meeste cijfers onder de INTMAX eindigen wel in een palindroom.

Het programma werkt niet wanneer er een bij het encoderen een pin groter dan 9999 of kleiner dan 0 wordt gegeven, bij decoderen een pin groter dan 9999 of kleiner dan -1.

# Notes
In ons programma hebben wij een werkende bruteforce functie, maar hij is langzamer dan anderen. We hebben voor nu cout << pin om te laten zien dat hij wel bezig is met de file readen.
