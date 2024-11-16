# TEMA 3: Quick Time

### Coechipier: [@Bogdan-Lungu](https://github.com/Bogdan-Lungu/Robotica)

<details>
  <summary> <b> Despre </b> </summary>

  ## 1. Descrierea temei:
  - Tema presupune crearea unui joc competitiv de reflexe pentru doi jucatori, care concureaza pentru a obtine cel mai mare punctaj, punandu-si la incercare viteza de reactie.
  - Proiectul se va desfasura in echipe de cate doua persoane, fiecare jucator avand butoane si LED-uri proprii.
  - Jocul va include mai multe runde, iar scopul fiecarui jucator este sa apese cat mai rapid butonul care corespunde culorii afisate pe LED-ul RGB al echipei sale.
  - Punctajul fiecarui jucator va fi afisat in timp real pe un ecran LCD, iar la final, jucatorul cu cel mai mare punctaj va fi declarat castigator.

  ## 2. Desfasurarea jocului:
  - Jocul incepe cu un mesaj de bun venit afisat pe LCD.
  - Pentru a porni, jucatorii au la dispozitie mai multe optiuni de start:
    
      a) fie se apasa oricare dintre butoane,
    
      b) fie se foloseste un buton anume desemnat
    
      c) fie un buton suplimentar dedicat pentru start.
    
  - La fiecare runda, fiecare jucator este activ pe rand, iar LED-ul RGB al acestuia se aprinde intr-o culoare care corespunde unuia dintre butoanele sale.
  - Jucatorul trebuie sa apese rapid butonul corect pentru a primi puncte. Cu cat reactioneaza mai repede, cu atat scorul este mai mare.
  - La finalul fiecarei runde, LCD-ul afiseaza punctajele ambilor jucatori.

  ## 3. Timpul si finalizarea jocului
  - Pe parcursul jocului, servomotorul se roteste, indicand progresul.
  - O rotatie completa a servomotorului semnaleaza sfarsitul jocului, iar LCD-ul afiseaza numele castigatorului si scorul final.
  - Dupa cateva secunde, ecranul revine la mesajul de start.

##
</details>


<details> 
  <summary><b>Componente</b></summary>
  
  ## Componentele folosite:
  - 2x Arduino Uno (ATmega328P microcontroller)
  - 2x Breadbord
  - 6x LED-uri (cate 3 pentru fiecare jucator)
  - 2x LED RGB (1 pentru fiecare jucator)
  - 6x Butoane (3 pentru fiecare jucator)
  - 22x Rezistoare (13x 220ohm, 8x 1K, 1x 100ohm)
  - 1x Servomotor
  - 1x LCD
  - 1x Buzzer
  - Linii de legatura
    ##
</details>


<details>
  <summary> <b> Schema electrica </b> </summary>

  ## Schema electrica a circuitului implementat pe Tinkercad
  ![tema3 - final (1)](https://github.com/user-attachments/assets/a0ed21f9-6a5f-423d-b3f3-7bf24b97e93f)

  ##
</details>


<details>
  <summary> <b> Poze ale setup-ului fizic </b> </summary>
  
  ## Poze cu montajul implementat fizic:
  TBD
  ##
</details>


<details>
  <summary> <b> Video cu montajul fizic </b> </summary>

  ## Link catre videoul ce arata functionalitatea montajului fizic:
  TBD
  ##
</details>
