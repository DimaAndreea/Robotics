# TEMA 2

<details>
  <summary> <b> Despre </b> </summary>

  ## Descrierea temei:
  - Aceasta tema simuleaza un joc inspirat de TypeRacer, cu un LED RGB ca indicator de stare si doua butoane: Start/Stop si Dificultate.
  - LED-ul RGB indica starea jocului: in repaus este alb, in numaratoarea inversa de la start clipeste timp de 3 secunde
  - In timpul jocului devine verde pentru tastare corecta si rosu pentru greseli
  - Butonul Start/Stop initiaza sau opreste runda
  - Butonul de dificultate schimba viteza cuvintelor intre Easy, Medium si Hard, afisand mesajul corespunzator in terminal.
  - Runda dureaza 30 de secunde, timp in care jucatorul trebuie sa tasteze corect cuvintele afisate.
  - La final, scorul cu numarul de cuvinte scrise corect este afisat in terminal
 
##
</details>



<details>
  <summary><b>Cerinte</b></summary>

  ## 1. Detalii tehnice:
  - LED RGB - Indicator de stare:
    - In starea de repaus, LED-ul va avea culoarea alba.
    - La apasarea butonului de start, LED-ul va clipi timp de 3 secunde, indicand o numaratoare inversa pana la inceperea rundei.
    - In timpul unei runde: LED-ul va fi verde daca textul introdus este corect si va deveni rosu in caz de greseala.

- Butonul Start/Stop:
  - Modul de repaus: Daca jocul este oprit, apasarea butonului initiaza o noua runda dupa o numaratoare inversa de 3 secunde.
  - In timpul unei runde: Daca runda este activa, apasarea butonului o va opri imediat.
 
- Butonul de dificultate:
  - Butonul de dificultate controleaza viteza cu care apar cuvintele si poate fi folosit doar in starea de repaus.
  - La fiecare apasare, dificultatea se schimba ciclind intre: (Easy, Medium, Hard).
  - La schimbarea dificultatii, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.
  
- Generarea cuvintelor:
  - Se va crea un dictionar de cuvinte.
  - In timpul unei runde, cuvintele vor fi afisate in terminal intr-o ordine aleatorie.
  - Daca cuvantul curent a fost scris corect, un cuvant nou va fi afisat imediat. Daca nu, un nou cuvant va aparea dupa intervalul de timp stabilit in functie de dificultate.
  
- Alte observatii:
  - Timpul alocat pentru o runda este de 30 de secunde.
  - La sfarsitul fiecarei runde, se va afisa in terminal cate cuvinte au fost scrise corect.
 
## 2. Flow:
- Jocul este in repaus. LED-ul RGB are culoarea alba.

- Se alege dificultatea jocului folosind butonul de dificultate, iar in terminal va aparea “Easy/Medium/Hard mode on!”.

- Se apasa butonul de start/stop.

- LED-ul clipeste timp de 3 secunde, iar in terminal se va afisa numaratoarea inversa: 3, 2, 1.

- LED-ul devine verde si incep sa apara cuvinte de tastat.

- La tastarea corecta, urmatorul cuvant apare imediat. Daca nu se tasteaza cuvantul in timpul stabilit de dificultate, va aparea un nou cuvant.

- O greseala face LED-ul sa devina rosu. Pentru a corecta cuvantul, se va folosi tasta BackSpace.

- Dupa 30 de secunde, runda se termina, iar in terminal se va afisa scorul: numarul total de cuvinte scrise corect.

- Jocul se poate opri oricand cu butonul de start/stop.

  ##
</details>

<details>
  <summary> <b> Componente </b> </summary>

  ## Lista componentelor folosite:
    
  * Arduino UNO (ATmega328P microcontroller)
  * 1x LED RGB
  * 2x Butoane 
  * 5x Rezistoare (3x 220 ohm, 2x 1000 ohm)
  * Breadbord
  * Fire de legatura
  ##
  
</details>


<details>
  <summary> <b> Schema electrica </b> </summary>
  
   ## Schema electrica a circuitului implementat pe Tinkercad

  ![schema_electrica](https://github.com/user-attachments/assets/0e185056-20b3-499c-b11d-64d9c823ab85)

  ##

</details>


<details>
  <summary> <b> Poze ale setup-ului fizic </b> </summary>
  
  ## Poze cu montajul implementat fizic:
  
  ![IMG_5963](https://github.com/user-attachments/assets/f6a804ff-ddbc-47cf-8fdd-5b348a305e7c)
  ![IMG_5965](https://github.com/user-attachments/assets/79cb56c7-48c1-402f-a189-7bcb1279bf43)
  ![IMG_5966](https://github.com/user-attachments/assets/64740498-a129-4ade-995f-7634ebe51cbb)
  ![IMG_5968](https://github.com/user-attachments/assets/53e536ed-59e5-4f7e-944e-d873c0821f78)
  ![IMG_5972](https://github.com/user-attachments/assets/15b7a250-0a97-407c-b23f-6906e0c6990f)

##
</details>



<details>
  <summary> <b> Video cu montajul fizic </b> </summary>

  ## Link catre videoul ce arata functionalitatea montajului fizic:
  [https://www.youtube.com/watch?v=eAE200TeHGY](https://youtu.be/5zqyRliXPS8)
  ##
</details>
