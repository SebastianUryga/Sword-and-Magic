# Open Arena of Swords and Magic

---

## DEMO Aplikacji

Aby uruchomić aplikacjie na lokalnej maszynie należy:

### Windows
 - [POBIERZ ARCHIWUM ZIP](https://github.com/SebastianUryga/Heroes3-engine/files/7618349/Release.zip) (wraz z zawartością)
 - rozpakuj archiwum
 - uruchom plik BattlefieldH3.exe
 
### Linux
 - Sklonować repozytorium       ```git clone https://github.com/SebastianUryga/Sword-and-Magic.git```
 - zainstalować bibliotekę SFML ```sudo apt install libsfml-dev```
 - przejść do katalogu z kodem źródłowym ```cd Sword-and-Magic/BattlefieldH3/BattlefieldH3/```
 - skompilować program          ```g++ -std=c++17 *.cpp -I. -o h3mm $(pkg-config --libs sfml-all)```
 - uruchomić program            ```./h3mm```

---
## O Aplikacji
Open Arena of Swords and Magic to symulator prowadzenia bitew. 
Aplikacja korzysta z biblioteki graficzenij SFML. 
Dodano mechaniki inspirowane innymi grami strategicznymi takimi jak Age of Empires.

---
## Działanie Aplikacji
#### Menu Główne
W menu głównym mamy możliwość rozpoczęcia kampani, rozgrywki niestandardowej, przejścia do trybu edycji, ustawień, lub wyjścia z aplikacji.
#### Tryb Edycji
Umożliwia użytkownikowi ustawienie garnizonów, czyli jakie dwie armie będą ze sobą walczyć.
Każdy garnizon ma po siedem slotów. Po dwukrotnym kliknięciu na jeden ze slotów ukaże nam się okienko wyboru jednostki oraz ustawienia jej ilości.
#### Tryb Rozgrywki
Pozwala nam oglądać przebieg bitwy, jak również mamy możliwość wydawania poleceń jednostom, czy używania czarów.
Aby wydać rozkaz jednostkom, należy zaznaczyć je za pomocą myszki i możemy:
- wydać rozkaz ataku klikając PPM na wrogą jednostkę
- kazać przemieścić się na konkretne miejsce klikając PPM na odopowiednie pole
- przyjąć postawę agresywną klikając przycisk Agrressiv Position.
- przyjąć postawę obronną klikając przycisk Defence Position

Aby użyć czaru należy kliknąć przycisk Spell Book, wybrać czar kilkając jedną z ikon i wybrać jednostkę LPM.

---
## Autor:
Sebastian Uryga
sebastian.uryga@gmail.com
