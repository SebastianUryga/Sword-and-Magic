# Heroes 3 Battle Engine

![Hnet-image (1)](https://user-images.githubusercontent.com/33723260/133456961-1486f473-0002-4b63-89f0-e084efd1cd81.gif)
---
## Filmik przedstawiający działanie aplikacji:

 https://youtu.be/RJXgUcLYeWE
 
---

## DEMO Aplikacji

Aby uruchomić aplikacjie na lokalnej maszynie należy:

### Windows
 - [POBIERZ ARCHIWUM ZIP](https://github.com/SebastianUryga/Heroes3-engine/files/7618349/Release.zip) (wraz z zawartością)
 - rozpakuj archiwum
 - uruchom plik BattlefieldH3.exe
 
### Linux
 - Sklonować repozytorium       ```git clone https://github.com/SebastianUryga/Heroes3-engine.git```
 - zainstalować bibliotekę SFML ```sudo apt install libsfml-dev```
 - przejść do katalogu z kodem źródłowym ```cd Heroes3-engine/BattlefieldH3/BattlefieldH3/```
 - skompilować program          ```g++ -std=c++17 *.cpp -I. -o h3mm $(pkg-config --libs sfml-all)```
 - uruchomić program            ```./h3mm```

---
## O Aplikacji
Heroes battle engine to symulator prowadzenia bitew. 
Aplikacja korzysta z biblioteki graficzenij SFML. 
Symulator przedstawia alternatywną mechanikę, którą możnaby zastąpić prowadzenie bitew w ogrinalenej grze Heroes of Might & Magic III.
Dodano mechaniki inspirowane innymi grami strategicznymi takimi jak Age of Empires.

---
## Działanie Aplikacji
#### Menu Główne
W menu głównym mamy możliwość rozpoczęcia rozgrywki/symulacji, przejścia do trybu edycji, lub wyjścia z aplikacji.
#### Tryb Edycji
Umożliwia użytkownikowi ustawienie garnizonów, czyli jakie dwie armie będą ze sobą walczyć.
Każdy garnizon ma po siedem slotów. Po dwukrotnym kliknięciu na jeden ze slotów ukaże nam się okienko wyboru jednostki oraz ustawienia jej ilości, któa nie może być większa od 20.
#### Tryb Rozgrywki
Pozwala nam oglądać przebieg bitwy, jak również mamy możliwość wydawania poleceń jednostom, czy używania czarów.
Aby wydać rozkaz jednostkom, należy zaznaczyć je za pomocą myszki i możemy:
- wydać rozkaz ataku klikając PPM na wrogą jednostkę
![Hnet-image](https://user-images.githubusercontent.com/33723260/133455004-17f35019-5333-4a12-bc24-e772d82827bd.gif)

- kazać przemieścić się na konkretne miejsce klikając PPM na odopowiednie pole
- przyjąć postawę agresywną klikając przycisk Agrressiv Position.
![Hnet-image (1)](https://user-images.githubusercontent.com/33723260/133456961-1486f473-0002-4b63-89f0-e084efd1cd81.gif)
- przyjąć postawę obronną klikając przycisk Defence Position

Aby użyć czaru należy kliknąć przycisk Spell Book, wybrać czar kilkając jedną z ikon i wybrać jednostkę LPM.

---
## Autor:
Sebastian Uryga
sebastian.uryga@gmail.com
